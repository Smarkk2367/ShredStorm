#include "../include/argsHandling.h"
#include "../include/tab.h"
#include "../include/ui.h"
#include <iostream>

namespace shredstorm
{
    void handleCommandLineArgs(int argc, char* argv[]) {
        if (argc < 2) return;

        std::string arg = argv[1];

        if (arg == "--cheatsheet" || arg == "-c") {
            showCheatSheet();
            exit(0);
        }
        if (arg == "--list" || arg == "-l") {
            listAllTabs();
            exit(0);
        }
        if (arg.rfind("--show=", 0) == 0) {
            std::string title = arg.substr(7);  //everything after '='
            if (title.empty()) {
                std::cerr << "Error: You must provide a title after --show=\n";
                exit(1);
            }

            shredstorm::Tab loadedTab;
            if (shredstorm::loadTabFromFile(title, loadedTab)) {
                std::cout << "Loaded tab:\n";
                shredstorm::displayTab(loadedTab);
            } else {
                std::cerr << "Error: Cannot find the tab \"" << title << "\".\n";
            }
            exit(0);
        }
        else {
            std::cout << "Unknown argument: " << arg << "\n";
            std::cout << "Available options:\n"
                         "  --cheatsheet | -c        : Show help\n"
                         "  --list       | -l        : List all tabs\n"
                         "  --show=TITLE             : Show specific tab by title\n";
            exit(1);
        }
    }

}