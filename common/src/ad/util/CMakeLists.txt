project(${SDK_AD_UTIL})

file(GLOB
     sdk_ad_src_util_source
     *.cc
     *.h)

if(OSX OR IOS)
    file(GLOB
        sdk_ad_src_util_source_mm
        *.mm
        *.m)
    list(APPEND sdk_ad_src_util_source ${sdk_ad_src_util_source_mm})
endif()

add_library(${PROJECT_NAME} STATIC ${sdk_ad_src_util_source})
if(${CMAKE_VERSION} VERSION_GREATER "3.16.0")
    target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${SRC_ROOT}/pch.h>")
endif()