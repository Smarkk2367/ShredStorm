#include <iostream>
#include <algorithm>
#include "include/ui.h"
#include "include/tab.h"

bool isValidFileName(const std::string& name)
{
    const std::string forbiddenChars = R"(\/:*?"<>|)";
    return !name.empty() && std::none_of(name.begin(), name.end(), [&](char c) {
        return forbiddenChars.find(c) != std::string::npos;
    });
}


int main(int argc, char* argv[])
{
    shredstorm::printTitleScreen();

    while (true)
    {
        std::cout << "Welcome to ShredStorm" << std::endl;
        std::cout << "1: create a tab" << std::endl;
        std::cout << "2: search tab" << std::endl;
        std::cout << "3: see all tabs" << std::endl;
        std::cout << "4: see the Cheat Sheet" << std::endl;
        std::cout << "5: exit app" << std::endl;
        std::cout << "Choose and option: " << std::endl;

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // \n causes some trouble



        if (choice == 1)
        {
            shredstorm::Tab newTab;
            std::string encodedInput;

            do
            {
                std::cout << "Input Title: ";
                std::getline(std::cin, newTab.title);

                if (newTab.title.empty())
                {
                    std::cout << "Title cannot be empty, please try again.\n";
                }
                else if (!isValidFileName(newTab.title))
                {
                    std::cout << "Title contains invalid characters. Avoid: \\ / : * ? \" < > |\n";
                    newTab.title.clear();
                }

            } while (newTab.title.empty());

            std::cout << "Input Author: " << std::endl;
            std::getline(std::cin, newTab.author);

            std::cout << "Enter your tab in form of a single string (e.g. E1-A3-e5): " << std::endl;
            std::getline(std::cin, encodedInput);

            shredstorm::createTab(encodedInput, newTab);
            shredstorm::saveTabToFile(newTab);
        } else if (choice == 2)
        {
            std::string title;
            std::cout << "Enter title: " << std::endl;
            std::getline(std::cin, title);

            shredstorm::Tab loadedTab;
            if (shredstorm::loadTabFromFile(title, loadedTab))
            {
                std::cout << "Loaded tab: " << std::endl;
                shredstorm::displayTab(loadedTab);
            } else
            {
                std::cout << "Error: Cannot find the tab/The tab does not exist" << std::endl;
            }
        } else if (choice == 3)
        {
            shredstorm::listAllTabs();
        } else if (choice == 4)
        {
            shredstorm::showCheatSheet();
        }
        else if (choice == 5)
        {
            std::cout << "Exiting..." << std::endl;
            break;
        } else
        {
            std::cout << "Error: Invalid choice, exiting... " << std::endl;
            break;
        }
    }
    return 0;
}