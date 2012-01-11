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

project(TotemEDK_Standard)

empty_preprocess_pair_list()

add_preprocess_pair("T_String" 							"std::string")
add_preprocess_pair("D32" 								"double")
add_preprocess_pair("F32" 								"float")
add_preprocess_pair("S32" 								"int")
add_preprocess_pair("U32" 								"unsigned int")

add_preprocess_pair("T_PropertyTypeId" 					"unsigned int")
add_preprocess_pair("T_EntityId" 						"unsigned long")
add_preprocess_pair("T_Exception" 						"std::runtime_error")
add_preprocess_pair("HAS_SIGNALSLOTS_INHERITANCE_TYPE" 	": public sigslot::has_slots<>")
add_preprocess_pair("NULL_PTR" 							"nullptr")
add_preprocess_pair("typename T_Signal_v0<>" 			"sigslot::signal0")
add_preprocess_pair("T_Signal_v0<>" 					"sigslot::signal0")
add_preprocess_pair("typename T_Delegate_v0" 			"fastdelegate::FastDelegate0")
add_preprocess_pair("T_Delegate_v0" 					"fastdelegate::FastDelegate0")
add_preprocess_pair("T_Any" 							"cdiggins::any")
add_preprocess_pair("T_BadAnyCast" 						"cdiggins::anyimpl::bad_any_cast")

add_preprocess_pair("typename T_Map" 					"std::unordered_map")
add_preprocess_pair("T_Map" 							"std::unordered_map")
add_preprocess_pair("typename T_SharedPtr" 				"std::shared_ptr")
add_preprocess_pair("T_SharedPtr" 						"std::shared_ptr")
add_preprocess_pair("typename T_Vector" 				"std::vector")
add_preprocess_pair("T_Vector" 							"std::vector")
add_preprocess_pair("typename T_Pair" 					"std::pair")
add_preprocess_pair("T_Pair" 							"std::pair")
add_preprocess_pair("::Type" 							" ")

add_preprocess_pair_regex("typename T_Signal_v(.)"		"sigslot::signal\\\\1")
add_preprocess_pair_regex("T_Signal_v(.)"				"sigslot::signal\\\\1")
add_preprocess_pair_regex("typename T_Delegate_v(.)"	"fastdelegate::FastDelegate\\\\1")
add_preprocess_pair_regex("T_Delegate_v(.)"				"fastdelegate::FastDelegate\\\\1")

set(package_src_files)
set(package_hdr_files)
set(package_config_hdr_files)		
preprocess_totem("Standard")

add_library(TotemEDK_Standard STATIC ${package_src_files} ${package_hdr_files} ${package_config_hdr_files})

set_target_properties(TotemEDK_Standard PROPERTIES DEBUG_POSTFIX -debug)
set_target_properties(TotemEDK_Standard PROPERTIES LINKER_LANGUAGE CXX)
