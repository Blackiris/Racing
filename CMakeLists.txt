cmake_minimum_required(VERSION 3.16)

project(Racing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib 5.5 REQUIRED)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_subdirectory(src/racing_lib)

add_executable(Racing src/main.cpp
    src/Backend/raylib_backend.h src/Backend/raylib_backend.cpp
     )
target_link_libraries(${PROJECT_NAME} raylib racing_lib)

include(GNUInstallDirs)
install(TARGETS Racing
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
