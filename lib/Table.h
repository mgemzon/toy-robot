#pragma once

namespace toy_robot
{
    class Table
    {
    public:

        /**
         * @brief Construct a Table instance.
         * @throws std::invalid_argument if Table dimensions are invalid.
         */
        Table(int x, int y);
    
        /**
         * @brief Check if current location in table is valid.
         * @param[in] x location in x-axis of table.
         * @param[in] y location in y-axis of table.
         * @return true if valid location, false otherwise.
         */
        bool isValidLocation(int x, int y) const;
    
    private:
        int m_width;
        int m_height;    
    };
}
