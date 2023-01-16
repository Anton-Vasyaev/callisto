cmake_minimum_required(VERSION 3.19)

# configure project *******************************************************************************
project(callisto.graphics)
set(TARGET_NAME callisto_graphics)

option(CALLISTO_GRAPHICS_SHARED "Build the shared library" ON)

set(CMAKE_CXX_STANDARD 20)

if(CALLISTO_GRAPHICS_SHARED)
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
file(GLOB_RECURSE TARGET_SRC "src/*.c" "src/*.cpp")
add_library(${TARGET_NAME} ${LIBRARY_TYPE} ${TARGET_SRC})
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

# callisto.math
if(NOT TARGET callisto_math)
add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/../callisto.math
    ${CMAKE_CURRENT_BINARY_DIR}/callisto.math
)
endif()
target_link_libraries(${TARGET_NAME} PUBLIC callisto_math)

# callisto.opencv
if(NOT TARGET callisto_opencv)
add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/../callisto.opencv
    ${CMAKE_CURRENT_BINARY_DIR}/callisto.opencv
)
endif()
target_link_libraries(${TARGET_NAME} PUBLIC callisto_opencv)

# Conan
find_package(Freetype PATHS ${CONAN_DIR})
find_package(nameof PATHS ${CONAN_DIR})
find_package(Boost PATHS ${CONAN_DIR})
find_package(GLEW)
find_package(glfw3)
find_package(imgui)
find_package(glm)


target_link_libraries(${TARGET_NAME} PUBLIC Freetype::Freetype)
target_link_libraries(${TARGET_NAME} PUBLIC nameof::nameof)
target_link_libraries(${TARGET_NAME} PUBLIC Boost::headers)
target_link_libraries(${TARGET_NAME} PUBLIC GLEW::glew)
target_link_libraries(${TARGET_NAME} PUBLIC glfw::glfw)
target_link_libraries(${TARGET_NAME} PUBLIC imgui::imgui)
target_link_libraries(${TARGET_NAME} PUBLIC glm::glm)