#pragma once
#include <string>
#include <iostream>

class InputValidator {
public:
    /// Gets a single character input that must be one of the valid options
    /// @param prompt The message to display to the user
    /// @param validChars A string containing all valid characters (e.g., "YN" for Yes/No)
    /// @return The valid character entered by the user
    static char getValidChar(const std::string& prompt, const std::string& validChars);

    /// Gets an integer input within a valid range
    /// @param prompt The message to display to the user
    /// @param minValue The minimum valid value (inclusive)
    /// @param maxValue The maximum valid value (inclusive)
    /// @return The valid integer entered by the user
    static int getValidInt(const std::string& prompt, int minValue, int maxValue);

    /// Gets a yes/no response
    /// @param prompt The message to display to the user
    /// @return True for 'Y', False for 'N'
    static bool getYesNo(const std::string& prompt);
};