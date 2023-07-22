project(${SDK_AD_MODEL_LIB})

file(GLOB
     sdk_ad_src_model_source
     *.cc
     *.h
     ./entity/*.cc
     ./entity/*.h)

add_library(${PROJECT_NAME} STATIC ${sdk_ad_src_model_source})
if(${CMAKE_VERSION} VERSION_GREATER "3.16.0")
    target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${SRC_ROOT}/pch.h>")
endif()

include_directories(../../)