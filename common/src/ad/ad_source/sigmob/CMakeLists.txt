project(sigmob_source)

file(GLOB
     oneten_src_sigmob_source
     *.m
     *.h)

add_library(${PROJECT_NAME} STATIC ${oneten_src_sigmob_source})

set(TENON_SDK_BUNDLE_ID "")
string(CONCAT TENON_SDK_BUNDLE_ID ${SDK_BUNDLE_ID_PREFIX} ${PRO_NAME_LOWER_CASE} ".sdk.sigmob")
apple_framework_generate(${PROJECT_NAME} ${TENON_SDK_BUNDLE_ID} ${PROJECT_NAME} "")
