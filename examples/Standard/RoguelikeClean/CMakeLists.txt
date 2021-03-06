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

cmake_minimum_required(VERSION 2.8.3)

set(NAME RoguelikeClean)
project(${NAME})

set(TOTEM_HDRS
  ${CMAKE_SOURCE_DIR}/include/Totem/IComponent.h
  ${CMAKE_SOURCE_DIR}/include/Totem/Component.h
  ${CMAKE_SOURCE_DIR}/include/Totem/ComponentContainer.h
  ${CMAKE_SOURCE_DIR}/include/Totem/IProperty.h
  ${CMAKE_SOURCE_DIR}/include/Totem/Property.h
  ${CMAKE_SOURCE_DIR}/include/Totem/PropertyContainer.h
  ${CMAKE_SOURCE_DIR}/include/Totem/IPropertyList.h
  ${CMAKE_SOURCE_DIR}/include/Totem/PropertyList.h
  ${CMAKE_SOURCE_DIR}/include/Totem/PropertyListContainer.h
  ${CMAKE_SOURCE_DIR}/include/Totem/HashedString.h
)
SOURCE_GROUP("Source Files\\Totem" FILES ${TOTEM_HDRS})

set(TOTEM_EXT_HDRS
  ${CMAKE_SOURCE_DIR}/include/Totem/Extensions/EventSystem.h
)
SOURCE_GROUP("Source Files\\Totem" FILES ${TOTEM_EXT_HDRS})

file(GLOB ROOT_HEADER *.h)
file(GLOB ROOT_SOURCE *.cpp)
SOURCE_GROUP("Source Files" FILES ${ROOT_HEADER} ${ROOT_SOURCE})

file(GLOB COMP_HEADER Components/*.h)
file(GLOB COMP_SOURCE Components/*.cpp)
SOURCE_GROUP("Source Files\\Components" FILES ${COMP_HEADER} ${COMP_SOURCE})

file(GLOB GS_HEADER GameStates/*.h)
file(GLOB GS_SOURCE GameStates/*.cpp)
SOURCE_GROUP("Source Files\\GameStates" FILES ${GS_HEADER} ${GS_SOURCE})

file(GLOB MATH_HEADER Math/*.h)
file(GLOB MATH_SOURCE Math/*.cpp)
SOURCE_GROUP("Source Files\\Math" FILES ${MATH_HEADER} ${MATH_SOURCE})

file(GLOB SKILLS_HEADER Skills/*.h)
file(GLOB SKILLS_SOURCE Skills/*.cpp)
SOURCE_GROUP("Source Files\\Skills" FILES ${SKILLS_HEADER} ${SKILLS_SOURCE})

file(GLOB STATS_HEADER Stats/*.h)
file(GLOB STATS_SOURCE Stats/*.cpp)
SOURCE_GROUP("Source Files\\Stats" FILES ${STATS_HEADER} ${STATS_SOURCE})

set(SRCS
  ${TOTEM_HDRS} ${TOTEM_EXT_HDRS}
  ${ROOT_HEADER} ${ROOT_SOURCE}
  ${COMP_HEADER} ${COMP_SOURCE}
  ${GS_HEADER} ${GS_SOURCE}
  ${MATH_HEADER} ${MATH_SOURCE}
  ${SKILLS_HEADER} ${SKILLS_SOURCE}
  ${STATS_HEADER} ${STATS_SOURCE}
)
 
add_executable(${NAME} ${SRCS})

set_target_properties(${NAME} PROPERTIES DEBUG_POSTFIX -debug)
set_target_properties(${NAME} PROPERTIES FOLDER "Examples")

FIND_PACKAGE(LibTCOD REQUIRED)
TARGET_LINK_LIBRARIES(${NAME}   
	${TCOD_LIBRARY}
	${TCOD_GUI_LIBRARY}
)

include_directories(
  ${CMAKE_SOURCE_DIR}/depends/Standard/Examples/Roguelike/include/
  ${TCOD_INCLUDE}
)
