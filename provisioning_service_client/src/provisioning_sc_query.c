// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>  

#include "azure_c_shared_utility/xlogging.h"

#include "provisioning_sc_query.h"
#include "provisioning_sc_json_const.h"
#include "provisioning_sc_shared_helpers.h"
#include "parson.h"

static JSON_Value* querySpecification_toJson(const PROVISIONING_QUERY_SPECIFICATION* query_spec)
{
    JSON_Value* root_value = NULL;
    JSON_Object* root_object = NULL;

    //Setup
    if (query_spec == NULL)
    {
        LogError("Query Spec is NULL");
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
    else if (json_object_set_string(root_object, QUERY_SPECIFICATION_JSON_KEY_QUERY, query_spec->query_string) != JSONSuccess)
    {
        LogError("Failed to set %s in JSON string", QUERY_SPECIFICATION_JSON_KEY_QUERY);
    }

    return root_value;
}

//const char* querySpecification_serializeToJson(PROVISIONING_QUERY_SPECIFICATION* query_spec)
//{
//    char* result = NULL;
//    char* serialized_string = NULL;
//    JSON_Value* root_value = NULL;
//
//    if (query_spec == NULL)
//    {
//        LogError("Cannot serialize NULL");
//    }
//    else if ((root_value = individualEnrollment_toJson(query_spec)) == NULL)
//    {
//        LogError("Creating json object failed");
//    }
//    else if ((serialized_string = json_serialize_to_string(root_value)) == NULL)
//    {
//        LogError("Failed to serialize to JSON");
//    }
//    else if (mallocAndStrcpy_s(&result, serialized_string) != 0)
//    {
//        LogError("Failed to copy serialized string");
//    }
//
//    if (root_value != NULL)
//    {
//        json_value_free(root_value);
//        root_value = NULL;
//    }
//    if (serialized_string != NULL)
//    {
//        json_free_serialized_string(serialized_string);
//        serialized_string = NULL;
//    }
//
//    return result;
//}

// queryResponse_deserializeFromJson(const char* json_string)
//{
//
//}
