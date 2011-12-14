###
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
# 
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#
# Note: Some of the libraries Totem EDK may link to may have additional
# requirements or restrictions.
#
###
# CMake system for Totem EDK was contributed by Jacob 'jacmoe' Moen
#
###

cmake_minimum_required(VERSION 2.8)

project(TotemEDK)

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()
 
set(CMAKE_DEBUG_POSTFIX "_d")

# define an option for choosing between static and dynamic C runtime
set(STATIC_STD_LIBS TRUE CACHE BOOL "TRUE to statically link to the standard libraries, FALSE to use them as DLLs")

if(MSVC)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  
  if(STATIC_STD_LIBS)
	foreach(flag
	  CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
	  CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
	  if(${flag} MATCHES "/MD")
		string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
	  endif()
	endforeach()
  endif()
  
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -std=c++0x")
endif()

set(BUILD_TEST_PROJECTS TRUE CACHE BOOL "TRUE if you want to include test projects with the generated solution, FALSE if not.")
if(BUILD_TEST_PROJECTS)
	add_subdirectory(tests)
endif()

set(BUILD_EXAMPLE_PROJECTS TRUE CACHE BOOL "TRUE if you want to include example projects with the generated solution, FALSE if not.")
if(BUILD_EXAMPLE_PROJECTS)
	add_subdirectory(examples)
endif()

set(BUILD_TOOL_PROJECTS FALSE CACHE BOOL "TRUE if you want to include tool projects with the generated solution, FALSE if not.")
if(BUILD_TOOL_PROJECTS)
	add_subdirectory(tools)
endif()

set(TOTEM_WITHOUT_PREPROCESSING TRUE CACHE BOOL "TRUE if you want Totem EDK's codebase without any preprocessing , FALSE if not.")
if(TOTEM_WITHOUT_PREPROCESSING)
	include_directories("${CMAKE_SOURCE_DIR}"
	  "${CMAKE_SOURCE_DIR}/src"
	  "${CMAKE_SOURCE_DIR}/include"
	)
	add_subdirectory(src)
endif()

set(PREPROCESS_TOTEM_FOR_CLANLIB FALSE CACHE BOOL "TRUE if you want to preprocess Totem EDK's codebase with ClanLib 3rdparty bindings, FALSE if not.")
if(PREPROCESS_TOTEM_FOR_CLANLIB)
	include_directories("${CMAKE_SOURCE_DIR}"
	  "${CMAKE_SOURCE_DIR}/editions/clanlib/src"
	  "${CMAKE_SOURCE_DIR}/editions/clanlib/include"
	)
	add_subdirectory(depends/ClanLib)
endif()