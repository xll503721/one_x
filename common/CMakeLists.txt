cmake_minimum_required(VERSION 3.24)

project(SDKCommon)

set(CMAKE_CXX_STANDARD 17)
set(SDK_NAME_LOWER_CASE "oneten")
set(SDK_NAME_UPPER_CASE "OneTen")
set(SDK_BUNDLE_ID_PREFIX "cn.gz.ch")

set(SDK_AD_LIB "")
string(CONCAT SDK_AD_LIB ${SDK_NAME_LOWER_CASE} "_ad")

set(SDK_AD_MODEL_LIB "")
string(CONCAT SDK_AD_MODEL_LIB ${SDK_NAME_LOWER_CASE} "_ad_model")

set(SDK_AD_ENTITY_LIB "")
string(CONCAT SDK_AD_ENTITY_LIB ${SDK_NAME_LOWER_CASE} "_ad_entity")

set(SDK_AD_SERVICE_LIB "")
string(CONCAT SDK_AD_SERVICE_LIB ${SDK_NAME_LOWER_CASE} "_ad_service")

set(SDK_AD_LOADER_LIB "")
string(CONCAT SDK_AD_LOADER_LIB ${SDK_NAME_LOWER_CASE} "_ad_loader")

set(SDK_AD_SOURCE "")
string(CONCAT SDK_AD_SOURCE ${SDK_NAME_LOWER_CASE} "_ad_source")

set(SDK_AD_UTIL "")
string(CONCAT SDK_AD_UTIL ${SDK_NAME_LOWER_CASE} "_util")

set(SRC_ROOT ${PROJECT_SOURCE_DIR}/src)
set(BASE_ROOT ${PROJECT_SOURCE_DIR}/../../base/src)

if(IOS)
    set(PLATFORM iOS)
    set(ONETEN_SDK "OneTenSDK")
    add_definitions(-D OS_IOS)
elseif(OSX)
    set(PLATFORM Mac)
    set(ONETEN_SDK "OneTenSDK")
    add_definitions(-D OS_MAX)
elseif(ANDROID)
    set(PLATFORM Android)
    add_definitions(-D OS_ANDROID)
endif()

macro(target_exclude_from_all_if_exist targets)
  foreach(target ${targets})
    if(TARGET ${target})
      set_target_properties(${target} PROPERTIES EXCLUDE_FROM_ALL TRUE EXCLUDE_FROM_DEFAULT_BUILD TRUE)
    endif()
  endforeach()
endmacro()

macro(apple_framework_generate target_name identifier product_name resource_files)
  if(IOS OR OSX)
    set_xcode_property(${target_name} MACOSX_FRAMEWORK_IDENTIFIER "${identifier}")
    set_xcode_property(${target_name} MACOSX_FRAMEWORK_BUNDLE_VERSION "1")
    set_xcode_property(${target_name} MACOSX_FRAMEWORK_SHORT_VERSION_STRING "0.0.1")
    set_xcode_property(${target_name} FRAMEWORK TRUE)
    set_xcode_property(${target_name} FRAMEWORK_VERSION A)
    set_xcode_property(${target_name} XCODE_ATTRIBUTE_PRODUCT_NAME "${product_name}")
    set_xcode_attr_property(${target_name} CLANG_ENABLE_OBJC_ARC "YES")
    set_xcode_attr_property(${target_name} ENABLE_BITCODE "NO")
    set_xcode_attr_property(${target_name} DEFINES_MODULE "YES")
    set_xcode_attr_property(${target_name} DYLIB_INSTALL_NAME_BASE "@rpath")
    set_xcode_attr_property(${target_name} LD_RUNPATH_SEARCH_PATHS "@executable_path/../Frameworks @loader_path/Frameworks")
    if(NOT ("${resource_files}" STREQUAL ""))
      set_source_files_properties(${resource_files} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    endif()
    if(OSX)
      set(CMAKE_OSX_DEPLOYMENT_TARGET "10.11" CACHE STRING "Minimum OS X deployment version" FORCE)
    elseif(IOS)
      set_xcode_attr_property(${target_name} CLANG_DEBUG_INFORMATION_LEVEL[variant=Release] "line-tables-only")
    endif()
  endif()
endmacro()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
macro(set_target_folder_if_exist target folder)
  if(TARGET ${target})
    set_target_properties(${target} PROPERTIES FOLDER ${folder})
  endif()
endmacro()

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/${PLATFORM})
SET(LIBRARY_BASE_OUTPUT_PATH ${BASE_ROOT}/output/${PLATFORM})

add_subdirectory(${BASE_ROOT} base.src)

add_subdirectory(src)

execute_process(COMMAND sh ${app_repo_path}/tool/wemeet_install.js)

