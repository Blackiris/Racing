#include "levelutil.h"

RoadSection LevelUtil::findRoadSection(const Level &level, const unsigned int &z) {
    RoadSection section = level.road_sections.front();
    for (RoadSection current_section : level.road_sections) {
        if (current_section.z_begin > z) {
            break;
        }
        section = current_section;
    }
    return section;
}
