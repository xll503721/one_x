mkdir cmake_project
cd cmake_project
cmake .. -G Xcode -DCMAKE_TOOLCHAIN_FILE=../ios/ios.cmake -DPLATFORM=OS
