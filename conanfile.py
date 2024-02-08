# python
from os.path import join

from dataclasses import dataclass, field
from typing import Dict, List, Tuple, Any

# conan
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import copy


@dataclass
class RequireData:
    name : str

    resolve_str : str

    transitive_headers : bool = field(default=False)

    transitive_libs : bool = field(default=True)


@dataclass
class LibraryNode:
    name : str
    
    dependencies : List[str]
    
    requires : List[str]


class DependencyGraph:
    libraries : Dict[str, LibraryNode]

    requires : Dict[str, RequireData]


    def __init__(self):
        self.libraries = dict()
        self.requires  = dict()


    def append_library(
        self,
        name         : str,
        dependencies : List[str],
        requires     : List[str]
    ):
        if name in self.libraries:
            raise Exception(f'library already appended:{name}')

        # Check and append dependency
        for dependency in dependencies:
            if not dependency in self.libraries:
                raise Exception(f'Cannot resolve dependency:{dependency}')

        # Check requires
        for require in requires:
            require_name = require.split(':')[0]

            if not require_name in [r.name for r in self.requires.values()]:
                raise Exception(f'Cannot resolve require library:{require_name}')

        node = LibraryNode(name, dependencies, requires)

        self.libraries[name] = node


    def append_require(
        self,
        name               : str,
        resolve_str        : str,
        transitive_headers : bool = False,
        transitive_libs    : bool = True
    ):
        if name in self.requires:
            raise Exception(f'requires already appended:{name}')

        self.requires[name] = RequireData(
            name, 
            resolve_str, 
            transitive_headers,
            transitive_libs
        )


    def disable_library(self, name : str):
        if not name in self.libraries:
            raise Exception(f'library not exist:{name}')

        del self.libraries[name]


    def __has_full_dependency_path(self, node : LibraryNode) -> bool:
        for dependency in node.dependencies:
            if not dependency in self.libraries:
                return False

            dependency_node = self.libraries[dependency]

            dependency_path_status = self.__has_full_dependency_path(dependency_node)
            if not dependency_path_status:
                return False

        return True


    def form_libraries(self) -> List[LibraryNode]:
        nodes : List[LibraryNode] = list()
        
        for lib_name, lib_node in self.libraries.items():
            if self.__has_full_dependency_path(lib_node):
                nodes.append(lib_node)

        return nodes


    def form_requires(self) -> List[RequireData]:
        build_requires : Dict[str, RequireData] = dict()

        for lib_name, lib_node in self.libraries.items():
            if self.__has_full_dependency_path(lib_node):
                for require_target in lib_node.requires:
                    require_name = require_target.split(':')[0]

                    build_requires[require_name] = self.requires[require_name]

        return list(build_requires.values())


