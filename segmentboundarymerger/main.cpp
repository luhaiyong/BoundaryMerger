#include <iostream>
#include <gtest/gtest.h>
#include "SegmentMerger.h"

//TEST(Fortest, add) {
//    EXPECT_EQ(5,5);
//}

TEST(SEGMENTMERGERTEST,addCollection_onecollection)
{
    SegmentMerger segmentMerger;
    segmentMerger.addCollection({Point(-1),Point(1)});
    auto points = segmentMerger.getMergedPoint();
    ASSERT_EQ(2,points.size());
    EXPECT_DOUBLE_EQ(-1,points[0].x);
    EXPECT_DOUBLE_EQ(1,points[1].x);
}

TEST(SEGMENTMERGERTEST,addCollection_twocollection_nooverlap)
{
    SegmentMerger segmentMerger;
    segmentMerger.addCollection({Point(-1),Point(1)});
    segmentMerger.addCollection({Point(2),Point(4)});
    auto points = segmentMerger.getMergedPoint();
    ASSERT_EQ(4,points.size());
    EXPECT_DOUBLE_EQ(-1,points[0].x);
    EXPECT_DOUBLE_EQ(1,points[1].x);
    EXPECT_DOUBLE_EQ(2,points[2].x);
    EXPECT_DOUBLE_EQ(4,points[3].x);
}

TEST(SEGMENTMERGERTEST,addCollection_twocollection_overlap)
{
    SegmentMerger segmentMerger;
    segmentMerger.addCollection({Point(-1),Point(1)});
    segmentMerger.addCollection({Point(0),Point(4)});
    auto points = segmentMerger.getMergedPoint();
    ASSERT_EQ(3,points.size());
    EXPECT_DOUBLE_EQ(-1,points[0].x);
    EXPECT_DOUBLE_EQ(1,points[1].x);
    EXPECT_DOUBLE_EQ(4,points[2].x);
}

TEST(SEGMENTMERGERTEST,allcoverd_shoulddiscardall)
{
    SegmentMerger segmentMerger;
    segmentMerger.addCollection({Point(-1),Point(1)});
    segmentMerger.addCollection({Point(0),Point(0.5)});
    auto points = segmentMerger.getMergedPoint();
    ASSERT_EQ(2,points.size());
    EXPECT_DOUBLE_EQ(-1,points[0].x);
    EXPECT_DOUBLE_EQ(1,points[1].x);
}

TEST(SEGMENTMERGERTEST,covering_exsiting_all)
{
    SegmentMerger segmentMerger;
    segmentMerger.addCollection({Point(-3),Point(-1)});
    segmentMerger.addCollection({Point(1),Point(3)});
    segmentMerger.addCollection({Point(5),Point(7)});
    segmentMerger.addCollection({Point(-5),Point(-2),Point(0),Point(2),Point(4),Point(6),Point(8)});
    auto points = segmentMerger.getMergedPoint();
    ASSERT_EQ(10,points.size());
    EXPECT_DOUBLE_EQ(-5,points[0].x);
    EXPECT_DOUBLE_EQ(8,points[9].x);
}

TEST(SEGMENTMERGERTEST,covering_exsiting_all_2)
{
    SegmentMerger segmentMerger;
    segmentMerger.addCollection({Point(-3),Point(-1)});
    segmentMerger.addCollection({Point(1),Point(3)});
    segmentMerger.addCollection({Point(5),Point(7)});
    segmentMerger.addCollection({Point(-5),Point(-2),Point(0),Point(2),Point(4),Point(6)});
    auto points = segmentMerger.getMergedPoint();
    ASSERT_EQ(9,points.size());
    EXPECT_DOUBLE_EQ(-5,points[0].x);
    EXPECT_DOUBLE_EQ(7,points[8].x);
}


GTEST_API_ int main() {
    std::cout << "Hello, World!" << std::endl;
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
