cmake_minimum_required(VERSION 2.8)
 
project(EntitySystem)
 
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
 
add_library(EntitySystem STATIC ${HDRS} ${SRCS})

set_target_properties(EntitySystem PROPERTIES DEBUG_POSTFIX _d)
