#include <gtest/gtest.h>

#include "../../src/racing_lib/levelutil.h"

TEST(LevelUtil, findRoadSection_no_road_expect_exception) {
    Level level{1,500,{}};
    ASSERT_DEATH(LevelUtil::find_road_section(level, 0), "");
}

TEST(LevelUtil, findRoadSection_road_expect_first) {
    Level level{1,500,{{0,1}, {100, 2}}};
    const RoadSection& road = LevelUtil::find_road_section(level, 0);
    ASSERT_EQ(road.angle, 1);
}


TEST(LevelUtil, findRoadSection_road_expect_second) {
    Level level{1,500,{{0,1}, {100, 2}}};
    const RoadSection& road = LevelUtil::find_road_section(level, 110);
    ASSERT_EQ(road.angle, 2);
}
