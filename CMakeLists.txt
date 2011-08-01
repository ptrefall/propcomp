cmake_minimum_required(VERSION 2.8)

project(EntitySystemSolution)

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()
 
set(CMAKE_DEBUG_POSTFIX "_d")
if(MSVC)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif(MSVC)

include_directories("${CMAKE_SOURCE_DIR}"
  "${CMAKE_SOURCE_DIR}/src"
)

add_subdirectory(src)
add_subdirectory(tests)