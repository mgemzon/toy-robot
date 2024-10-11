#include "Controller.h"
#include "RobotInterface.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

using namespace toy_robot;

const int TABLE_WIDTH = 5;
const int TABLE_HEIGHT = 5;

class MockRobot : public RobotInterface
{
public:
    MOCK_METHOD(bool, place, (int x, int y, std::shared_ptr<Table> table, Direction direction), (override));
    MOCK_METHOD(bool, move, (), (override));
    MOCK_METHOD(bool, left, (), (override));
    MOCK_METHOD(bool, right, (), (override));
    MOCK_METHOD(std::string, report, (), (const, override));
    MOCK_METHOD(Direction, getDirection, (), (const, override));
};

class ControllerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        m_table = std::make_shared<Table>(TABLE_WIDTH, TABLE_HEIGHT);
        m_mockRobot = std::make_unique<MockRobot>();
        pMockRobot = m_mockRobot.get();
        m_controller = std::make_unique<Controller>(std::move(m_mockRobot), m_table);
    }

    std::unique_ptr<MockRobot> m_mockRobot;
    MockRobot* pMockRobot {nullptr};
    std::shared_ptr<Table> m_table;
    std::unique_ptr<Controller> m_controller;
};

TEST_F(ControllerTest, PassingValidPlaceCommands)
{
    // Check that when issuing valid PLACE commands, only place() method
    // of robot is getting called. This also checks that the arguements of
    // PLACE commands (x, y, and direction) is passed properly.

    std::vector<std::string> validPlaceCommands {
        "PLACE 0,0,NORTH",
        "PLACE 2,5,EAST",
        "PLACE 11,2,WEST",
        "PLACE 0,2,SOUTH",
        "PLACE 1,3,EAST",
        "PLACE 5,2,EAST   ",
        "   PLACE 2,12,WEST"
    };
    
    EXPECT_CALL(*pMockRobot, place(0, 0, m_table, Direction::NORTH))
        .Times(1);
    EXPECT_CALL(*pMockRobot, place(2, 5, m_table, Direction::EAST))
        .Times(1);
    EXPECT_CALL(*pMockRobot, place(11, 2, m_table, Direction::WEST))
        .Times(1);
    EXPECT_CALL(*pMockRobot, place(0, 2, m_table, Direction::SOUTH))
        .Times(1);
    EXPECT_CALL(*pMockRobot, place(1, 3, m_table, Direction::EAST))
        .Times(1);
    EXPECT_CALL(*pMockRobot, place(5, 2, m_table, Direction::EAST))
        .Times(1);
    EXPECT_CALL(*pMockRobot, place(2, 12, m_table, Direction::WEST))
        .Times(1);

    EXPECT_CALL(*pMockRobot, move()).Times(0);
    EXPECT_CALL(*pMockRobot, left()).Times(0);
    EXPECT_CALL(*pMockRobot, right()).Times(0);
    EXPECT_CALL(*pMockRobot, report()).Times(0);


    for (std::string& command : validPlaceCommands)
    {
        EXPECT_TRUE(m_controller->processInput(command));
    }
}

TEST_F(ControllerTest, PassingValidMoveCommands)
{
    // Check that when issuing valid MOVE commands, only move() method
    // of robot is getting called. 

    std::vector<std::string> validMoveCommands {
        "MOVE",
        "   MOVE",
        "MOVE"
    };
    
    EXPECT_CALL(*pMockRobot, move())
        .Times(validMoveCommands.size());
    
    EXPECT_CALL(*pMockRobot, place(testing::_, testing::_, testing::_, testing::_))
        .Times(0);
    EXPECT_CALL(*pMockRobot, left()).Times(0);
    EXPECT_CALL(*pMockRobot, right()).Times(0);
    EXPECT_CALL(*pMockRobot, report()).Times(0);


    for (std::string& command : validMoveCommands)
    {
        EXPECT_TRUE(m_controller->processInput(command));
    }
}

