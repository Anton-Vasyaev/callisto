cmake_minimum_required(VERSION 3.19)

# configure project *******************************************************************************
project(callisto.framework)
set(TARGET_NAME callisto_framework)

option(CALLISTO_FRAMEWORK_SHARED "Build the shared library" ON)

set(CMAKE_CXX_STANDARD 20)

if(CALLISTO_FRAMEWORK_SHARED)
    set(LIBRARY_TYPE SHARED)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else()
    set(LIBRARY_TYPE STATIC)
endif()

# conan settings **********************************************************************************
set(CONAN_DIR "")
if(DEFINED CREATE_PACKAGE)
    set(CONAN_DIR ${CMAKE_BINARY_DIR}/..)
else()
    set(CONAN_DIR ${CMAKE_CURRENT_LIST_DIR}/../.main_cache/conan/x64/${CMAKE_BUILD_TYPE})
endif()
set(CMAKE_PREFIX_PATH ${CONAN_DIR})
set(CMAKE_MODULE_PATH ${CONAN_DIR})


# collects source to target ***********************************************************************
file(GLOB_RECURSE CALLISTO_FRAMEWORK_SRC "src/*.c" "src/*.cpp")
add_library(${TARGET_NAME} ${LIBRARY_TYPE} ${CALLISTO_FRAMEWORK_SRC})

target_include_directories(${TARGET_NAME} PUBLIC  include)
target_include_directories(${TARGET_NAME} PRIVATE src)

# linkage with other libraries
find_package(cpuid)
find_package(Boost)

target_link_libraries(${TARGET_NAME} PRIVATE cpuid::cpuid)
target_link_libraries(${TARGET_NAME} PUBLIC  Boost::exception)