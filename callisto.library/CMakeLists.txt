cmake_minimum_required(VERSION 3.19)

# configure project ***************************************************************************************************
project(callisto.library)

option(CALLISTO_SHARED "Build the shared library" OFF)
option(CALLISTO_MATH_ENABLE "Build callisto.math" ON)
option(CALLISTO_OPENCV_ENABLE "Build callisto.opencv" ON)
option(CALLISTO_GRAPHICS_ENABLE "Build callisto.graphics" ON)

set(CMAKE_CXX_STANDARD 20)

if(CALLISTO_SHARED)
    set(LIBRARY_TYPE SHARED)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else()
    set(LIBRARY_TYPE STATIC)
endif()

if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
elseif(GCC)
endif()

# configure conan and 3rdparty libaries *******************************************************************************
set(CONAN_DIR "")

# TODO
message("!!!!!!!!!!!!!!!!!!!!!!!!!!!CREATE PACKAGE OPTIONS:${CREATE_PACKAGE}")
message(${CMAKE_BINARY_DIR}/generators)

if(DEFINED CREATE_PACKAGE)
    set(CONAN_DIR ${CMAKE_BINARY_DIR}/generators)
else()
    set(CONAN_DIR ${CMAKE_CURRENT_LIST_DIR}/../.main_cache/conan/x64/${CMAKE_BUILD_TYPE})
endif()
set(CMAKE_PREFIX_PATH ${CONAN_DIR})
set(CMAKE_MODULE_PATH ${CONAN_DIR})

# find libraries
find_package(cpuid)
find_package(Boost PATHS ${CONAN_DIR})
find_package(nameof PATHS ${CONAN_DIR})

if(CALLISTO_OPENCV_ENABLE)
    find_package(OpenCV PATHS ${CONAN_DIR})
endif()

if(CALLISTO_GRAPHICS_ENABLE)
    find_package(Freetype PATHS ${CONAN_DIR})
    find_package(GLEW)
    find_package(glfw3)
    find_package(imgui)
    find_package(glm)
endif()


# configure targets ***************************************************************************************************

# callisto.framework
set(FRAMEWORK_TARGET callisto_framework)
file(GLOB_RECURSE CALLISTO_FRAMEWORK_SRC "callisto.framework/src/*.c" "callisto.framework/src/*.cpp")
add_library(${FRAMEWORK_TARGET} ${LIBRARY_TYPE} ${CALLISTO_FRAMEWORK_SRC})

target_include_directories(${FRAMEWORK_TARGET} PUBLIC  callisto.framework/include)
target_include_directories(${FRAMEWORK_TARGET} PRIVATE callisto.framework/src)


target_link_libraries(${FRAMEWORK_TARGET} PRIVATE cpuid::cpuid)
target_link_libraries(${FRAMEWORK_TARGET} PUBLIC  Boost::exception)

# callisto.math
if(CALLISTO_MATH_ENABLE)
    set(MATH_TARGET callisto_math)
    file(GLOB_RECURSE CALLISTO_MATH_SRC "callisto.math/src/*.c" "callisto.math/src/*.cpp")
    add_library(${MATH_TARGET} ${LIBRARY_TYPE} ${CALLISTO_MATH_SRC})

    target_include_directories(${MATH_TARGET} PUBLIC  callisto.math/include)
    target_include_directories(${MATH_TARGET} PRIVATE callisto.math/src)


    target_link_libraries(${MATH_TARGET} PUBLIC callisto_framework)
endif()

# callisto.opencv
if(CALLISTO_OPENCV_ENABLE)
    set(OPENCV_TARGET callisto_opencv)
    file(GLOB_RECURSE CALLISTO_OPENCV_SRC "callisto.opencv/src/*.c" "callisto.opencv/src/*.cpp")
    add_library(${OPENCV_TARGET} ${LIBRARY_TYPE} ${CALLISTO_OPENCV_SRC})

    target_include_directories(${OPENCV_TARGET} PUBLIC  callisto.opencv/include)
    target_include_directories(${OPENCV_TARGET} PRIVATE callisto.opencv/src)

    target_link_libraries(${OPENCV_TARGET} PUBLIC callisto_framework)
    target_link_libraries(${OPENCV_TARGET} PUBLIC callisto_math)

    target_link_libraries(${OPENCV_TARGET} PUBLIC opencv::opencv)
    target_link_libraries(${OPENCV_TARGET} PUBLIC Boost::filesystem)
endif()

# callisto.graphics
if(CALLISTO_GRAPHICS_ENABLE)
    set(GRAPHICS_TARGET callisto_graphics)
    file(GLOB_RECURSE CALLISTO_GRAPHICS_SRC "callisto.graphics/src/*.c" "callisto.graphics/src/*.cpp")
    add_library(${GRAPHICS_TARGET} ${LIBRARY_TYPE} ${CALLISTO_GRAPHICS_SRC})

    target_include_directories(${GRAPHICS_TARGET} PUBLIC  callisto.graphics/include)
    target_include_directories(${GRAPHICS_TARGET} PRIVATE callisto.graphics/src)

    target_link_libraries(${GRAPHICS_TARGET} PUBLIC callisto_framework)
    target_link_libraries(${GRAPHICS_TARGET} PUBLIC callisto_math)
    target_link_libraries(${GRAPHICS_TARGET} PUBLIC callisto_opencv)

    target_link_libraries(${GRAPHICS_TARGET} PUBLIC Freetype::Freetype)
    target_link_libraries(${GRAPHICS_TARGET} PUBLIC nameof::nameof)
    target_link_libraries(${GRAPHICS_TARGET} PUBLIC Boost::headers)

    if(CALLISTO_SHARED)
        target_link_libraries(${GRAPHICS_TARGET} PUBLIC GLEW::GLEW)
    else()
        target_link_libraries(${GRAPHICS_TARGET} PUBLIC GLEW::GLEW)
    endif()

    target_link_libraries(${GRAPHICS_TARGET} PUBLIC glfw)
    target_link_libraries(${GRAPHICS_TARGET} PUBLIC imgui::imgui)
    target_link_libraries(${GRAPHICS_TARGET} PUBLIC glm::glm)
endif()