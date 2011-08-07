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
# Note: Some of the libraries Component-based Entity Engine may link to may have additional
# requirements or restrictions.
#
###
# CMake system for Component-based Entity Engine was contributed by Jacob 'jacmoe' Moen
#
###

cmake_minimum_required(VERSION 2.8)
 
project(EntitySystem)

set(MinDepends_HDRS
	../depends/MinDepends/types.h
	../depends/MinDepends/sigslot.h
)
SOURCE_GROUP("Header Files\\Types\\MinDepends" FILES ${MinDepends_HDRS})

set(ClanLib_HDRS
	../depends/ClanLib/types.h
)
SOURCE_GROUP("Header Files\\Types\\ClanLib" FILES ${ClanLib_HDRS})

set(Boost_HDRS
	../depends/Boost/types.h
)
SOURCE_GROUP("Header Files\\Types\\Boost" FILES ${Boost_HDRS})

set(HDRS
  ./Component.h
  ./ComponentFactory.h
  ./IProperty.h
  ./Property.h
  ./Entity.h
  ./types_config.h
)

set(SRCS
  ./ComponentFactory.cpp
  ./Entity.cpp
)
 
add_library(EntitySystem STATIC  ${MinDepends_HDRS} ${ClanLib_HDRS} ${Boost_HDRS} ${HDRS} ${SRCS})

set_target_properties(EntitySystem PROPERTIES DEBUG_POSTFIX _d)
