#include <gtest/gtest.h>

#include "Table.h"

using namespace toy_robot;

const int TABLE_WIDTH = 5;
const int TABLE_HEIGHT = 5;
const int INVALID_TABLE_WIDTH = -1;
const int INVALID_TABLE_HEIGHT = -1;

TEST(TableTest, InvalidConstructorArguments)
{
    EXPECT_THROW(Table tableInvalidWidth = Table(INVALID_TABLE_WIDTH, TABLE_HEIGHT),
                 std::invalid_argument);
    EXPECT_THROW(Table tableInvalidWidth = Table(TABLE_WIDTH, INVALID_TABLE_HEIGHT),
                 std::invalid_argument);
    EXPECT_THROW(Table tableInvalidWidth = Table(INVALID_TABLE_WIDTH,
                                                 INVALID_TABLE_HEIGHT),
                 std::invalid_argument);                          
}

TEST(TableTest, ValidLocations)
{
    Table table = Table(TABLE_WIDTH, TABLE_HEIGHT);
    
    for (int x = 0; x < TABLE_WIDTH; x++)
    {
        for (int y = 0; y < TABLE_HEIGHT; y++)
        {
            EXPECT_TRUE(table.isValidLocation(x, y));
        }
    }
}

TEST(TableTest, InvalidLocations)
{
    Table table = Table(TABLE_WIDTH, TABLE_HEIGHT);

    EXPECT_FALSE(table.isValidLocation(-1, -1));
    EXPECT_FALSE(table.isValidLocation(5, 0));
    EXPECT_FALSE(table.isValidLocation(0, 5));
    EXPECT_FALSE(table.isValidLocation(5, 5));
}
