#ifndef TAB_H
#define TAB_H

#include <string>
#include <vector>
namespace shredstorm
{

    struct Tab
    {
        std::string title;
        std::string author;
        std::vector<std::string> content;
    };

    void createTab(const std::string& encodedInput, Tab& tabOut);

    void displayTab(const Tab& tab);

    void saveTabToFile(const Tab& tab);

    bool loadTabFromFile(const std::string& title, Tab& tabOut);

    void listAllTabs();

}

#endif
