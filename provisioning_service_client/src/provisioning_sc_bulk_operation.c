// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>  

#include "azure_c_shared_utility/xlogging.h"
#include "azure_c_shared_utility/gballoc.h"
#include "azure_c_shared_utility/crt_abstractions.h"

#include "provisioning_sc_bulk_operation.h"
#include "provisioning_sc_models_serializer.h"
#include "provisioning_sc_shared_helpers.h"
#include "provisioning_sc_json_const.h"
#include "provisioning_sc_enrollment.h"
#include "parson.h"

#define UNREFERENCED_PARAMETER(x) x


static void test()
{
    PROVISIONING_BULK_OPERATION bulkop;
    UNREFERENCED_PARAMETER(bulkop);
}

static const char* bulkOperation_mode_toString(PROVISIONING_BULK_OPERATION_MODE mode)
{
    const char* result;
    if (mode == BULK_OP_CREATE)
    {
        result = BULK_ENROLLMENT_MODE_JSON_VALUE_CREATE;
    }
    else if (mode == BULK_OP_UPDATE)
    {
        result = BULK_ENROLLMENT_MODE_JSON_VALUE_UPDATE;
    }
    else if (mode == BULK_OP_UPDATE_IF_MATCH_ETAG)
    {
        result = BULK_ENROLLMENT_MODE_JSON_VALUE_UPDATE_IF_MATCH_ETAG;
    }
    else if (mode == BULK_OP_DELETE)
    {
        result = BULK_ENROLLMENT_MODE_JSON_VALUE_DELETE;
    }
    else
    {
        result = NULL;
    }

    return result;
}

static JSON_Value* bulkOperation_toJson(const PROVISIONING_BULK_OPERATION* bulk_op)
{
    JSON_Value* root_value = NULL;
    JSON_Object* root_object = NULL;

    const char* mode_str = NULL;

    //setup
    if ((root_value = json_value_init_object()) == NULL)
    {
        LogError("json_value_init_object failed");
    }
    else if ((root_object = json_value_get_object(root_value)) == NULL)
    {
        LogError("json_value_get_object failed");
        json_value_free(root_value);
        root_value = NULL;
    }

    //Set data
    else if (((mode_str = bulkOperation_mode_toString(bulk_op->mode)) == NULL) || (json_object_set_string(root_object, BULK_ENROLLMENT_OPERATION_JSON_KEY_MODE, mode_str) != JSONSuccess))
    {
        LogError("Failed to set '%s' in JSON string", BULK_ENROLLMENT_OPERATION_JSON_KEY_MODE);
        json_value_free(root_value);
        root_value = NULL;
    }
    else if (json_serialize_and_set_struct_array(root_object, BULK_ENROLLMENT_OPERATION_JSON_KEY_ENROLLMENTS, bulk_op->enrollments, bulk_op->num_enrollments, individualEnrollment_toJson) != 0)
    {
        LogError("Failed to set '%s' in JSON string", BULK_ENROLLMENT_OPERATION_JSON_KEY_ENROLLMENTS);
        json_value_free(root_value);
        root_value = NULL;
    }

    return root_value;
}

char* bulkOperation_serializeToJson(const PROVISIONING_BULK_OPERATION* bulk_op)
{
    char* result = NULL;
    char* serialized_string = NULL;
    JSON_Value* root_value = NULL;

    if (bulk_op == NULL || bulk_op->enrollments == NULL)
    {
        LogError("Invalid bulk operation");
    }
    else if ((root_value = bulkOperation_toJson(bulk_op)) == NULL)
    {
        LogError("Creating json object failed");
    }
    else if ((serialized_string = json_serialize_to_string(root_value)) == NULL)
    {
        LogError("Failed to serialize to JSON");
    }
    else if (mallocAndStrcpy_s(&result, serialized_string) != 0)
    {
        LogError("Failed to copy serialized string");
    }

    if (root_value != NULL)
    {
        json_value_free(root_value);
        root_value = NULL;
    }
    if (serialized_string != NULL)
    {
        json_free_serialized_string(serialized_string);
        serialized_string = NULL;
    }

    return result;
}