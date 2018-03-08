// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef PROVISIONING_SC_BULK_OPERATION_H
#define PROVISIONING_SC_BULK_OPERATION_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <stdint.h>

#include "azure_c_shared_utility/umock_c_prod.h"
#include "azure_c_shared_utility/macro_utils.h"
#include "parson.h"

#define PROVISIONING_BULK_OPERATION_VERSION_1 (int)1

#define PROVISIONING_BULK_OPERATION_MODE_VALUES \
BULK_OP_CREATE, \
BULK_OP_UPDATE, \
BULK_OP_UPDATE_IF_MATCH_ETAG, \
BULK_OP_DELETE

DEFINE_ENUM(PROVISIONING_BULK_OPERATION_MODE, PROVISIONING_BULK_OPERATION_MODE_VALUES);

#define PROVISIONING_BULK_OPERATION_TYPE_VALUES \
BULK_OP_INDIVIDUAL_ENROLLMENT

DEFINE_ENUM(PROVISIONING_BULK_OPERATION_TYPE, PROVISIONING_BULK_OPERATION_TYPE_VALUES);

typedef struct PROVISIONING_BULK_OPERATION_ERROR_TAG
{
    char* registration_id;
    int32_t error_code;
    char* error_status;
} PROVISIONING_BULK_OPERATION_ERROR;

typedef struct PROVISIONING_BULK_OPERATION_RESULT_TAG
{
    bool is_successful;
    PROVISIONING_BULK_OPERATION_ERROR** errors; //array
    size_t num_errors;
} PROVISIONING_BULK_OPERATION_RESULT;

typedef struct PROVISIONING_BULK_OPERATION_TAG
{
    int version;
    PROVISIONING_BULK_OPERATION_MODE mode;
    void** enrollments;
    size_t num_enrollments;
    PROVISIONING_BULK_OPERATION_TYPE type;
} PROVISIONING_BULK_OPERATION;


MOCKABLE_FUNCTION(, void, bulkOperationResult_free, PROVISIONING_BULK_OPERATION_RESULT*, bulk_op_result);

/* ---INTERNAL USAGE ONLY--- */
MOCKABLE_FUNCTION(, PROVISIONING_BULK_OPERATION_ERROR*, bulkOperationError_fromJson, JSON_Object*, root_object);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PROVISIONING_SC_BULK_OPERATION_H */
