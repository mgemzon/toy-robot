#pragma once

#include "RobotInterface.h"

namespace toy_robot
{
    class Robot : public RobotInterface
    {
    public:
        /**
         * @brief Construct a Robot instance. 
         */
        Robot();

        /**
         * @brief Places robot on a table. It makes sure that robot is placed in a
         * valid location on the table.
         * @param[in] x x-coordinate on where to place the robot.
         * @param[in] y y-coordinate on where to place the robot.
         * @param[in] table table object where to place the robot.
         * @param[in] direction direction where the robot is facing.
         *
         * @return true if robot is placed, false otherwise.
         */
        bool place(int x, int y, std::shared_ptr<Table> table, Direction direction) override;
        
        /**
         * @brief Move the robot one unit to the direction it is currently facing.
         * It may not perform this operation if robot is not placed yet.
         * @return true if move operation is successful, false otherwise.
         */
        bool move() override;

        /**
         * @brief Rotate the robot 90 degrees to the left i.e. if it is currently
         * facing NORTH, it would face WEST after this operation. It may not
         * perform this operation if robot is not placed yet.
         * @return true if move operation is successful, false otherwise.
         */
        bool left() override;

        /**
         * @brief Rotate the robot 90 degrees to the right i.e. if it is currently
         * facing NORTH, it would face EAST after this operation. It may not
         * perform this operation if robot is not placed yet.
         * @return true if move operation is successful, false otherwise.
         */
        bool right() override;
        
        /**
         * @brief Report the current status of the robot regarding its position on
         * the table and the direction it is facing. It may not perform this operation
         * if robot is not placed yet.
         * @return std::string with format of 'Output: <x>,<y>,<direction>'. Returns an
         * empty string if robotis not placed yet.
         */
        std::string report() const override;

        /**
         * @brief Get direction the robot is facing.
         * @return Direction of robot. Returns 'Direction::UNINITIALIZED' when robot
         * is not placed yet.
         */
        Direction getDirection() const override;

    private:
        int m_x;
        int m_y;
        Direction m_direction;
        bool m_isPlaced;
        std::shared_ptr<Table> m_table;
    };
}