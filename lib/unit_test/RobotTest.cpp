#include <gtest/gtest.h>

#include "Robot.h"

using namespace toy_robot;

const int TABLE_WIDTH = 5;
const int TABLE_HEIGHT = 5;

class RobotTest : public ::testing::Test
{
protected:
    std::shared_ptr<Table> table;
    Robot robot;

    void SetUp() override
    {
        table = std::make_shared<Table>(TABLE_WIDTH, TABLE_HEIGHT);
    }
};

TEST_F(RobotTest, PlaceRobotOnValidTableLocations)
{
    EXPECT_TRUE(robot.place(0, 0, table, Direction::NORTH));
    EXPECT_EQ(robot.report(), "Output: 0,0,NORTH");

    EXPECT_TRUE(robot.place(0, 4, table, Direction::EAST));
    EXPECT_EQ(robot.report(), "Output: 0,4,EAST");
    
    EXPECT_TRUE(robot.place(4, 0, table, Direction::SOUTH));
    EXPECT_EQ(robot.report(), "Output: 4,0,SOUTH");
     
    EXPECT_TRUE(robot.place(4, 4, table, Direction::WEST));
    EXPECT_EQ(robot.report(), "Output: 4,4,WEST");
}

TEST_F(RobotTest, PlaceRobotOnInvalidLocations)
{
    EXPECT_FALSE(robot.place(-1, 0, table, Direction::NORTH));
    EXPECT_EQ(robot.report(), "");

    EXPECT_FALSE(robot.place(0, -1, table, Direction::EAST));
    EXPECT_EQ(robot.report(), "");
    
    EXPECT_FALSE(robot.place(5, 0, table, Direction::SOUTH));
    EXPECT_EQ(robot.report(), "");
    
    EXPECT_FALSE(robot.place(0, 5, table, Direction::WEST));
    EXPECT_EQ(robot.report(), "");
    
    EXPECT_FALSE(robot.place(-1, 5, table, Direction::NORTH));
    EXPECT_EQ(robot.report(), "");
    
    EXPECT_FALSE(robot.place(5, -1, table, Direction::EAST));
    EXPECT_EQ(robot.report(), "");
}

TEST_F(RobotTest, RotateLeft)
{
    EXPECT_EQ(robot.report(), "");
    EXPECT_TRUE(robot.place(0, 0, table, Direction::NORTH));
    EXPECT_EQ(robot.report(), "Output: 0,0,NORTH");

    EXPECT_TRUE(robot.left());
    EXPECT_EQ(robot.getDirection(), Direction::WEST);
    EXPECT_EQ(robot.report(), "Output: 0,0,WEST");
    
    EXPECT_TRUE(robot.left());
    EXPECT_EQ(robot.getDirection(), Direction::SOUTH);
    EXPECT_EQ(robot.report(), "Output: 0,0,SOUTH");

    EXPECT_TRUE(robot.left());
    EXPECT_EQ(robot.getDirection(), Direction::EAST);
    EXPECT_EQ(robot.report(), "Output: 0,0,EAST");

    EXPECT_TRUE(robot.left());
    EXPECT_EQ(robot.getDirection(), Direction::NORTH);
    EXPECT_EQ(robot.report(), "Output: 0,0,NORTH");
}

TEST_F(RobotTest, RotateRight)
{
    EXPECT_EQ(robot.report(), "");
    EXPECT_TRUE(robot.place(0, 0, table, Direction::NORTH));
    EXPECT_EQ(robot.report(), "Output: 0,0,NORTH");

    EXPECT_TRUE(robot.right());
    EXPECT_EQ(robot.getDirection(), Direction::EAST);
    EXPECT_EQ(robot.report(), "Output: 0,0,EAST");

    EXPECT_TRUE(robot.right());
    EXPECT_EQ(robot.getDirection(), Direction::SOUTH);
    EXPECT_EQ(robot.report(), "Output: 0,0,SOUTH");

    EXPECT_TRUE(robot.right());
    EXPECT_EQ(robot.getDirection(), Direction::WEST);
    EXPECT_EQ(robot.report(), "Output: 0,0,WEST");

    EXPECT_TRUE(robot.right());
    EXPECT_EQ(robot.getDirection(), Direction::NORTH);
    EXPECT_EQ(robot.report(), "Output: 0,0,NORTH");
}

TEST_F(RobotTest, UnplacedRobotAndPerformMove)
{
    EXPECT_FALSE(robot.move());
}

TEST_F(RobotTest, UnplacedRobotAndPerformLeft)
{
    EXPECT_FALSE(robot.left());
}

TEST_F(RobotTest, UnplacedRobotAndPerformRight)
{
    EXPECT_FALSE(robot.right());
}

TEST_F(RobotTest, UnplacedRobotAndPerformReport)
{
    EXPECT_EQ(robot.report(), "");
}

TEST_F(RobotTest, PlaceRobotAndMoveAtTableEdge)
{
    EXPECT_TRUE(robot.place(0, 0, table, Direction::NORTH));
    EXPECT_EQ(robot.report(), "Output: 0,0,NORTH");
    
    for (int i = 0; i < TABLE_HEIGHT - 1; i++)
    {
        std::ostringstream report;
        report << "Output: "  << 0 << "," << i << ",NORTH";
        EXPECT_EQ(robot.report(), report.str());
        EXPECT_TRUE(robot.move());
    }

    // Robot shouldn't move one unit forward if next move is going to be
    // on an invalid location.
    EXPECT_EQ(robot.report(), "Output: 0,4,NORTH");
    EXPECT_FALSE(robot.move());
    EXPECT_EQ(robot.report(), "Output: 0,4,NORTH");
}
