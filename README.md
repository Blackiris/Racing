# Old-school racing game

# Goal
Finish the race as fast as possible. Bumping on other cars or driving on grass will make you slower.

# How to build
On root,

conan install . --output-folder=build --build=missing

    cd build/build/Release/generators
    cmake ../../../.. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
    cmake --build .

# How to play
UP - Accelerate
DOWN - Brake
LEFT - Turn left
RIGHT - Turn right