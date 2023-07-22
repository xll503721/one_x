project(${SDK_AD_LIB})

file(GLOB
     oneten_src_ad_h
     *.h)

file(GLOB
     oneten_src_ad_source
     *.cc)

if(OSX OR IOS)
    file(GLOB
        oneten_src_ad_source_mm
        *.mm
        *.m)
    list(APPEND oneten_src_ad_source ${oneten_src_ad_h} ${oneten_src_ad_source_mm})
endif()

add_library(${PROJECT_NAME} STATIC ${oneten_src_ad_source})
if(${CMAKE_VERSION} VERSION_GREATER "3.16.0")
    target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${SRC_ROOT}/pch.h>")
endif()

include_directories(../)
include_directories(../../../../base/src)
include_directories(../../../../base/thirdparty)

add_subdirectory(model)
add_subdirectory(service)
add_subdirectory(loader)
add_subdirectory(entity)
add_subdirectory(util)