class CallistoConan(ConanFile):
    dependency_graph : DependencyGraph

    name = 'callisto'
    version = '0.3.2'
    license = 'BSD'
    package_typ='library'
    settings = 'os', 'compiler', 'build_type', 'arch'
    
    generators = "CMakeDeps", "PkgConfigDeps", "VirtualBuildEnv"

    exports_sources = '*'

    options = {
        'shared'         : [True, False],
        'build_math'     : [True, False],
        'build_opencv'   : [True, False],
        'build_graphics' : [True, False]
    }

    default_options = {
        'shared': False,

        'build_math':     True,
        'build_opencv':   True,
        'build_graphics': True
    }


    def __get_option_from_bool(self, flag : bool) -> str:
        return "ON" if flag else "OFF"

    
    def config_options(self):
        self.dependency_graph = DependencyGraph()
        
        # Append 3rd party requires
        self.dependency_graph.append_require(
            'libcpuid', 
            'libcpuid/0.5.1'
        )

        self.dependency_graph.append_require(
            'nameof', 
            'nameof/0.10.1', 
            transitive_headers=True
        )
        self.dependency_graph.append_require(
            'boost',    
            'boost/1.71.0', 
            transitive_headers=True,
        )
        self.dependency_graph.append_require(
            'opencv',   
            'opencv/4.5.3',    
            transitive_headers=True,
        )
        self.dependency_graph.append_require(
            'freetype', 'freetype/2.13.0', 
            transitive_headers=True,
        )
        self.dependency_graph.append_require(
            'glfw',     
            'glfw/3.3.2',      
            transitive_headers=True,
        )
        self.dependency_graph.append_require(
            'glew',     
            'glew/2.1.0',      
            transitive_headers=True,
        )
        self.dependency_graph.append_require(
            'glm',      
            'glm/0.9.9.5',     
            transitive_headers=True
        )
        self.dependency_graph.append_require(
            'imgui',    
            'imgui/1.90.1',    
            transitive_headers=True
        )

        # Append libraries with dependencies-------------------------------------------------------
        
        # framework
        self.dependency_graph.append_library(
            'framework', 
            [], 
            ['boost::exception', 'libcpuid::libcpuid']
        )
        
        # math
        self.dependency_graph.append_library(
            'math', 
            ['framework'],
            []
        )
    
        # opencv
        self.dependency_graph.append_library(
            'opencv', 
            ['framework', 'math'], 
            ['boost::filesystem', 'opencv::opencv']
        )

        # graphics
        self.dependency_graph.append_library(
            'graphics',
            ['framework', 'math', 'opencv'],
            [
                'boost::headers',
                'nameof::nameof',
                'freetype::freetype', 
                'glfw::glfw', 
                'glew::glew', 
                'glm::glm', 
                'imgui::imgui'
            ]
        )


    def configure(self):
        if not self.options.build_math:
            self.dependency_graph.disable_library('math')
        
        if not self.options.build_opencv:
            self.dependency_graph.disable_library('opencv')

        if not self.options.build_graphics:
            self.dependency_graph.disable_library('graphics')

        not_shared_requires = ['glm', 'nameof']

        self.options['zlib'].shared = self.options.shared

        requires = self.dependency_graph.form_requires()

        for require in requires:
            if not require.name in not_shared_requires: 
                self.options[require.name].shared = self.options.shared


    def requirements(self):
        self.requires('zlib/1.2.12', override=True)

        requires = self.dependency_graph.form_requires()
        for require in requires:
            self.requires(
                require.resolve_str, 
                transitive_headers=require.transitive_headers,
                transitive_libs=require.transitive_libs
            )


    def layout(self):
        cmake_layout(self, src_folder=f'callisto.library', build_folder=f'callisto.library.build')


    def generate(self):
        libraries = self.dependency_graph.form_libraries()

        tc = CMakeToolchain(self)

        tc.variables[f'CALLISTO_SHARED'] = self.__get_option_from_bool(self.options.shared)
        tc.variables[f'CREATE_PACKAGE']  = '1'

        libraries_names = [lib.name for lib in libraries]

        tc.variables[f'CALLISTO_MATH_ENABLE']     = self.__get_option_from_bool('math'     in libraries_names)
        tc.variables[f'CALLISTO_OPENCV_ENABLE']   = self.__get_option_from_bool('opencv'   in libraries_names)
        tc.variables[f'CALLISTO_GRAPHICS_ENABLE'] = self.__get_option_from_bool('graphics' in libraries_names)
        tc.generate()


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


    def package(self):
        libraries = self.dependency_graph.form_libraries()

        for lib_module in libraries:
            lib_name = lib_module.name

            copy(self, f'*h',   join(self.source_folder, f'callisto.{lib_name}/include'), join(self.package_folder, f'include/callisto_{lib_name}_headers'))
            copy(self, f'*hpp', join(self.source_folder, f'callisto.{lib_name}/include'), join(self.package_folder, f'include/callisto_{lib_name}_headers'))

        copy(self, '*callisto_*.lib',   self.build_folder, join(self.package_folder, 'lib'), keep_path=False)
        copy(self, '*callisto_*.a',     self.build_folder, join(self.package_folder, 'lib'), keep_path=False)
        copy(self, '*callisto_*.dll',   self.build_folder, join(self.package_folder, 'bin'), keep_path=False)
        copy(self, '*callisto_*.so',    self.build_folder, join(self.package_folder, 'lib'), keep_path=False)
        copy(self, '*callisto_*.dylib', self.build_folder, join(self.package_folder, 'lib'), keep_path=False)


    def package_info(self):
        self.cpp_info.set_property('cmake_file_name', 'Callisto')

        self.cpp_info.names['cmake_find_package'] = 'Callisto'
        self.cpp_info.names['cmake_find_package_multi'] = 'Callisto'

        libraries = self.dependency_graph.form_libraries()

        for lib_module in libraries:
            lib_name = lib_module.name

            self.cpp_info.components[lib_name].set_property('cmake_target_name', f'Callisto::{lib_name}')
            self.cpp_info.components[lib_name].set_property("pkg_config_name", lib_name)

            self.cpp_info.components[lib_name].names['cmake_find_package']       = lib_name
            self.cpp_info.components[lib_name].names['cmake_find_package_multi'] = lib_name

            self.cpp_info.components[lib_name].libs = [f'callisto_{lib_name}']
            self.cpp_info.components[lib_name].includedirs = [f'include/callisto_{lib_name}_headers']

            requires = lib_module.dependencies + lib_module.requires

            print(f'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!requires:{requires}')
            self.cpp_info.components[lib_name].requires.extend(requires)