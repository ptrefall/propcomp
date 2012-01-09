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
set(TOTEM_CLANLIB_CONFIG_H ${TotemEDK_SOURCE_DIR}/depends/ClanLib)

message(STATUS "Path to Totem src/: ${TOTEM_SRCS}")
message(STATUS "Path to Totem include/Totem/: ${TOTEM_HDRS}")
message(STATUS "Path to Totem src/Addons/: ${TOTEM_SRCS_ADDONS}")
message(STATUS "Path to Totem include/Totem/Addons/: ${TOTEM_HDRS_ADDONS}")
message(STATUS "Path to ClanLib config.h for Totem: ${TOTEM_CLANLIB_CONFIG_H}")
message(STATUS " ")

#Extract files from directories
file(GLOB totem_src_files_abs_path ${TOTEM_SRCS}/*.cpp)
file(GLOB totem_hdr_files_abs_path ${TOTEM_HDRS}/*.h)
file(GLOB totem_src_addon_files_abs_path ${TOTEM_SRCS_ADDONS}/*.cpp)
file(GLOB totem_hdr_addon_files_abs_path ${TOTEM_HDRS_ADDONS}/*.h)
file(GLOB totem_clanlib_config_hdr_abs_path ${TOTEM_CLANLIB_CONFIG_H}/*.h)
message(STATUS "Source Files in src/ ${totem_src_files_abs_path}")
message(STATUS "Header Files in include/Totem/ ${totem_hdr_files_abs_path}")
message(STATUS "Source Files in src/Addons/ ${totem_src_addon_files_abs_path}")
message(STATUS "Header Files in include/Totem/Addons/ ${totem_hdr_addon_files_abs_path}")
message(STATUS "ClanLib config.h for Totem in depends/ClanLib/ ${totem_clanlib_config_hdr_abs_path}")
message(STATUS " ")

#Define the output paths
set(TOTEM_CLANLIB_PATH_NAME "clanlib")
set(TOTEM_FOR_CLANLIB_OUTPUT_DIR ${TotemEDK_SOURCE_DIR}/editions/${TOTEM_CLANLIB_PATH_NAME})
set(TFC_SRCS_DIR ${TOTEM_FOR_CLANLIB_OUTPUT_DIR}/src)
set(TFC_HDRS_DIR ${TOTEM_FOR_CLANLIB_OUTPUT_DIR}/include/Totem)
set(TFC_SRCS_ADDONS_DIR ${TOTEM_FOR_CLANLIB_OUTPUT_DIR}/src/Addons)
set(TFC_HDRS_ADDONS_DIR ${TOTEM_FOR_CLANLIB_OUTPUT_DIR}/include/Totem/Addons)
set(TFC_TOTEM_CLANLIB_CONFIG_DIR ${TOTEM_FOR_CLANLIB_OUTPUT_DIR}/include/Totem)

message(STATUS "Output Path to Totem ClanLib src/: ${TFC_SRCS_DIR}")
message(STATUS "Output Path to Totem ClanLib include/Totem/: ${TFC_HDRS_DIR}")
message(STATUS "Output Path to Totem ClanLib src/Addons/: ${TFC_SRCS_ADDONS_DIR}")
message(STATUS "Output Path to Totem ClanLib include/Totem/Addons/: ${TFC_HDRS_ADDONS_DIR}")
message(STATUS "Output Path to Totem ClanLib config.h include/Totem/: ${TFC_TOTEM_CLANLIB_CONFIG_DIR}")
message(STATUS " ")

#Split into filenames
set(totem_src_files)
set(totem_hdr_files)
set(totem_hdr_ignore_files)
set(totem_src_addon_files)
set(totem_hdr_addon_files)
set(totem_clanlib_config_file)

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
	
	STRING(COMPARE EQUAL ${filename} "types_config.h" string_compare_result)
	STRING(COMPARE EQUAL ${filename} "config.h" string_compare_result2)
	
	if(${string_compare_result} OR ${string_compare_result2})
		set(totem_hdr_ignore_files ${totem_hdr_ignore_files} ${f})
		message(STATUS "THROW AWAY ${filename}")
	endif()
	
	if(NOT ${string_compare_result} AND NOT ${string_compare_result2})
		set(totem_hdr_files ${totem_hdr_files}  ${filename})
		message(STATUS "- ${filename}")
	endif()
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
message(STATUS "include/Totem/config.h:")
FOREACH(f ${totem_clanlib_config_hdr_abs_path})
	FILE(RELATIVE_PATH folder ${TOTEM_HDRS_ADDONS} ${f})
	get_filename_component(filename ${folder} NAME)
	set(totem_clanlib_config_file ${totem_clanlib_config_file} ${filename})
	message(STATUS "- ${filename}")
ENDFOREACH(f ${ARGN})
message(STATUS " ")

#Define output files with absolute paths
set(tcp_src_files)
set(tcp_hdr_files)
set(tcp_src_addon_files)
set(tcp_hdr_addon_files)
set(tcp_clanlib_config_file)
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
foreach(f ${totem_clanlib_config_file})
	set(tcp_clanlib_config_file ${tcp_clanlib_config_file} ${TFC_TOTEM_CLANLIB_CONFIG_DIR}/${f})
endforeach()

message(STATUS "Source Files to editions/clanlib/src/ ${tcp_src_files}")
message(STATUS "Header Files to editions/clanlib/include/Totem/ ${tcp_hdr_files}")
message(STATUS "Source Files to editions/clanlib/src/Addons/ ${tcp_src_addon_files}")
message(STATUS "Header Files to editions/clanlib/include/Totem/Addons/ ${tcp_hdr_addon_files}")
message(STATUS "ClanLib Config File to editions/clanlib/include/Totem/ ${tcp_clanlib_config_file}")
message(STATUS " ")

#Define where to locate FindSed.cmake
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

#find Sed for Windows
#http://gnuwin32.sourceforge.net/packages/sed.htm
#or for linux
#gnu sed

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
message(STATUS " ")

##################
# copy header files
#
set(list_count)
set(list_index 0)
list(LENGTH totem_hdr_files_abs_path list_count)
foreach(input ${totem_hdr_files_abs_path})
	set(ignore_index 0)
	foreach(ignore ${totem_hdr_ignore_files})
		STRING(COMPARE EQUAL ${input} ${ignore} ignore_this_index)
		if(${ignore_this_index})
			set(ignore_index 1)
		endif(${ignore_this_index})
	endforeach(ignore ${totem_hdr_ignore_files})
	
	if(NOT ${ignore_index})
		list(GET tcp_hdr_files ${list_index} output)
		message(STATUS "Evaluating index ${list_index}/${list_count}: ${output}")
		MATH(EXPR list_index "${list_index}+1")
		
		configure_file(${input} ${output} COPYONLY)
	endif(NOT ${ignore_index})
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
message(STATUS " ")

##################
# copy clanlib config file
#
set(list_count)
set(list_index 0)
list(LENGTH tcp_clanlib_config_file list_count)
foreach(input ${totem_clanlib_config_hdr_abs_path})
	list(GET tcp_clanlib_config_file ${list_index} output)
	message(STATUS "Evaluating index ${list_index}/${list_count}: ${output}")
	MATH(EXPR list_index "${list_index}+1")
	
	configure_file(${input} ${output} COPYONLY)
endforeach(input ${totem_clanlib_config_hdr_abs_path})
#
#################
message(STATUS "----------------------------------------------")

set(output_files ${tcp_src_files} ${tcp_hdr_files})

function(do_replace comment)
	foreach(output ${output_files})
		FILE(READ "${output}" contents)
		
		STRING(REPLACE "T_String" 							"CL_String" 					contents "${contents}")
		STRING(REPLACE "D32" 								"double" 						contents "${contents}")
		STRING(REPLACE "F32" 								"float" 						contents "${contents}")
		STRING(REPLACE "S32" 								"int" 							contents "${contents}")
		STRING(REPLACE "U32" 								"unsigned int" 					contents "${contents}")
		
		STRING(REPLACE "T_PropertyTypeId" 					"unsigned int" 					contents "${contents}")
		STRING(REPLACE "T_EntityId" 						"unsigned long" 				contents "${contents}")
		STRING(REPLACE "T_Exception" 						"CL_Exception" 					contents "${contents}")
		STRING(REPLACE "HAS_SIGNALSLOTS_INHERITANCE_TYPE" 	"" 								contents "${contents}")
		STRING(REPLACE "NULL_PTR" 							"nullptr" 						contents "${contents}")
		STRING(REPLACE "typename T_Signal_v0<>::Type" 		"CL_Signal_v0" 					contents "${contents}")
		STRING(REPLACE ".bind(" 							".set("							contents "${contents}")
		STRING(REPLACE "delegate->delegate(" 				"delegate->delegate.invoke(" 	contents "${contents}")
		
		STRING(REPLACE "typename T_Map" 					"std::unordered_map" 			contents "${contents}")
		STRING(REPLACE "T_Map" 								"std::unordered_map" 			contents "${contents}")
		STRING(REPLACE "typename T_SharedPtr" 				"CL_SharedPtr" 					contents "${contents}")
		STRING(REPLACE "T_SharedPtr" 						"CL_SharedPtr" 					contents "${contents}")
		STRING(REPLACE "typename T_Vector" 					"std::vector" 					contents "${contents}")
		STRING(REPLACE "T_Vector" 							"std::vector" 					contents "${contents}")
		STRING(REPLACE "typename T_Pair" 					"std::pair" 					contents "${contents}")
		STRING(REPLACE "T_Pair" 							"std::pair" 					contents "${contents}")
		STRING(REPLACE "::Type" 							"" 								contents "${contents}")
		STRING(REPLACE ";" 									"\;" 							contents "${contents}")
		
		STRING(REGEX REPLACE "typename T_Signal_v(.)"		"CL_Signal_v\\1"				contents "${contents}")
		STRING(REGEX REPLACE "T_Signal_v(.)"				"CL_Signal_v\\1"				contents "${contents}")
		
		#message(STATUS " ")
		#message(STATUS "Content of ${output}:\n${contents}")
		#message(STATUS " ")
		
		FILE(WRITE ${output} ${contents})
	endforeach(output ${output_files})
endfunction(do_replace)

do_replace("Preprocessing Totem EDK for ClanLib")

message(STATUS "Preprocessing Totem EDK for ClanLib is FINISHED!")
message(STATUS "See editions/clanlib/ for list of all files.")

find_package(ClanLib REQUIRED)
include_directories(${CL_INCLUDE_PATH})

add_library(TotemEDK_ClanLib STATIC ${tcp_src_files} ${tcp_hdr_files} ${tcp_clanlib_config_file})

set_target_properties(TotemEDK_ClanLib PROPERTIES DEBUG_POSTFIX _d)
set_target_properties(TotemEDK_ClanLib PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(TotemEDK_ClanLib
  debug ${CL_CORE_LIB_DEBUG} optimized ${CL_CORE_LIB_RELEASE}
)
