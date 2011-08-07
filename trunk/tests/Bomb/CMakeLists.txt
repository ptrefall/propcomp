cmake_minimum_required(VERSION 2.8.3)

project(TestBomb)

add_subdirectory(Components)

set(Component_HDRS
  ./Components/Health.h
  ./Components/Explosive.h
  ./Components/Timer.h
  ./Components/MultiTargeter.h
  ./Components/RadiusTargetSeeker.h
  ./Components/Transformable.h
)

SOURCE_GROUP("Header Files\\Components" FILES ${Component_HDRS})

set(Component_SRCS
  ./Components/Health.cpp
  ./Components/Explosive.cpp
  ./Components/Timer.cpp
  ./Components/MultiTargeter.cpp
  ./Components/RadiusTargetSeeker.cpp
  ./Components/Transformable.cpp
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
 
add_executable(TestBomb ${Component_HDRS} ${Component_SRCS} ${HDRS} ${SRCS})

set_target_properties(TestBomb PROPERTIES DEBUG_POSTFIX _d)
set_target_properties(TestBomb PROPERTIES FOLDER "Tests")


target_link_libraries(TestBomb
  EntitySystem
)
