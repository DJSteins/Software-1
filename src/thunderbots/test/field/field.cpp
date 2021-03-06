#include "ai/world/field.h"
#include <gtest/gtest.h>

TEST(FieldTest, construction)
{
    Field field = Field();

    EXPECT_FALSE(field.valid());
    EXPECT_DOUBLE_EQ(0, field.length());
    EXPECT_DOUBLE_EQ(0, field.width());
    EXPECT_DOUBLE_EQ(0, field.goalWidth());
    EXPECT_DOUBLE_EQ(0, field.centreCircleRadius());
    EXPECT_DOUBLE_EQ(0, field.defenseAreaWidth());
    EXPECT_DOUBLE_EQ(0, field.defenseAreaLength());
}

TEST(FieldTest, update_and_accessors)
{
    Field field                 = Field();
    double length               = 9.0;
    double width                = 6.0;
    double goal_width           = 1.0;
    double defense_width        = 2.0;
    double defense_length       = 1.0;
    double boundary_width       = 0.3;
    double center_circle_radius = 0.5;

    field.updateDimensions(
        length, width, defense_length, defense_width, goal_width, boundary_width,
        center_circle_radius);

    EXPECT_TRUE(field.valid());

    EXPECT_DOUBLE_EQ(9.6, field.totalLength());
    EXPECT_DOUBLE_EQ(6.6, field.totalWidth());
    EXPECT_DOUBLE_EQ(0.3, boundary_width);

    EXPECT_EQ(Point(-4.5, 0.0), field.friendlyGoal());
    EXPECT_EQ(Point(4.5, 0.0), field.enemyGoal());

    EXPECT_EQ(Point(-4.5, 1.0), field.friendlyGoalpostPos());
    EXPECT_EQ(Point(-4.5, -1.0), field.friendlyGoalpostNeg());
    EXPECT_EQ(Point(4.5, 1.0), field.enemyGoalpostPos());
    EXPECT_EQ(Point(4.5, -1.0), field.enemyGoalpostNeg());

    EXPECT_EQ(Point(-3.5, 0.0), field.penaltyFriendly());
    EXPECT_EQ(Point(3.5, 0.0), field.penaltyEnemy());

    EXPECT_EQ(Point(-4.5, 3.0), field.friendlyCornerPos());
    EXPECT_EQ(Point(-4.5, -3.0), field.friendlyCornerNeg());
    EXPECT_EQ(Point(4.5, 3.0), field.enemyCornerPos());
    EXPECT_EQ(Point(4.5, -3.0), field.enemyCornerNeg());
}

TEST(FieldTest, equality_operators)
{
    double length               = 9.0;
    double width                = 6.0;
    double goal_width           = 1.0;
    double defense_width        = 2.0;
    double defense_length       = 1.0;
    double boundary_width       = 0.3;
    double center_circle_radius = 0.5;

    Field invalid_field = Field();

    Field field = Field();
    field.updateDimensions(
        length, width, goal_width, defense_length, defense_width, boundary_width,
        center_circle_radius);

    Field field_other = Field();
    field_other.updateDimensions(
        length, width, goal_width, defense_length, defense_width, boundary_width,
        center_circle_radius);

    EXPECT_EQ(invalid_field, invalid_field);
    EXPECT_NE(invalid_field, field);
    EXPECT_NE(invalid_field, field_other);
    EXPECT_EQ(field, field_other);
    EXPECT_EQ(field, field);

    // Update with the same dimensions as above, except for a slightly larger length
    field_other.updateDimensions(
        length + 0.02, width, goal_width, defense_length, defense_width, boundary_width,
        center_circle_radius);

    EXPECT_NE(field, field_other);
    EXPECT_NE(field_other, field);
    EXPECT_NE(invalid_field, field_other);
    EXPECT_NE(field_other, invalid_field);
    EXPECT_EQ(field_other, field_other);
}

int main(int argc, char **argv)
{
    std::cout << argv[0] << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
