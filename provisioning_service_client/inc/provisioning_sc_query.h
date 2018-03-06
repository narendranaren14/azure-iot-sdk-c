// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef PROVISIONING_SC_QUERY_H
#define PROVISIONING_SC_QUERY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    
    typedef struct PROVISIONING_QUERY_SPECIFICATION_TAG
    {
        char* query_string;
    } PROVISIONING_QUERY_SPECIFICATION;

    typedef struct PROVISIONING_QUERY_TAG
    {
        size_t page_size;
        char* continuation_token;
        PROVISIONING_QUERY_SPECIFICATION* query_spec;

    } PROVISIONING_QUERY;

    typedef struct PROVISIONING_QUERY_RESPONSE_TAG
    {
        void** response_arr;
        size_t repsonse_arr_size;
    } PROVISIONING_QUERY_RESPONSE;

    MOCKABLE_FUNCTION(, const char*, querySpecification_serializeToJson, PROVISIONING_QUERY_SPECIFICATION*, query_spec);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PROVISIONING_SC_QUERY_H */
