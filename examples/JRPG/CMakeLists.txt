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

project(ExampleJRPG)

add_subdirectory(Components)

set(Component_HDRS
  ./Components/Health.h
  ./Components/RadiusTargetSeeker.h
  ./Components/Transformable.h
)

SOURCE_GROUP("Header Files\\Components" FILES ${Component_HDRS})

set(Component_SRCS
  ./Components/Health.cpp
  ./Components/RadiusTargetSeeker.cpp
  ./Components/Transformable.cpp
)

SOURCE_GROUP("Source Files\\Components" FILES ${Component_SRCS})

set(HDRS
  ../../include/Totem/Addons/TemplateEventHandler.h
  ../../include/Totem/Addons/DelegateHandler.h
  ../Common/Entity.h
  ../Common/EntityManager.h
  ../Common/Vector3.h
)

set(SRCS
  ./main.cpp
  ../../src/Addons/TemplateEventHandler.cpp
  ../../src/Addons/DelegateHandler.cpp
  ../Common/EntityManager.cpp
)
 
add_executable(ExampleJRPG ${Component_HDRS} ${Component_SRCS} ${HDRS} ${SRCS})

set_target_properties(ExampleJRPG PROPERTIES DEBUG_POSTFIX _d)
set_target_properties(ExampleJRPG PROPERTIES FOLDER "Examples")


target_link_libraries(ExampleJRPG
  TotemEDK
)
