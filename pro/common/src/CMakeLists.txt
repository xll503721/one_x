
set(SDK_NAME "")
string(CONCAT SDK_NAME ${SDK_NAME_UPPER_CASE} "SDK")

project(${SDK_NAME})

set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
set(CMAKE_OSX_SYSROOT "iphonesimulator")

set(AD_FRAMEWORK "")
string(CONCAT AD_FRAMEWORK ${SDK_NAME_LOWER_CASE} "_ad_sdk")

set(COMPILE_FEATURE_FRAMEWORK 1)
set(ALL_FEATURE_FRAMEWORK)

file(GLOB
     oneten_src_h
     *.h)

file(GLOB
     oneten_src_source
     *.cc
     *.m)

if(OSX OR IOS)
    file(GLOB
        oneten_src_source_mm
        *.mm)
    list(APPEND oneten_src_source ${oneten_src_source_mm})
endif()

if(${COMPILE_AD_FRAMEWORK})
    list(APPEND ${ALL_FEATURE_FRAMEWORK} ${AD_FRAMEWORK})
endif()

find_library(UIKIT UIKit)
find_library(FOUNDATION Foundation)
find_library(MOBILECORESERVICES MobileCoreServices)
find_library(CFNETWORK CFNetwork)
find_library(SYSTEMCONFIGURATION SystemConfiguration)

add_subdirectory(ad)

include_directories(./)
include_directories(ad)
include_directories(./../../../base/src)
include_directories(./../../../base/thirdparty)

add_library(${PROJECT_NAME} SHARED ${oneten_src_h} ${oneten_src_source})
add_dependencies(${PROJECT_NAME} ${SDK_AD_LIB})
add_dependencies(${PROJECT_NAME} ${SDK_AD_MODEL_LIB})
add_dependencies(${PROJECT_NAME} ${SDK_AD_SERVICE_LIB})
add_dependencies(${PROJECT_NAME} ${SDK_AD_LOADER_LIB})
add_dependencies(${PROJECT_NAME} ${SDK_AD_REPOSITORY_LIB})
add_dependencies(${PROJECT_NAME} ${SDK_AD_ENTITY_LIB})
add_dependencies(${PROJECT_NAME} ${SDK_AD_UTIL})
add_dependencies(${PROJECT_NAME} Base)

target_link_libraries(${PROJECT_NAME} 
                        ${SDK_AD_LIB} 
                        ${SDK_AD_MODEL_LIB} 
                        ${SDK_AD_SERVICE_LIB} 
                        ${SDK_AD_LOADER_LIB}
                        ${SDK_AD_REPOSITORY_LIB} 
                        ${SDK_AD_ENTITY_LIB}
                        ${SDK_AD_UTIL}
                        Base)
target_link_libraries(${PROJECT_NAME} ${UIKIT} ${FOUNDATION})

set(TENON_SDK_BUNDLE_ID "")
string(CONCAT TENON_SDK_BUNDLE_ID ${SDK_BUNDLE_ID_PREFIX} ${PRO_NAME_LOWER_CASE} ".sdk")
apple_framework_generate(${PROJECT_NAME} ${TENON_SDK_BUNDLE_ID} ${PROJECT_NAME} "")
set_xcode_property(${PROJECT_NAME} PUBLIC_HEADER "${oneten_src_h}")


if(${CMAKE_VERSION} VERSION_GREATER "3.16.0")
    target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${SRC_ROOT}/pch.h>")
endif()

set_target_folder_if_exist(${SDK_AD_LIB} ${PROJECT_NAME})
set_target_folder_if_exist(${SDK_AD_MODEL_LIB} ${PROJECT_NAME}/${SDK_AD_LIB})
set_target_folder_if_exist(${SDK_AD_SERVICE_LIB} ${PROJECT_NAME}/${SDK_AD_LIB})
set_target_folder_if_exist(${SDK_AD_LOADER_LIB} ${PROJECT_NAME}/${SDK_AD_LIB})
set_target_folder_if_exist(${SDK_AD_REPOSITORY_LIB} ${PROJECT_NAME}/${SDK_AD_LIB})
set_target_folder_if_exist(${SDK_AD_ENTITY_LIB} ${PROJECT_NAME}/${SDK_AD_LIB})
set_target_folder_if_exist(${SDK_AD_ENTITY_LIB} ${PROJECT_NAME}/${SDK_AD_LIB})
set_target_folder_if_exist(${SDK_AD_UTIL} ${PROJECT_NAME}/${SDK_AD_LIB})
