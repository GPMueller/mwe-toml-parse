MESSAGE( STATUS ">> -------------------------------------------------------------------- <<" )
MESSAGE( STATUS ">> ------------------------- MWE -------------------------------------- <<" )


######### CMake Version ###############################################
cmake_minimum_required( VERSION 3.10 FATAL_ERROR )
### We need at least C++17
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
### Distinction between Clang and AppleClang
cmake_policy( SET CMP0025 NEW )
#######################################################################



### Set a default build type in case none is passed
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()


######### Extra flags for Eigen #######################################
SET(CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS_RELEASE}")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
SET(CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS_DEBUG}")
#######################################################################


######## Compiler-specific flags #####################################
### GNU Compiler Collection - gcc
if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
    ### Require at least gcc 7.0
    if( CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7 )
        message( FATAL_ERROR "GCC version must be at least 7!" )
    endif( )
    ### Compile and Link Flags (we deactivate -Wint-in-bool-context because of Eigen)
    set( MWE_COMPILE_FLAGS "-Wall -Wextra -Wpedantic -Wno-int-in-bool-context" )
    set( MWE_LINK_FLAGS    "" )
    ### We deactivate -Wunknown-pragmas in case OpenMP is not used
    if( NOT MWE_USE_OPENMP )
        set( MWE_COMPILE_FLAGS "${MWE_COMPILE_FLAGS} -Wno-unknown-pragmas" )
    endif( )

### Apple Clang
elseif( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
    ### Compile and Link Flags
    set( MWE_COMPILE_FLAGS "-Wall -Wextra -Wpedantic" )
    set( MWE_LINK_FLAGS    "" )

### Microsoft Visual Compiler - msvc
elseif( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC" )
    ### Compile and Link Flags
    set( MWE_COMPILE_FLAGS "-DNOMINMAX" )
    set( MWE_LINK_FLAGS    "" )

### Intel Compiler - icc
elseif( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Intel" )
    ### Compile and Link Flags
    set( MWE_COMPILE_FLAGS "-Wall -Wextra -Wpedantic" )
    set( MWE_LINK_FLAGS    "" )
endif( )
message( STATUS "MWE Compile Flags: ${MWE_COMPILE_FLAGS}" )
message( STATUS "MWE Link Flags:    ${MWE_LINK_FLAGS}" )
######################################################################


######### Where to search for library headers #########################
include_directories( ${PROJECT_SOURCE_DIR} )
#######################################################################


add_executable( mwe main.cpp )
set_property( TARGET mwe PROPERTY CXX_STANDARD 17 )
set_property( TARGET mwe PROPERTY CXX_STANDARD_REQUIRED ON )
set_property( TARGET mwe PROPERTY CXX_EXTENSIONS OFF )
set_property( TARGET mwe PROPERTY COMPILE_FLAGS "${MWE_COMPILE_FLAGS} ${MWE_FLAGS_COVERAGE}" )
set_property( TARGET mwe PROPERTY LINK_FLAGS    "${MWE_LINK_FLAGS}    ${MWE_FLAGS_COVERAGE}" )

target_include_directories( mwe PRIVATE ${PROJECT_SOURCE_DIR} )


MESSAGE( STATUS ">> ------------------------- MWE done --------------------------------- <<" )
MESSAGE( STATUS ">> -------------------------------------------------------------------- <<" )