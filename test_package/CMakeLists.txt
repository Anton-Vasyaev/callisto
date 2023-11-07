cmake_minimum_required(VERSION 3.19)

#--------------------------------------------------------------------------------------------------
# list of libraries names
set(CALLISTO_LIBRARIES framework math opencv graphics)

#--------------------------------------------------------------------------------------------------
# configure project
project(callisto.test CXX)

option(CALLISTO_SHARED "Build the shared library" OFF)

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD     20)

if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
elseif(GCC)
endif()

#--------------------------------------------------------------------------------------------------
# callisto library providing and conan settings
set(CONAN_DIR "")

# CREATE_PACKAGE defined when cmake and build running from conan create command
if(DEFINED CREATE_PACKAGE)
    set(CONAN_DIR ${CMAKE_BINARY_DIR})
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    set(CONAN_DIR ${CMAKE_SOURCE_DIR}/../.main_cache/conan/x64/${CMAKE_BUILD_TYPE})
endif()

set(CMAKE_PREFIX_PATH ${CONAN_DIR})
set(CMAKE_MODULE_PATH ${CONAN_DIR})

# Provide callisto library
if(DEFINED CREATE_PACKAGE)
    find_package(Callisto)
    foreach(lib_name ${CALLISTO_LIBRARIES})
        if(TARGET Callisto::${lib_name})
            set(ENABLE_${lib_name} TRUE)
        endif()
    endforeach()
else()
    add_subdirectory(
        ${CMAKE_SOURCE_DIR}/../callisto.library
        ${CMAKE_CURRENT_BINARY_DIR}/callisto.library
    )

    foreach(lib_name ${CALLISTO_LIBRARIES})
        if(TARGET callisto_${lib_name})
            set(ENABLE_${lib_name} TRUE)
        endif()
    endforeach()
endif()

#--------------------------------------------------------------------------------------------------
# collect source and linked libraries to executable file
set(TEST_TARGET callisto_test)

set(TEST_SRC src/main.cpp)

macro(collect_source lib_name)
    if(DEFINED ENABLE_${lib_name})
        file(GLOB_RECURSE ${lib_name}_src "src/${lib_name}/*.c" "src/${lib_name}/*.cpp")
        list(APPEND TEST_SRC ${${lib_name}_src})
    endif()
endmacro()

foreach(lib_name ${CALLISTO_LIBRARIES})
    collect_source(${lib_name})
endforeach()


add_executable(${TEST_TARGET} ${TEST_SRC})
target_include_directories(${TEST_TARGET} PRIVATE src)

#--------------------------------------------------------------------------------------------------
# Generate debug pdb information for Release mode
# Need for boost::stactrace
if(MSVC)
    target_compile_options(${TEST_TARGET} PRIVATE "$<$<CONFIG:Release>:/Zi>")

    # fix problem when pdb symbols not find
    # https://github.com/boostorg/stacktrace/issues/55
    target_link_options(${TEST_TARGET} PRIVATE "/PDBALTPATH:%_PDB%")
endif()

#--------------------------------------------------------------------------------------------------
# 3rd party 
find_package(Boost PATHS ${CONAN_DIR})
find_package(GTest PATHS ${CONAN_DIR})

target_link_libraries(${TEST_TARGET} PRIVATE GTest::gtest)

if(NOT DEFINED CREATE_PACKAGE)
    macro(link_local lib_name)
        if(TARGET callisto_${lib_name})
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
        else()
            string(TOUPPER ${lib_name} lib_name_upper)
            target_compile_definitions(${TEST_TARGET} CALLISTO_${lib_name_upper}_DISABLE)
        endif()

    endmacro()

    foreach(lib_name ${CALLISTO_LIBRARIES})
        link_local(${lib_name})
    endforeach()
else()
    macro(link_conan lib_name)
        if(TARGET Callisto::${lib_name})
            target_link_libraries(${TEST_TARGET} PRIVATE Callisto::${lib_name})
        else()
            string(TOUPPER ${lib_name} lib_name_upper)
            target_compile_definitions(${TEST_TARGET} PRIVATE CALLISTO_${lib_name_upper}_DISABLE)
        endif()
    endmacro()

    foreach(lib_name ${CALLISTO_LIBRARIES})
        link_conan(${lib_name})
    endforeach()
endif()

#--------------------------------------------------------------------------------------------------
# copy dlls if platform is windows
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