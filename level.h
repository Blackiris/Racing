#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

struct RoadSection {
    unsigned int z_begin = 0;
    int angle = 0;
};

struct Level {
    unsigned int nb_lanes = 1;
    unsigned int end_line_z = 0;
    std::vector<RoadSection> road_sections;
};


#endif // LEVEL_H
