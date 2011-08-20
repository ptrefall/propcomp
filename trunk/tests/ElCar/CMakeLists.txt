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
# Note: Some of the libraries Factotum EDK may link to may have additional
# requirements or restrictions.
#
###
# CMake system for Factotum EDK was contributed by Jacob 'jacmoe' Moen
#
###

cmake_minimum_required(VERSION 2.8.3)

project(TestElCar)

add_subdirectory(Components)

set(Component_HDRS
  ./Components/EnergyCharger.h
  ./Components/EnergyDecharger.h
  ./Components/Dynamo.h
  ./Components/WheelMount.h
  ./Components/Transformable.h
  ./Components/Throttle.h
  ./Components/AngularPhysics.h
  ./Components/LinearPhysics.h
)

SOURCE_GROUP("Header Files\\Components" FILES ${Component_HDRS})

set(Component_SRCS
  ./Components/EnergyCharger.cpp
  ./Components/EnergyDecharger.cpp
  ./Components/Dynamo.cpp
  ./Components/WheelMount.cpp
  ./Components/Transformable.cpp
  ./Components/Throttle.cpp
  ./Components/AngularPhysics.cpp
  ./Components/LinearPhysics.cpp
)

SOURCE_GROUP("Source Files\\Components" FILES ${Component_SRCS})

set(HDRS
  ../Common/EntityManager.h
  ../Common/Vector3.h
)

set(SRCS
  ./main.cpp
  ../Common/EntityManager.cpp
)
 
add_executable(TestElCar ${Component_HDRS} ${Component_SRCS} ${HDRS} ${SRCS})

set_target_properties(TestElCar PROPERTIES DEBUG_POSTFIX _d)
set_target_properties(TestElCar PROPERTIES FOLDER "Tests")


target_link_libraries(TestElCar
  FactotumEDK
)
