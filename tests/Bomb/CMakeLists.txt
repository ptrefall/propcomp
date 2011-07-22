cmake_minimum_required(VERSION 2.8.3)

project(TestBomb)

add_subdirectory(Components)

set(Component_HDRS
  ./Components/Health.h
  ./Components/Explosive.h
  ./Components/Timer.h
)

SOURCE_GROUP("Header Files\\Components" FILES ${Component_HDRS})

set(Component_SRCS
  ./Components/Health.cpp
  ./Components/Explosive.cpp
  ./Components/Timer.cpp
)

SOURCE_GROUP("Source Files\\Components" FILES ${Component_SRCS})

set(HDRS
  ./EntityManager.h
)

set(SRCS
  ./main.cpp
  ./EntityManager.cpp
)
 
add_executable(TestBomb ${Component_HDRS} ${Component_SRCS} ${HDRS} ${SRCS})

set_target_properties(TestBomb PROPERTIES DEBUG_POSTFIX _d)
set_target_properties(TestBomb PROPERTIES FOLDER "Tests")


target_link_libraries(TestBomb
  EntitySystem
)
