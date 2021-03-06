#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

#this is CMakeLists for provisioning_service_client

if(NOT ${use_http})
    message("provisioning service client needs HTTP support - use_http option was ${use_http}")
    return()
endif()

compileAsC99()

set(provisioning_service_client_c_files
./src/provisioning_sc_attestation_mechanism.c
./src/provisioning_sc_bulk_operation.c
./src/provisioning_sc_device_registration_state.c
./src/provisioning_sc_enrollment.c
./src/provisioning_sc_query.c
./src/provisioning_sc_shared_helpers.c
./src/provisioning_sc_tpm_attestation.c
./src/provisioning_sc_twin.c
./src/provisioning_sc_x509_attestation.c
./src/provisioning_service_client.c
../deps/parson/parson.c
)

set(provisioning_service_client_h_files
./inc/provisioning_sc_attestation_mechanism.h
./inc/provisioning_sc_bulk_operation.h
./inc/provisioning_sc_device_registration_state.h
./inc/provisioning_sc_enrollment.h
./inc/provisioning_sc_json_const.h
./inc/provisioning_sc_models.h
./inc/provisioning_sc_models_serializer.h
./inc/provisioning_sc_query.h
./inc/provisioning_sc_shared_helpers.h
./inc/provisioning_sc_tpm_attestation.h
./inc/provisioning_sc_twin.h
./inc/provisioning_sc_x509_attestation.h
./inc/provisioning_service_client.h
../deps/parson/parson.h
)

if(MSVC)
set_source_files_properties(../deps/parson/parson.c PROPERTIES COMPILE_FLAGS "/wd4244 /wd4232")
endif()

include_directories(${SHARED_UTIL_INC_FOLDER})
include_directories(${UHTTP_C_INC_FOLDER})
include_directories(${CMAKE_CURRENT_LIST_DIR}/../deps/parson)

set(PROVISIONING_SERVICE_CLIENT_INC_FOLDER ${CMAKE_CURRENT_LIST_DIR}/inc CACHE INTERNAL "This is the include folder for provisioning_service_client" FORCE)

include_directories(${PROVISIONING_SERVICE_CLIENT_INC_FOLDER})
include_directories(${DEV_AUTH_MODULES_CLIENT_INC_FOLDER})

IF(WIN32)
    #windows needs this define
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-DGB_MEASURE_MEMORY_FOR_THIS -DGB_DEBUG_ALLOC)
ENDIF(WIN32)

if (${build_as_dynamic})
    add_library(provisioning_service_client SHARED ${provisioning_service_client_c_files} ${provisioning_service_client_h_files} ./src/provisioning_service_client_dll.def)
    linkSharedUtil(provisioning_service_client)

else()
    add_library(provisioning_service_client ${provisioning_service_client_c_files} ${provisioning_service_client_h_files})
endif()

target_link_libraries(provisioning_service_client)

if (NOT ${ARCHITECTURE} STREQUAL "ARM")
    if (NOT ${skip_samples})
    add_subdirectory(samples)
    endif()
endif()

if(NOT IN_OPENWRT)
    # Disable tests for OpenWRT
    if(${run_unittests})
        add_subdirectory(tests)
    endif()
endif()