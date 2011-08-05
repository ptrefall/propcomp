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
  ./EntityManager.h
  ./Vector3.h
)

set(SRCS
  ./main.cpp
  ./EntityManager.cpp
)
 
add_executable(TestElCar ${Component_HDRS} ${Component_SRCS} ${HDRS} ${SRCS})

set_target_properties(TestElCar PROPERTIES DEBUG_POSTFIX _d)
set_target_properties(TestElCar PROPERTIES FOLDER "Tests")


target_link_libraries(TestElCar
  EntitySystem
)
