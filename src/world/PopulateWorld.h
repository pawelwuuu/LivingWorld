#pragma once

#include <world/World.h>

// Losowe umieszczenie zadanej liczby organizmów w świecie.
void populateWorld(World& world,
                   int grassCount,
                   int sheepCount,
                   int wolfCount,
                   int dandelionCount,
                   int toadstoolCount);
