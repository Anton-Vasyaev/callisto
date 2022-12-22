cmake_minimum_required(VERSION 3.19)

# configure project *******************************************************************************
project(callisto.opencv)
set(TARGET_NAME callisto_opencv)

option(CALLISTO_OPENCV_SHARED "Build the shared library" ON)

set(CMAKE_CXX_STANDARD 20)

if(CALLISTO_OPENCV_SHARED)
    set(LIBRARY_TYPE SHARED)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else()
    set(LIBRARY_TYPE STATIC)
endif()


# conan settings **********************************************************************************
set(CONAN_DIR "")
if(DEFINED CREATE_PACKAGE)
    set(CONAN_DIR ${CMAKE_BINARY_DIR}/..)
    message($"CONAN CREATE CONAN DIR:${CONAN_DIR}")
else()
    set(CONAN_DIR ${CMAKE_SOURCE_DIR}/../.main_cache/conan/x64/${CMAKE_BUILD_TYPE})
endif()
set(CMAKE_PREFIX_PATH ${CONAN_DIR})
set(CMAKE_MODULE_PATH ${CONAN_DIR})


# collects source to target ***********************************************************************
file(GLOB_RECURSE CALLISTO_OPENCV_SRC "src/*.c" "src/*.cpp")
add_library(${TARGET_NAME} ${LIBRARY_TYPE} ${CALLISTO_OPENCV_SRC})
target_include_directories(${TARGET_NAME} PUBLIC  include)
target_include_directories(${TARGET_NAME} PRIVATE src)


# Dependencies

# callisto.framework
if(NOT TARGET callisto_framework)
    add_subdirectory(
        ${CMAKE_SOURCE_DIR}/../callisto.framework 
        ${CMAKE_CURRENT_BINARY_DIR}/callisto.framework
    )
endif()
target_link_libraries(${TARGET_NAME} PUBLIC callisto_framework)

# callisto.math
if(NOT TARGET callisto_math)
add_subdirectory(
    ${CMAKE_SOURCE_DIR}/../callisto.math
    ${CMAKE_CURRENT_BINARY_DIR}/callisto.math
)
endif()
target_link_libraries(${TARGET_NAME} PUBLIC callisto_math)

# Conan
find_package(cpuid)
find_package(Boost)
find_package(opencv)

target_link_libraries(${TARGET_NAME} PUBLIC opencv::opencv)
target_link_libraries(${TARGET_NAME} PUBLIC Boost::filesystem)