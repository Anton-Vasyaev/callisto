# python
import os
# 3rd party
from conans import ConanFile, CMake, tools


class TestConanCallisto(ConanFile):
    name = 'TestConanCallisto'

    settings   = 'os', 'compiler', 'arch', 'build_type'
    generators = 'cmake', 'cmake_find_package_multi'

    requires        = 'gtest/1.8.1'
    default_options = 'gtest:shared=True'


    def build(self):
        cmake = CMake(self)
        cmake.definitions['CREATE_PACKAGE'] = '1'
        cmake.configure()
        cmake.build()


    def imports(self):
        self.copy('*.so',    dst='bin', src='lib')
        self.copy('*.dll',   dst='bin', src='bin')
        self.copy('*.dylib', dst='bin', src='lib')


    def test(self):
        if not tools.cross_building(self.settings):
            bin_path = os.path.join('bin', 'callisto_test')
            self.run(bin_path, run_environment=True)
