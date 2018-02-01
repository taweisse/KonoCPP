
#include "Helpers.h"

namespace helpers {
    // Helper funtion to display a menu to the user and allow them to make a choice.
    int ShowMenu(std::string title, std::vector<std::string> items)
    {
        std::cout << title << '\n';
        for (int i = 0; i < (int)items.size(); i++) {
            std::cout << i + 1 << ". " << items[i] << '\n';
        }
        while (1) {
            int choice;
            ReadDigit(choice);
            if (choice > 0 && choice <= (int)items.size()) {
                return choice;
            }
            std::cout << "Invalid. Re-enter selection.\n";
        }
    }

    // Helper function to read a single digit from the console.
    // Returns true if successful.
    bool ReadDigit(int& digit)
    {
        std::string input;
        getline(std::cin, input);

        // Make sure the user only entered a single character.
        if (input.length() > 1) {
            return false;
        }

        // Make sure the user entered a digit. If they did, convert it.
        char num = input[0];
        if (!isdigit(num)) {
            return false;
        }
        digit = atoi(&num);
        return true;
    }

    // Helper function to read a compass direction from the console.
    // Returns true if successful.
    bool ReadDirection(Move::Direction& dir)
    {
        std::string input;
        std::getline(std::cin, input);

        // Make sure the user only entered 2 characters.
        if (input.length() != 2) {
            return false;
        }

        // Make sure the user entered alpha characters, and convert to uppercase if they did.
        for (int i = 0; i < 2; i++) {
            if (!isalpha(input[i])) {
                return false;
            }
            input[i] = toupper(input[i]);
        }

        // Make sure the input is a valid direction.
        if (input[0] == 'N' && input[1] == 'W'){
            dir = Move::Direction::NW;
            return true;
        }
        else if (input[0] == 'N' && input[1] == 'E') {
            dir = Move::Direction::NE;
            return true;
        }
        else if (input[0] == 'S' && input[1] == 'E') {
            dir = Move::Direction::SE;
            return true;
        }
        else if (input[0] == 'S' && input[1] == 'W') {
            dir = Move::Direction::SW;
            return true;
        }
        return false;
    }
}
