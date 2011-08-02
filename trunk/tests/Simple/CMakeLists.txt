cmake_minimum_required(VERSION 2.8.3)

project(TestSimple)

set(SRCS
  ./main.cpp
)
 
add_executable(TestSimple ${SRCS})

set_target_properties(TestSimple PROPERTIES DEBUG_POSTFIX _d)
set_target_properties(TestSimple PROPERTIES FOLDER "Tests")


target_link_libraries(TestSimple
  EntitySystem
)
