conan install . --build=missing

cd build/Release/generators
cmake ../../../.. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
