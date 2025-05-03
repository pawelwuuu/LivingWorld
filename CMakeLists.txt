cmake_minimum_required(VERSION 3.16)
project(LivingWorld)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        organisms/animal
        organisms/animal/sheep
        organisms/organism
        organisms/plant
        world
)

add_executable(LivingWorld
        LivingWorld.cpp
        organisms/animal/Animal.cpp
        organisms/animal/sheep/Sheep.cpp
        organisms/organism/Organism.cpp
        organisms/plant/Plant.cpp
        world/Position.cpp
        world/World.cpp
        world/managers/movementManager/IMovementManager.h
        world/managers/movementManager/DefaultMovementManager.h
        world/managers/interactionManager/IInteractionManager.h
        world/managers/interactionManager/DefaultInteractionManager.h
        organisms/plant/grass/Grass.cpp
        organisms/plant/grass/Grass.h
        organisms/animal/wolf/Wolf.cpp
        organisms/animal/wolf/Wolf.h
        organisms/plant/dandelion/Dandelion.cpp
        organisms/plant/dandelion/Dandelion.h
        organisms/plant/toadstool/Toadstool.cpp
        organisms/plant/toadstool/Toadstool.h
)
