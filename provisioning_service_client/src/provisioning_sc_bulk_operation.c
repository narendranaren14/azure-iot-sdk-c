// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>  

#include "azure_c_shared_utility/xlogging.h"
#include "azure_c_shared_utility/gballoc.h"

#include "provisioning_sc_bulk_operation.h"
#include "provisioning_sc_shared_helpers.h"
#include "provisioning_sc_json_const.h"
#include "parson.h"

#define UNREFERENCED_PARAMETER(x) x


static void test()
{
    PROVISIONING_BULK_OPERATION bulkop;
    UNREFERENCED_PARAMETER(bulkop);
}

static const char* bulkOperation_mode_toString(PROVISIONING_BULK_OPERATION_MODE mode)
{
    char* result;
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

    char* mode_str = NULL;

    //setup
    if (bulk_op == NULL)
    {
        LogError("bulk operation is NULL");
    }
    else if ((root_value = json_value_init_object()) == NULL)
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
    else if (json_serialize_and_set_struct(root_object, BULK_ENROLLMENT_OPERATION_JSON_KEY_ENROLLMENTS, bulk_op->enrollments, (TO_JSON_FUNCTION)enrollmentList_toJson, REQUIRED) != 0)
}