cmake_minimum_required(VERSION 3.19)

# configure project *******************************************************************************
project(callisto.math)
set(TARGET_NAME callisto_math)

option(CALLISTO_SHARED "Build the shared library" ON)

set(CMAKE_CXX_STANDARD 20)

if(CALLISTO_SHARED)
    set(LIBRARY_TYPE SHARED)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else()
    set(LIBRARY_TYPE STATIC)
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()


# collects source to target ***********************************************************************
file(GLOB_RECURSE CALLISTO_MATH_SRC "src/*.c" "src/*.cpp")
add_library(${TARGET_NAME} ${LIBRARY_TYPE} ${CALLISTO_MATH_SRC})
target_include_directories(${TARGET_NAME} PUBLIC  include)
target_include_directories(${TARGET_NAME} PRIVATE src)


# Dependencies

# callisto.framework
if(NOT TARGET callisto_framework)
    add_subdirectory(
        ${CMAKE_CURRENT_LIST_DIR}/../callisto.framework 
        ${CMAKE_CURRENT_BINARY_DIR}/callisto.framework
    )
endif()

target_link_libraries(${TARGET_NAME} PUBLIC callisto_framework)