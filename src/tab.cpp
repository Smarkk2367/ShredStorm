#include "../include/tab.h"
#include "../include/consts.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace shredstorm
{
    void createTab(const std::string& encodedInput, Tab& tabOut)
    {

        TabLines strings = {
            "e|", "B|", "G|", "D|", "A|", "E|"
        };

        char lastString = '\0';

        size_t i = 0;
        while (i<encodedInput.length())
        {
            char current = encodedInput[i];

            if (current == 'E' || current == 'B' || current == 'G' || current == 'D' ||
                current == 'A' || current == 'e')
            {
                std::string fret = "";
                ++i;

                while (i<encodedInput.length() && std::isdigit(encodedInput[i]))
                {
                    fret += encodedInput[i];
                    i++;
                }

                if (i < encodedInput.length() && (
                    encodedInput[i] == 'h' || encodedInput[i] == 'p' ||
                    encodedInput[i] == '/' || encodedInput[i] == '\\' || encodedInput[i] == 'b'))
                {
                    char tech = encodedInput[i];
                    ++i;

                    std::string secondFret = "";
                    //if the technique has a second fret
                    while (i < encodedInput.length() && std::isdigit(encodedInput[i]))
                    {
                        secondFret += encodedInput[i];
                        ++i;
                    }

                    fret += tech;
                    fret += secondFret;
                }

                if (fret.empty()) continue;

                int pad = fret.length();

                for (auto& line : strings)
                {
                    if (line[0] == current)
                    {
                        if (current == lastString)
                        {
                            if (!line.empty() && std::isdigit(line.back()))
                            {
                                line += "-";
                                ++pad;
                            }
                        }
                        line += fret;

                    } else
                    {
                        line += std::string(pad, '-');
                    }
                }
                lastString = current;

            } else if (current == '-', current == ' ')
            {
                ++i;
            } else
            {
                ++i; //na wypadek innego znaku specjalnego
            }
        }
        tabOut.content = strings;
    }

    void displayTab(const Tab& tabIn)
    {
        std::cout << "Title: " << tabIn.title << std::endl;
        std::cout << "Author: " << tabIn.author << std::endl;
        std::cout << std::endl;

        for (const auto& line : tabIn.content) {
            std::cout << line << std::endl;
        }
    }

    void saveTabToFile(const Tab& tab)
    {
        std::filesystem::create_directory(TAB_DIRECTORY);
        std::ofstream file(TAB_DIRECTORY + tab.title + TAB_EXTENSION);
        if (!file)
        {
            std::cerr << "Error: An error has appeared upon opening the file" << std::endl;
            return;
        }

        file << "Title: " << tab.title << std::endl;
        file << "Author: " << tab.author << std::endl;
        for (const auto& line : tab.content)
        {
            file << line << std::endl;
        }
    }

    bool loadTabFromFile(const std::string& title, Tab& tabOut)
    {
        std::ifstream file(TAB_DIRECTORY + title + TAB_EXTENSION);
        if (!file)
        {
            std::cerr << "Error: Could not find the file you're looking for" << std::endl;
            return false;
        }

        std::getline(file, tabOut.title);
        std::getline(file, tabOut.author);

        tabOut.content.clear();
        std::string line;
        while (std::getline(file, line))
        {
            tabOut.content.push_back(line);
        }
        return true;

    }

    void listAllTabs()
    {
        std::cout << "All tabs: " << std::endl;
        for (const auto& entry : std::filesystem::directory_iterator(TAB_DIRECTORY))
        {
            if (entry.path().extension() == TAB_EXTENSION)
            {
                std::cout << entry.path().stem().string() << std::endl;
            }
        }
    }

}