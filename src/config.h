#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>

// Global Variables
const uint64_t NUM_BLOCKS = 20;
const uint64_t BLOCK_SIZE = 3;
const uint64_t BUILDINGS_PER_BLOCK = 5;
const uint64_t VISUAL_RANGE = 10;

// the maximum dimensions for the "city" or grid that the robot will be moving
// on, coordinates x and y that are greater than or equal to the grid max are
// deemed invalid locations and boundary checks shall be done to prevent such
// moves
const uint64_t GRID_DIMENSIONS = (NUM_BLOCKS * (BLOCK_SIZE + 1)) + 1;

#endif