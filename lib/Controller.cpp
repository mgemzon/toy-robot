#include "Controller.h"

#include <cstring>
#include <iostream>
#include <regex>

namespace
{
    /**
     * @brief Trim leading and trailing whitespaces.
     * @param input string to be trimmed.
     * @return a trimmed string, if input is all whitespaces or
     * an empty string, it returns an empty string.
     */
    std::string trimInput(std::string& input)
    {
        size_t first = input.find_first_not_of(" \t\r\n");
        size_t last = input.find_last_not_of(" \t\r\n");

        if (first == std::string::npos || last == std::string::npos) {
            return "";
        }

        return input.substr(first, (last - first + 1));
    }
}

namespace toy_robot
{
    Controller::Controller(std::unique_ptr<RobotInterface> robot,
                           std::shared_ptr<Table> table)
    {
        if (robot == nullptr || table == nullptr)
        {
            throw std::invalid_argument("Robot and/or table must not be a nullptr.");
        }
        m_robot = std::move(robot);
        m_table = table;
    }

    bool Controller::processInput(std::string& input)
    {
        input = trimInput(input);

        if (input.empty())
        {
            return false;
        }

        if (input.substr(0, std::strlen("PLACE")) == "PLACE")
        {
            std::regex placeCommandPattern("PLACE (\\d+),(\\d+),(NORTH|EAST|WEST|SOUTH)$");
            std::smatch match;
            if (std::regex_search(input, match, placeCommandPattern))
            {
                int x;
                int y;

                try
                {
                    x = std::stoi(match.str(1));
                    y = std::stoi(match.str(2));
                }
                catch (...)
                {
                    return false;
                }

                Direction direction;

                if (match.str(3) == "NORTH")
                {
                    direction = Direction::NORTH;
                }
                else if (match.str(3) == "EAST")
                {
                    direction = Direction::EAST;
                }
                else if (match.str(3) == "WEST")
                {
                    direction = Direction::WEST;
                }
                else if (match.str(3) == "SOUTH")
                {
                    direction = Direction::SOUTH;
                }
                else
                {
                    return false;
                }
                
                m_robot->place(x, y, m_table, direction);
            }
            else
            {
                return false;
            }
        }
        else if (input == "MOVE")
        {
            m_robot->move();
        }
        else if (input == "LEFT")
        {
            m_robot->left();
        }
        else if (input == "RIGHT")
        {
            m_robot->right();
        }
        else if (input == "REPORT")
        {
            std::string robotReport = m_robot->report();
            if (! robotReport.empty())
            {
                std::cout << robotReport << std::endl;
            }
        }
        else
        {
            // Comment out logs, not in specs.
            // std::cout << "Unkown command" << std::endl;
            return false;
        }

        return true;
    }
}
