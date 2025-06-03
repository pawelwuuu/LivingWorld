cmake_minimum_required(VERSION 3.22)
project(LivingWorldGui)

set(CMAKE_CXX_STANDARD 20)

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)

# Include directories
include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIRS}
        src/
        src/organisms/
        src/organisms/animal
        src/organisms/animal/sheep
        src/organisms/animal/wolf
        src/organisms/organism
        src/organisms/plant
        src/organisms/plant/grass
        src/organisms/plant/dandelion
        src/organisms/plant/toadstool
        src/world
        src/world/managers/movementManager
        src/world/managers/interactionManager
)

# List all source files
set(SOURCE_FILES
        src/LivingWorld.cpp
        src/gui/LifeGameRenderer.cpp

        # World
        src/world/World.cpp
        src/world/Position.cpp

        # Managers
        src/world/managers/movementManager/DefaultMovementManager.h
        src/world/managers/interactionManager/DefaultInteractionManager.h

        # Organisms
        src/organisms/organism/Organism.cpp
        src/organisms/animal/Animal.cpp
        src/organisms/animal/sheep/Sheep.cpp
        src/organisms/animal/wolf/Wolf.cpp
        src/organisms/plant/Plant.cpp
        src/organisms/plant/grass/Grass.cpp
        src/organisms/plant/dandelion/Dandelion.cpp
        src/organisms/plant/toadstool/Toadstool.cpp
        src/organisms/organism/organismFactory/OrganismFactory.cpp
        src/gui/Application.cpp
        src/gui/Application.h
        src/world/PopulateWorld.cpp
        src/world/PopulateWorld.h
        src/world/managers/serializer/WorldSerializer.h
        src/world/managers/serializer/binarySerializer/BinarySerialzer.cpp
        src/world/managers/serializer/binarySerializer/BinarySerialzer.h
)

# Create single executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIBRARY}
)

if (MINGW)
    target_link_options(${PROJECT_NAME} PRIVATE "-Wl,-subsystem,console")
endif()