cmake_minimum_required(VERSION 3.16)

project(Racing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib 5.5 REQUIRED)

add_executable(Racing main.cpp
    Backend/IBackend.h
    Backend/raylib_backend.h Backend/raylib_backend.cpp
    car.h car.cpp
    level.h
    levelutil.h levelutil.cpp
    renderer.h renderer.cpp )
target_link_libraries(${PROJECT_NAME} raylib)

include(GNUInstallDirs)
install(TARGETS Racing
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
