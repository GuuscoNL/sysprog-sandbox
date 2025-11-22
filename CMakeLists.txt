cmake_minimum_required(VERSION 3.10.0)
project(idk VERSION 0.1.0 LANGUAGES C CXX)

# use ccache if available
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Found ccache: ${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
else()
    message(STATUS "ccache not found. Consider installing ccache to speed up recompilation.")
endif()

# Use ninja if available
find_program(NINJA_PROGRAM ninja)
if(NINJA_PROGRAM)
    message(STATUS "Found ninja: ${NINJA_PROGRAM}")
    set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "" FORCE)
    set(CMAKE_MAKE_PROGRAM ${NINJA_PROGRAM} CACHE INTERNAL "" FORCE)
else()
    message(STATUS "ninja not found. Consider installing ninja for faster builds.")
endif()


# Use mold or lld linker if available
find_program(MOLD_LINKER mold)
find_program(LLD_LINKER lld)

if(MOLD_LINKER)
    message(STATUS "Found mold linker: ${MOLD_LINKER}")
    # Clang and GCC uses '-fuse-ld=mold'
    add_link_options("-fuse-ld=mold")
    # SDL fix: disable version-script on unsupported linkers
    if(WIN32)
        set(LINKER_SUPPORTS_VERSION_SCRIPT FALSE)
    endif()
elseif(LLD_LINKER)
    message(STATUS "Found lld linker: ${LLD_LINKER}")
    # Clang and GCC uses '-fuse-ld=lld'
    add_link_options("-fuse-ld=lld")
    # SDL fix: disable version-script on unsupported linkers
    if(WIN32)
        set(LINKER_SUPPORTS_VERSION_SCRIPT FALSE)
    endif()
else()
    message(STATUS "mold/lld linker not found. Using default system linker. Consider installing mold or lld for faster linking.")
endif()


add_subdirectory(main_src)
add_subdirectory(child_src)
add_subdirectory(plugin1)
add_subdirectory(plugin2)
add_subdirectory(plugin3)
add_subdirectory(plugin4)