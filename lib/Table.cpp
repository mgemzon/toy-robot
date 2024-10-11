#include <stdexcept>

#include "Table.h"

namespace toy_robot
{
    Table::Table(int width, int height)
    {
        if (width < 0 || height < 0)
        {
            throw std::invalid_argument("Width or height must not be negative.");
        }
        m_width = width;
        m_height = height;
    }
    
    bool Table::isValidLocation(int x, int y) const
    {
        return ((x >= 0) && (x < m_width)) && ((y >= 0 ) && (y < m_height));
    }
}

    