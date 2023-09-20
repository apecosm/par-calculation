cmake_minimum_required(VERSION 3.0.0)

if (POLICY CMP0074)
  cmake_policy (SET CMP0074 NEW)
endif ()

if (POLICY CMP0083)
  cmake_policy (SET CMP0083 NEW)
endif ()


# define the par_calculation version
project(par_calculation VERSION 1.0.2)

# Find boost library
find_package(Boost 1.60 REQUIRED)
if(NOT ${Boost_FOUND})
    MESSAGE(FATAL_ERROR "The Boost library was not found")
endif()
MESSAGE(STATUS "BOOST found")
MESSAGE(STATUS "   - included files located in ${Boost_INCLUDE_DIRS}")

# Find NetCDF library
find_package(netCDF REQUIRED)
if(NOT ${netCDF_FOUND})
    MESSAGE(FATAL_ERROR "The NetCDF library was not found")
endif()

MESSAGE(STATUS "NetCDF found")
MESSAGE(STATUS "   - version = ${netCDF_VERSION}")
MESSAGE(STATUS "   - prefix = ${netCDF_INSTALL_PREFIX}")
MESSAGE(STATUS "   - included files located in ${netCDF_INCLUDE_DIR}")
MESSAGE(STATUS "   - library  files located in ${netCDF_LIB_DIR}")
MESSAGE(STATUS "   - has parallel support: ${netCDF_HAS_PARALLEL}")

# Find HDF5 library
find_package(HDF5 REQUIRED)
if(NOT ${HDF5_FOUND})
    MESSAGE(FATAL_ERROR "The HDF5 library was not found")
endif()

MESSAGE(STATUS "HDF5 found")
MESSAGE(STATUS "   - version = ${HDF5_VERSION}")
MESSAGE(STATUS "   - included files located in ${HDF5_INCLUDE_DIRS}")
MESSAGE(STATUS "   - library  files located in ${HDF5_C_LIBRARIES}")
MESSAGE(STATUS "   - parallel support: ${HDF5_IS_PARALLEL}")

# Find MPI Library
find_package(MPI REQUIRED)
if(NOT ${MPI_FOUND})
    MESSAGE(FATAL_ERROR "The MPI library was not found")
endif()
MESSAGE(STATUS "MPI found")
MESSAGE(STATUS "   - included files located in ${MPI_C_HEADER_DIR}")
MESSAGE(STATUS "   - library  files located in ${MPI_mpi_LIBRARY}")

# Get the latest abbreviated commit hash of the working branch
execute_process(
    COMMAND git log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Include the directories.
# PROJECT_BINARY_DIR is the path where the newly created Version.h is created
include_directories(
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${netCDF_INCLUDE_DIR}
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

################################################################# User defined options

set(RUNNING_TESTS true CACHE BOOL "True if tests should be running")
set(BUILD_MODE "release" CACHE STRING "Build mode (debug, release)")
set(BOOST_ASSERT false CACHE BOOL "True if Boost assert is on. Default is False")
set(USE_PARALLEL_NETCDF false CACHE BOOL "True if the Parallel Netcdf should be used. Default is False")

# If MPI is activated, then we look for the value of MPI
if(NOT NO_USE_MPI)
    # If MPI Found, include the MPI libray + activate MPI
    if(MPI_FOUND)
        include_directories("${MPI_C_HEADER_DIR}")
    else()
        # message(FATAL_ERROR "No MPI FOUND. Recompile using the -DNO_USE_MPI option")
        MESSAGE(WARNING "MPI library not found. The NO_USE_MPI option has been activated")
        set(NO_USE_MPI true CACHE BOOL "True if MPI should be deactivated. Default is OFF (i.e. MPI is activated)" FORCE)
    endif()
endif()

if(USE_PARALLEL_NETCDF)
    if(NOT ${netCDF_HAS_PARALLEL})
        MESSAGE(WARNING "NetCDF library has no parallel support. The USE_PARALLEL_NETCDF has been deactivated")
        set(USE_PARALLEL_NETCDF false CACHE BOOL "True if MPI should be deactivated. Default is OFF (i.e. MPI is activated)" FORCE)
    endif()
endif()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT BOOST_ASSERT)
    add_compile_options(-DBOOST_DISABLE_ASSERTS)
endif()

# If parallel Netcdf, activate the right option
if(USE_PARALLEL_NETCDF)
    add_compile_options(-DPAR_NETCDF)
endif()

if(BUILD_MODE STREQUAL "release")
    set(CMAKE_BUILD_TYPE Release)
elseif(BUILD_MODE STREQUAL "debug")
    set(CMAKE_BUILD_TYPE Debug)
    add_compile_options(-DNDEBUG)
else()
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

# Add path for the executable
add_executable(par_calculation main.cpp)

add_library(par_library string_util.cpp par.cpp ncio.cpp)

# If NEMO is not used, the executable is created
MESSAGE(STATUS "Building par_calculation binary")

# Add the target link directories
target_link_libraries(par_calculation par_library)

# Link with the NetCDF library
target_link_libraries(par_calculation ${netCDF_LIBRARIES})

# Link with the NetCDF library
target_link_libraries(par_calculation ${HDF5_LIBRARIES})

# If MPI is found, link with the MPI library
if(MPI_FOUND)
    target_link_libraries(par_calculation ${MPI_mpi_LIBRARY} ${MPI_mpi_cxx_LIBRARY})
endif()

set_property(TARGET par_calculation PROPERTY ENABLE_EXPORTS 1)

if(RUNNING_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
