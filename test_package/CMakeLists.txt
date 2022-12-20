cmake_minimum_required(VERSION 3.19)

# configure project *******************************************************************************
project(callisto.test CXX)
set(TARGET_NAME callisto_test)

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD     20)


#if(NOT DEFINED CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE "Debug")
#endif()

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
file(GLOB_RECURSE AUTO_SRC "src/*.c" "src/*.cpp")
add_executable(${TARGET_NAME} ${AUTO_SRC})
target_include_directories(${TARGET_NAME} PRIVATE src)


# 3rd party 
find_package(Boost PATHS ${CONAN_DIR})
find_package(GTest PATHS ${CONAN_DIR})
target_link_libraries(${TARGET_NAME} PRIVATE GTest::gtest)


# link with family libraries
if(NOT DEFINED CREATE_PACKAGE)
    macro(link_local lib_name)
        if(NOT TARGET callisto_${lib_name})
            add_subdirectory(
                ${CMAKE_SOURCE_DIR}/../callisto.${lib_name}
                ${CMAKE_CURRENT_BINARY_DIR}/callisto.${lib_name}
            )

            target_link_libraries(${TARGET_NAME} PRIVATE callisto_${lib_name})

            if(WIN32)
                add_custom_command(
                    TARGET ${TARGET_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} 
                    -E copy_if_different 
                    $<TARGET_FILE:callisto_${lib_name}> 
                    $<TARGET_FILE_DIR:${TARGET_NAME}>
                )
            endif()
        endif()
    endmacro()

    set(TEST_PACKAGE_LINK_LIBRARIES framework math)
    foreach(lib_name1 ${TEST_PACKAGE_LINK_LIBRARIES})
        link_local(${lib_name1})
    endforeach()
else()
    find_package(Callisto)
    target_link_libraries(${TARGET_NAME} PRIVATE Callisto::framework)
    target_link_libraries(${TARGET_NAME} PRIVATE Callisto::math)
endif()


# copy dlls if platform is windows ****************************************************************
if(WIN32)
    file(GLOB BINARY_SHARED_LIBRARIES "${CONAN_DIR}/bin/*.dll")
    foreach(BINARY_SHARED_LIBRARY IN LISTS BINARY_SHARED_LIBRARIES)
        add_custom_command(
            TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} 
            -E copy_if_different 
            ${BINARY_SHARED_LIBRARY}
            $<TARGET_FILE_DIR:${TARGET_NAME}>
        )
    endforeach()
endif()