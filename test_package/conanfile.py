# python
import os
from os.path import join
# 3rd party
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.build import can_run

class TestConanCallisto(ConanFile):
    settings   = 'os', 'compiler', 'arch', 'build_type'

    generators = "CMakeDeps", "VirtualRunEnv"

    test_type = "explicit"


    def __get_option_from_bool(self, flag : bool) -> str:
        return "ON" if flag else "OFF"


    def requirements(self):
        self.requires(self.tested_reference_str)
        self.requires('gtest/1.8.1')


    def layout(self):
        cmake_layout(self) #, build_folder='test_package.build')


    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables['CREATE_PACKAGE'] = '1'
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure() #(variables={'CREATE_PACKAGE' : '1'})
        cmake.build()

    '''
    def imports(self):
        if self.options['callisto'].shared:
            copy(self, '*.so',    dst='bin', src='lib')
            copy(self, '*.dll',   dst='bin', src='bin')
            copy(self, '*.dylib', dst='bin', src='lib')
    '''

    def test(self):
        if can_run(self):
            bin_path = join(self.cpp.build.bindir, 'callisto_test')

            self.run(bin_path, env='conanrun')
