from conans import ConanFile, CMake


class CallistoConan(ConanFile):
    name = 'callisto'
    version = '0.1.0'
    license = 'BSD'
    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'cmake', 'cmake_find_package_multi'
    exports = '*'

    options = {
        'shared': [True, False]
    }

    default_options = {
        'shared': True
    }

    libraries = [
        'framework',
        'math',
        'opencv'
    ]


    def requirements(self):
        self.requires('zlib/1.2.12', override=True)
        self.requires('libcpuid/0.5.1')
        self.requires('boost/1.71.0')
        self.requires('opencv/4.5.3')


    def configure(self):
        self.options['zlib'].shared     = self.options.shared
        self.options['boost'].shared    = self.options.shared
        self.options['libcpuid'].shared = self.options.shared
        self.options['opencv'].shared   = self.options.shared


    def build(self):
        for lib in self.libraries:
            cmake = CMake(self)
            cmake.definitions[f'CALLISTO_{lib.upper()}_SHARED'] = self.options.shared
            cmake.definitions['CREATE_PACKAGE'] = '1'
            cmake.configure(source_folder=f'callisto.{lib}', build_folder=f'callisto.{lib}.build')
            cmake.build()


    def package(self):
        for lib in self.libraries:
            self.copy(f'*h',   dst=f'include/callisto_{lib}_headers', src=f'callisto.{lib}/include')
            self.copy(f'*hpp', dst=f'include/callisto_{lib}_headers', src=f'callisto.{lib}/include')

        self.copy('*callisto_*.lib',   dst='lib', keep_path=False)
        self.copy('*callisto_*.a',     dst='lib', keep_path=False)
        self.copy('*callisto_*.dll',   dst='bin', keep_path=False)
        self.copy('*callisto_*.so',    dst='lib', keep_path=False)
        self.copy('*callisto_*.dylib', dst='lib', keep_path=False)


    def package_info(self):
        self.cpp_info.names['cmake_find_package'] = 'Callisto'
        self.cpp_info.names['cmake_find_package_multi'] = 'Callisto'

        for lib in self.libraries:
            self.cpp_info.components[lib].names['cmake_find_package'] = lib
            self.cpp_info.components[lib].libs = [f'callisto_{lib}']
            self.cpp_info.components[lib].includedirs = [f'include/callisto_{lib}_headers']

        # framework
        self.cpp_info.components['framework'].requires = [
            'boost::exception',
            'libcpuid::libcpuid'
        ]

        # math
        self.cpp_info.components['math'].requires = ['framework']

        # opencv
        self.cpp_info.components['opencv'].requires = [
            'boost::filesystem',
            'opencv::opencv',
            'framework',
            'math'
        ]
