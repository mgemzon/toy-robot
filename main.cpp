#include "Controller.h"
#include "Robot.h"

#include <iostream>

using namespace toy_robot;

int main()
{
    const int TABLE_WIDTH = 5;
    const int TABLE_HEIGHT = 5;

    std::unique_ptr<Robot> robot = std::make_unique<Robot>();
    std::shared_ptr<Table> table;
    
    try
    {
        table = std::make_shared<Table>(TABLE_WIDTH, TABLE_HEIGHT);
    }
    catch(std::invalid_argument const& e)
    {
        std::cerr << "Failed to initialize table: " << e.what() << std::endl;
        return -1;
    }
    
    try
    {
        Controller controller(std::move(robot), table);

        std::string input;

        while (std::getline(std::cin, input))
        {
            controller.processInput(input);
        }
    }
    catch(std::invalid_argument const& e)
    {
        std::cerr << "Failed to initialize controller: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}