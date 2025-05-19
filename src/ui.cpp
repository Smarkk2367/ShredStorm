#include "../include/ui.h"
#include <iostream>
#include <fstream>

namespace shredstorm
{
    void printTitleScreen()
    {
        std::cout << R"(
     _____                                                  _____
  __|___  |__    __   _    _____     ______    _____     __|___  |__      __      _____    _____     ____    __
 |   ___|    |  |  |_| |  |     |   |   ___|  |     \   |   ___|    |   _|  |_   /     \  |     |   |    \  /  |
  `-.`-.     |  |   _  |  |     \   |   ___|  |      \   `-.`-.     |  |_    _|  |     |  |     \   |     \/   |
 |______|  __|  |__| |_|  |__|\__\  |______|  |______/  |______|  __|    |__|    \_____/  |__|\__\  |__/\__/|__|
    |_____|                                                |_____|
    )" << std::endl;

        std::cout << "\nPress [Enter] to continue..." << std::endl;
        std::cin.get();
    }

    void showCheatSheet()
    {
        std::ifstream file("../cheatsheet.txt");
        if (!file)
        {
            std::cerr << "Error: Could not open cheatsheet.txt" << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::cout << line << std::endl;
        }
    }

}
