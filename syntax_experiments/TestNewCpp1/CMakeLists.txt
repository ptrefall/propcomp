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
 
project(TestNewCpp1)

set(Standard_HDRS
	../../depends/Standard/sigslot.h
	../../depends/Standard/cdiggins_any.h
	../../depends/Standard/FastDelegate.h
	../../depends/Standard/FastDelegateBind.h
)
SOURCE_GROUP("Header Files\\Depends" FILES ${Standard_HDRS})

set(HDRS
  ./Component.h
  ./ComponentContainer.h
  ./ComponentFactory.h
  ./PoolComponentFactory.h
  ./IProperty.h
  ./SharedProperty.h
  ./SharedPropertyContainer.h
  ./Property.h
  ./PropertyContainer.h
  ./Entity.h
  ./TestSystem.h
  ./TestComponent.h
)

set(SRCS
  ./main.cpp
  ./Component.cpp
  ./ComponentContainer.cpp
  ./ComponentFactory.cpp
  ./PoolComponentFactory.cpp
  ./SharedProperty.cpp
  ./SharedPropertyContainer.cpp
  ./Property.cpp
  ./PropertyContainer.cpp
  ./TestSystem.cpp
  ./TestComponent.cpp
)
 
add_executable(TestNewCpp1 ${Standard_HDRS} ${HDRS} ${SRCS})

set_target_properties(TestNewCpp1 PROPERTIES DEBUG_POSTFIX -debug)
