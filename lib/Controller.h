#pragma once

#include "RobotInterface.h"

#include <memory>
#include <string>

namespace toy_robot
{
    class Controller
    {
    public:
        /**
         * @brief Construct a Robot instance. 
         * @throws when robot and/or table is a nullptr.
         */
        Controller(std::unique_ptr<RobotInterface> robot, std::shared_ptr<Table> table);

        /**
         * @brief Read and check if input is a valid command. If command is valid
         * it performs robot operations i.e. MOVE, LEFT, RIFHT, REPORT, PLACE.
         * @return true if it is able to process a valid command, false otherwise.
         */
        bool processInput(std::string& input);
    
    private:
        std::unique_ptr<RobotInterface> m_robot;
        std::shared_ptr<Table> m_table;
    };
}

