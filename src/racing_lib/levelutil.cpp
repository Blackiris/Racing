#include "levelutil.h"

const RoadSection& LevelUtil::find_road_section(const Level &level, const unsigned int &z) {
    size_t idx = 0;
    for (RoadSection current_section : level.road_sections) {
        if (current_section.z_begin > z) {
            break;
        }
        idx++;
    }
    return level.road_sections[idx-1];
}
