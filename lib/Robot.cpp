#include "Robot.h"
#include <sstream>

namespace toy_robot
{
    Robot::Robot() :
        m_x(-1),
        m_y(-1),
        m_direction(Direction::UNINITIALIZED),
        m_isPlaced(false)
    {
    }

    bool Robot::place(int x, int y, std::shared_ptr<Table> table, Direction direction)
    {
        m_table = table;
        if (! m_table->isValidLocation(x, y))
        {
            return false;
        }

        m_direction = direction;
        m_x = x;
        m_y = y;
        m_isPlaced = true;

        return true;
    }

    bool Robot::move()
    {
        if (! m_isPlaced)
        {
            return false;
        }

        int next_x = m_x;
        int next_y = m_y;

        switch (m_direction)
        {
            case Direction::NORTH:
                next_y = m_y + 1;
                break;
            case Direction::SOUTH:
                next_y = m_y - 1;
                break;
            case Direction::EAST:
                next_x = m_x + 1;
                break;
            case Direction::WEST:
                next_x = m_x - 1;
                break;
        }

        if (! m_table->isValidLocation(next_x, next_y))
        {
            return false;
        }

        m_x = next_x;
        m_y = next_y;

        return true;
    }

    bool Robot::left()
    {
        if (! m_isPlaced)
        {
            return false;
        }
        
        switch (m_direction)
        {
            case Direction::NORTH:
                m_direction = Direction::WEST;
                break;
            case Direction::SOUTH:
                m_direction = Direction::EAST;
                break;
            case Direction::EAST:
                m_direction = Direction::NORTH;
                break;
            case Direction::WEST:
                m_direction = Direction::SOUTH;
                break;
        }

        return true;
    }

    bool Robot::right()
    {
        if (! m_isPlaced)
        {
            return false;
        }
        
        switch (m_direction)
        {
            case Direction::NORTH:
                m_direction = Direction::EAST;
                break;
            case Direction::SOUTH:
                m_direction = Direction::WEST;
                break;
            case Direction::EAST:
                m_direction = Direction::SOUTH;
                break;
            case Direction::WEST:
                m_direction = Direction::NORTH;
                break;
        }

        return true;
    }

    std::string Robot::report() const
    {
        if (! m_isPlaced)
        {
            return "";
        }

        std::ostringstream report;
        std::string directionString;

        switch (m_direction)
        {
            case Direction::NORTH:
                directionString = "NORTH";
                break;
            case Direction::SOUTH:
                directionString = "SOUTH";
                break;
            case Direction::EAST:
                directionString = "EAST";
                break;
            case Direction::WEST:
                directionString = "WEST";
                break;
        }

        report << "Output: " << m_x << "," << m_y << "," << directionString;

        return report.str();
    }

    Direction Robot::getDirection() const
    {
        return m_direction;
    }
}
