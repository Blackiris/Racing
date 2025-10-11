from conan import ConanFile
from conan.tools.cmake import cmake_layout

class MyProjectConan(ConanFile):
    name = "racing"
    version = "0.1"
    settings = "os", "arch", "compiler", "build_type"

    requires = "raylib/5.5"
    test_requires = "gtest/1.17.0"

    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        cmake_layout(self)