TEST_F(ControllerTest, PassingValidLeftCommands)
{
    // Check that when issuing valid LEFT commands, only left() method
    // of robot is getting called. 

    std::vector<std::string> validLeftCommands {
        "LEFT",
        "   LEFT",
        "LEFT"
    };
    
    EXPECT_CALL(*pMockRobot, left())
        .Times(validLeftCommands.size());
    
    EXPECT_CALL(*pMockRobot, place(testing::_, testing::_, testing::_, testing::_))
        .Times(0);
    EXPECT_CALL(*pMockRobot, move()).Times(0);
    EXPECT_CALL(*pMockRobot, right()).Times(0);
    EXPECT_CALL(*pMockRobot, report()).Times(0);


    for (std::string& command : validLeftCommands)
    {
        EXPECT_TRUE(m_controller->processInput(command));
    }
}

TEST_F(ControllerTest, PassingValidRightCommands)
{
    // Check that when issuing valid RIGHT commands, only right() method
    // of robot is getting called.

    std::vector<std::string> validRightCommands {
        "RIGHT",
        "   RIGHT",
        "RIGHT"
    };
    
    EXPECT_CALL(*pMockRobot, right())
        .Times(validRightCommands.size());
    
    EXPECT_CALL(*pMockRobot, place(testing::_, testing::_, testing::_, testing::_))
        .Times(0);
    EXPECT_CALL(*pMockRobot, move()).Times(0);
    EXPECT_CALL(*pMockRobot, left()).Times(0);
    EXPECT_CALL(*pMockRobot, report()).Times(0);

    for (std::string& command : validRightCommands)
    {
        EXPECT_TRUE(m_controller->processInput(command));
    }
}

TEST_F(ControllerTest, PassingValidReportCommands)
{
    // Check that when issuing valid REPORT commands, only report() method
    // of robot is getting called.

    std::vector<std::string> validReportCommands {
        "REPORT",
        "   REPORT",
        "REPORT"
    };
    
    EXPECT_CALL(*pMockRobot, report())
        .Times(validReportCommands.size());
    
    EXPECT_CALL(*pMockRobot, place(testing::_, testing::_, testing::_, testing::_))
        .Times(0);
    EXPECT_CALL(*pMockRobot, move()).Times(0);
    EXPECT_CALL(*pMockRobot, left()).Times(0);
    EXPECT_CALL(*pMockRobot, right()).Times(0);

    for (std::string& command : validReportCommands)
    {
        EXPECT_TRUE(m_controller->processInput(command));
    }
}

TEST_F(ControllerTest, PassingInvalidCommands)
{
    // Check that when issuing invalid, no robot methods are getting
    // called.

    std::vector<std::string> invalidCommands {
        "",
        "   ",
        "move",
        "moVe",
        "place 1,2,NORTH",
        "right",
        "left",
        "report",
        "  report",
        "MovE",
        "PLACE    2,2,NORTH",
        "PLACE 2,1,EASTWEST"
    };

    EXPECT_CALL(*pMockRobot, place(testing::_, testing::_, testing::_, testing::_))
        .Times(0);
    EXPECT_CALL(*pMockRobot, move()).Times(0);
    EXPECT_CALL(*pMockRobot, left()).Times(0);
    EXPECT_CALL(*pMockRobot, right()).Times(0);
    EXPECT_CALL(*pMockRobot, report()).Times(0);

    for (std::string& command : invalidCommands)
    {
        EXPECT_FALSE(m_controller->processInput(command));
    }
}

TEST(ControllerConstructorTest, InvalidArguments)
{
    std::unique_ptr<MockRobot> robot;
    std::shared_ptr<Table> table;

    // Uninitialized Robot and/or Table throws Controller constructor
    EXPECT_THROW(Controller(std::move(robot), table), std::invalid_argument);
    
    table = std::make_shared<Table>(TABLE_WIDTH, TABLE_HEIGHT);
    EXPECT_THROW(Controller(std::move(robot), table), std::invalid_argument);

    table.reset();
    robot = std::make_unique<MockRobot>();
    EXPECT_THROW(Controller(std::move(robot), table), std::invalid_argument);
}
