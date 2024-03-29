macro(callisto_configure_conan main_cache_dir)
    set(CONAN_DIR "")
    if(DEFINED CREATE_PACKAGE_STATUS)
        set(CONAN_DIR ${CMAKE_BINARY_DIR})
    else()
        set(CONAN_DIR ${main_cache_dir}/conan/x64/${CMAKE_BUILD_TYPE})
    endif()
    include(${CONAN_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endmacro()