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
