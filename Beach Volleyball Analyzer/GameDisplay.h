#pragma once

#include <vector>
#include <string>
#include "RallyRecorder.h"

class GameDisplay {
public:
    static void drawScoreboard(int teamAScore, int teamBScore, int servingTeam);
    static void drawPlayerGrid();
    static void drawActionMenu();
    static void drawRallyLog(const std::vector<Touch>& touches);
    static void showMessage(const std::string& message);
    static void showError(const std::string& message);
    static void showHelp();
    static void clearScreen();
    static void waitForEnter();
};

