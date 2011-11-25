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

project(TotemEDK_ClanLib)

###
# PREPROCESS Totem EDK's codebase
###
message(STATUS "Preprocessing Totem EDK for ClanLib")

#Define directory paths to totem files
set(TOTEM_SRCS ${TotemEDK_SOURCE_DIR}/src)
set(TOTEM_HDRS ${TotemEDK_SOURCE_DIR}/include/Totem)
set(TOTEM_SRCS_ADDONS ${TotemEDK_SOURCE_DIR}/src/Addons)
set(TOTEM_HDRS_ADDONS ${TotemEDK_SOURCE_DIR}/include/Totem/Addons)

message(STATUS "Path to Totem src/: ${TOTEM_SRCS}")
message(STATUS "Path to Totem include/Totem/: ${TOTEM_HDRS}")
message(STATUS "Path to Totem src/Addons/: ${TOTEM_SRCS_ADDONS}")
message(STATUS "Path to Totem include/Totem/Addons/: ${TOTEM_HDRS_ADDONS}")
message(STATUS " ")

#Extract files from directories
file(GLOB totem_src_files_abs_path ${TOTEM_SRCS}/*.cpp)
file(GLOB totem_hdr_files_abs_path ${TOTEM_HDRS}/*.h)
file(GLOB totem_src_addon_files_abs_path ${TOTEM_SRCS_ADDONS}/*.cpp)
file(GLOB totem_hdr_addon_files_abs_path ${TOTEM_HDRS_ADDONS}/*.h)
message(STATUS "Source Files in src/ ${totem_src_files_abs_path}")
message(STATUS "Header Files in include/Totem/ ${totem_hdr_files_abs_path}")
message(STATUS "Source Files in src/Addons/ ${totem_src_addon_files_abs_path}")
message(STATUS "Header Files in include/Totem/Addons/ ${totem_hdr_addon_files_abs_path}")
message(STATUS " ")

#Define the output paths
set(TOTEM_CLANLIB_PATH_NAME "clanlib")
set(TOTEM_FOR_CLANLIB_OUTPUT_DIR ${TotemEDK_SOURCE_DIR}/editions/${TOTEM_CLANLIB_PATH_NAME})
set(TFC_SRCS_DIR ${TOTEM_FOR_CLANLIB_OUTPUT_DIR}/src)
set(TFC_HDRS_DIR ${TOTEM_FOR_CLANLIB_OUTPUT_DIR}/include/Totem)
set(TFC_SRCS_ADDONS_DIR ${TOTEM_FOR_CLANLIB_OUTPUT_DIR}/src/Addons)
set(TFC_HDRS_ADDONS_DIR ${TOTEM_FOR_CLANLIB_OUTPUT_DIR}/include/Totem/Addons)

message(STATUS "Output Path to Totem ClanLib src/: ${TFC_SRCS_DIR}")
message(STATUS "Output Path to Totem ClanLib include/Totem/: ${TFC_HDRS_DIR}")
message(STATUS "Output Path to Totem ClanLib src/Addons/: ${TFC_SRCS_ADDONS_DIR}")
message(STATUS "Output Path to Totem ClanLib include/Totem/Addons/: ${TFC_HDRS_ADDONS_DIR}")
message(STATUS " ")

#Split into filenames
set(totem_src_files)
set(totem_hdr_files)
set(totem_src_addon_files)
set(totem_hdr_addon_files)

message(STATUS "src/ filenames:")
FOREACH(f ${totem_src_files_abs_path})
	FILE(RELATIVE_PATH folder ${TOTEM_SRCS} ${f})
	get_filename_component(filename ${folder} NAME)
	set(totem_src_files ${totem_src_files}  ${filename})
	message(STATUS "- ${filename}")
ENDFOREACH(f ${ARGN})
message(STATUS " ")
message(STATUS "src/Addons/ filenames:")
FOREACH(f ${totem_src_addon_files_abs_path})
	FILE(RELATIVE_PATH folder ${TOTEM_SRCS_ADDONS} ${f})
	get_filename_component(filename ${folder} NAME)
	set(totem_src_addon_files ${totem_src_addon_files}  ${filename})
	message(STATUS "- ${filename}")
ENDFOREACH(f ${ARGN})
message(STATUS " ")
message(STATUS "include/Totem/ filenames:")
FOREACH(f ${totem_hdr_files_abs_path})
	FILE(RELATIVE_PATH folder ${TOTEM_HDRS} ${f})
	get_filename_component(filename ${folder} NAME)
	set(totem_hdr_files ${totem_hdr_files}  ${filename})
	message(STATUS "- ${filename}")
ENDFOREACH(f ${ARGN})
message(STATUS " ")
message(STATUS "include/Totem/Addons/ filenames:")
FOREACH(f ${totem_hdr_addon_files_abs_path})
	FILE(RELATIVE_PATH folder ${TOTEM_HDRS_ADDONS} ${f})
	get_filename_component(filename ${folder} NAME)
	set(totem_hdr_addon_files ${totem_hdr_addon_files} ${filename})
	message(STATUS "- ${filename}")
ENDFOREACH(f ${ARGN})
message(STATUS " ")

#Define output files with absolute paths
set(tcp_src_files)
set(tcp_hdr_files)
set(tcp_src_addon_files)
set(tcp_hdr_addon_files)
foreach(f ${totem_src_files})
	set(tcp_src_files ${tcp_src_files} ${TFC_SRCS_DIR}/${f})
endforeach()
foreach(f ${totem_hdr_files})
	set(tcp_hdr_files ${tcp_hdr_files} ${TFC_HDRS_DIR}/${f})
endforeach()
foreach(f ${totem_src_addon_files})
	set(tcp_src_addon_files ${tcp_src_addon_files} ${TFC_SRCS_ADDONS_DIR}/${f})
endforeach()
foreach(f ${totem_hdr_addon_files})
	set(tcp_hdr_addon_files ${tcp_hdr_addon_files} ${TFC_HDRS_ADDONS_DIR}/${f})
endforeach()

message(STATUS "Source Files to editions/clanlib/src/ ${tcp_src_files}")
message(STATUS "Header Files to editions/clanlib/include/Totem/ ${tcp_hdr_files}")
message(STATUS "Source Files to editions/clanlib/src/Addons/ ${tcp_src_addon_files}")
message(STATUS "Header Files to editions/clanlib/include/Totem/Addons/ ${tcp_hdr_addon_files}")
message(STATUS " ")

#Define where to locate FindSed.cmake
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

#If we're on MSVC/Windows
if(MSVC)
	#find Sed for Windows
	#http://gnuwin32.sourceforge.net/packages/sed.htm
	find_package(Sed REQUIRED)
	find_program(SED_EXECUTABLE sed PATHS ${SED_DIR}/bin/)
	if(NOT SED_EXECUTABLE)
	   message(SEND_ERROR "Could not find Sed for Windows!")
	endif()
	
	message(STATUS "Copy files to ${TOTEM_FOR_CLANLIB_OUTPUT_DIR}:")
	message(STATUS "----------------------------------------------")
	
	##################
	# copy src files
	#
	set(list_count)
	set(list_index 0)
	list(LENGTH tcp_src_files list_count)
	foreach(input ${totem_src_files_abs_path})
		list(GET tcp_src_files ${list_index} output)
		message(STATUS "Evaluating index ${list_index}/${list_count}: ${output}")
		MATH(EXPR list_index "${list_index}+1")
		
		configure_file(${input} ${output} COPYONLY)
	endforeach(input ${totem_src_files_abs_path})
	#
	#################
	#configure_file(${totem_src_files_abs_path} ${tcp_src_files} COPYONLY)
	message(STATUS " ")
	
	##################
	# copy header files
	#
	set(list_count)
	set(list_index 0)
	list(LENGTH tcp_hdr_files list_count)
	foreach(input ${totem_hdr_files_abs_path})
		list(GET tcp_hdr_files ${list_index} output)
		message(STATUS "Evaluating index ${list_index}/${list_count}: ${output}")
		MATH(EXPR list_index "${list_index}+1")
		
		configure_file(${input} ${output} COPYONLY)
	endforeach(input ${totem_hdr_files_abs_path})
	#
	#################
	message(STATUS " ")
	
	##################
	# copy src addon files
	#
	set(list_count)
	set(list_index 0)
	list(LENGTH tcp_src_addon_files list_count)
	foreach(input ${totem_src_addon_files_abs_path})
		list(GET tcp_src_addon_files ${list_index} output)
		message(STATUS "Evaluating index ${list_index}/${list_count}: ${output}")
		MATH(EXPR list_index "${list_index}+1")
		
		configure_file(${input} ${output} COPYONLY)
	endforeach(input ${totem_src_addon_files_abs_path})
	#
	#################
	#configure_file(${totem_src_addon_files_abs_path} ${tcp_src_addon_files} COPYONLY)
	message(STATUS " ")
	
	##################
	# copy hdr addon files
	#
	set(list_count)
	set(list_index 0)
	list(LENGTH tcp_hdr_addon_files list_count)
	foreach(input ${totem_hdr_addon_files_abs_path})
		list(GET tcp_hdr_addon_files ${list_index} output)
		message(STATUS "Evaluating index ${list_index}/${list_count}: ${output}")
		MATH(EXPR list_index "${list_index}+1")
		
		configure_file(${input} ${output} COPYONLY)
	endforeach(input ${totem_hdr_addon_files_abs_path})
	#
	#################
	#configure_file(${totem_hdr_addon_files_abs_path} ${tcp_hdr_addon_files} COPYONLY)
	message(STATUS "----------------------------------------------")
	
	add_custom_command(	OUTPUT "${tcp_src_files}"
						COMMAND ${SED_EXECUTABLE} -i s/T_String/CL_String/g  ${tcp_src_files}
						COMMENT "Preprocessing Totem EDK Strings for ClanLib"
	)
	add_custom_command(	OUTPUT "${tcp_hdr_files}"
						COMMAND ${SED_EXECUTABLE} -i s/T_String/CL_String/g  ${tcp_hdr_files}
						COMMENT "Preprocessing Totem EDK Strings for ClanLib"
	)
#Else, add linux support
else()
	#find GNU Sed
	#http://www.gnu.org/s/sed/
endif()

add_library(TotemEDK_ClanLib STATIC ${tcp_src_files} ${tcp_hdr_files})

set_target_properties(TotemEDK_ClanLib PROPERTIES DEBUG_POSTFIX _d)
