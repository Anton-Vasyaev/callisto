cmake_minimum_required(VERSION 3.19)

# configure project *******************************************************************************
project(callisto.test CXX)

option(CALLISTO_SHARED "Build the shared library" OFF)

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD     20)

if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
elseif(GCC)
endif()

# conan settings **********************************************************************************
set(CONAN_DIR "")
if(DEFINED CREATE_PACKAGE)
    set(CONAN_DIR ${CMAKE_BINARY_DIR})
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    set(CONAN_DIR ${CMAKE_SOURCE_DIR}/../.main_cache/conan/x64/${CMAKE_BUILD_TYPE})
    set(CMAKE_PREFIX_PATH ${CONAN_DIR})
    set(CMAKE_MODULE_PATH ${CONAN_DIR})
endif()

message("CONAN DIR:${CONAN_DIR}")


# collect source and linked libraries to executable file ******************************************
set(TEST_TARGET callisto_test)
file(GLOB_RECURSE TEST_SRC "src/*.c" "src/*.cpp")
add_executable(${TEST_TARGET} ${TEST_SRC})
target_include_directories(${TEST_TARGET} PRIVATE src)


# 3rd party 
find_package(Boost PATHS ${CONAN_DIR})
find_package(GTest PATHS ${CONAN_DIR})
target_link_libraries(${TEST_TARGET} PRIVATE GTest::gtest)

# link with callisto
if(NOT DEFINED CREATE_PACKAGE)
    add_subdirectory(
        ${CMAKE_SOURCE_DIR}/../callisto.library
        ${CMAKE_CURRENT_BINARY_DIR}/callisto.library
    )

    macro(link_local lib_name)
        target_link_libraries(${TEST_TARGET} PRIVATE callisto_${lib_name})

        if(WIN32)
            add_custom_command(
                TARGET ${TEST_TARGET} POST_BUILD
                COMMAND ${CMAKE_COMMAND} 
                -E copy_if_different 
                $<TARGET_FILE:callisto_${lib_name}> 
                $<TARGET_FILE_DIR:${TEST_TARGET}>
            )
        endif()
    endmacro()

    set(TEST_PACKAGE_LINK_LIBRARIES framework math opencv graphics)
    foreach(lib_name1 ${TEST_PACKAGE_LINK_LIBRARIES})
        link_local(${lib_name1})
    endforeach()
else()
    find_package(Callisto)
    target_link_libraries(${TEST_TARGET} PRIVATE Callisto::framework)
    target_link_libraries(${TEST_TARGET} PRIVATE Callisto::math)
    target_link_libraries(${TEST_TARGET} PRIVATE Callisto::opencv)
    target_link_libraries(${TEST_TARGET} PRIVATE Callisto::graphics)
endif()


# copy dlls if platform is windows ****************************************************************
if(WIN32)
    file(GLOB BINARY_SHARED_LIBRARIES "${CONAN_DIR}/bin/*.dll")
    foreach(BINARY_SHARED_LIBRARY IN LISTS BINARY_SHARED_LIBRARIES)
        add_custom_command(
            TARGET ${TEST_TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} 
            -E copy_if_different 
            ${BINARY_SHARED_LIBRARY}
            $<TARGET_FILE_DIR:${TEST_TARGET}>
        )
    endforeach()
endif()