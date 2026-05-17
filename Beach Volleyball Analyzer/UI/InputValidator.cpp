#include "UI/InputValidator.h"
#include <cctype>
#include <algorithm>

char InputValidator::getValidChar(const std::string& prompt, const std::string& validChars) {
    char input;
    bool isValid = false;

    while (!isValid) {
        std::cout << prompt;
        std::cin >> input;
        std::cin.ignore(10000, '\n');  // Clear input buffer
        
        input = std::toupper(input);

        // Check if input is in valid characters
        if (validChars.find(input) != std::string::npos) {
            isValid = true;
        }
        else {
            std::cout << "Invalid input! Please enter one of: " << validChars << "\n";
        }
    }

    return input;
}

int InputValidator::getValidInt(const std::string& prompt, int minValue, int maxValue) {
    int input;
    bool isValid = false;

    while (!isValid) {
        std::cout << prompt;
        
        if (std::cin >> input) {
            std::cin.ignore(10000, '\n');  // Clear input buffer
            
            if (input >= minValue && input <= maxValue) {
                isValid = true;
            }
            else {
                std::cout << "Invalid input! Please enter a value between " << minValue 
                         << " and " << maxValue << "\n";
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number.\n";
        }
    }

    return input;
}

bool InputValidator::getYesNo(const std::string& prompt) {
    char input = getValidChar(prompt, "YN");
    return input == 'Y';
}