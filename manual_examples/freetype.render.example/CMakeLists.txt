cmake_minimum_required(VERSION 3.19)

# configure project *******************************************************************************
project(freetype.render.example CXX)
set(TARGET_NAME freetype_render_example)

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD     20)

if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

# conan settings **********************************************************************************
set(CONAN_DIR ${CMAKE_CURRENT_LIST_DIR}/../../.main_cache/conan/x64/${CMAKE_BUILD_TYPE})
set(CMAKE_PREFIX_PATH ${CONAN_DIR})
set(CMAKE_MODULE_PATH ${CONAN_DIR})

# collect source and linked libraries to executable file ******************************************
file(GLOB_RECURSE TARGET_SRC "src/*.c" "src/*.cpp")


add_executable(${TARGET_NAME} ${TARGET_SRC})
target_include_directories(${TARGET_NAME} PRIVATE src)

# 3rd party 

# link with family libraries
macro(link_local lib_name)
    if(NOT TARGET callisto_${lib_name})
        add_subdirectory(
            ${CMAKE_CURRENT_LIST_DIR}/../../callisto.${lib_name}
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

set(TEST_PACKAGE_LINK_LIBRARIES graphics)
foreach(lib_name1 ${TEST_PACKAGE_LINK_LIBRARIES})
    link_local(${lib_name1})
endforeach()

find_package(Boost)
target_link_libraries(${TARGET_NAME} PRIVATE Boost::program_options)

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


# Copy resource files to output
add_custom_command(
    TARGET ${TARGET_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/../resources $<TARGET_FILE_DIR:${TARGET_NAME}>/resources
)