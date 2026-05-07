#pragma once

#include <vector>
#include <string>
#include "Touch.h"

class GameDisplay {
public:
    static void clearScreen();
    static void drawScoreboard(int scoreA, int scoreB, int servingTeam, int currentServer);
    static void drawPlayerGrid();
    static void drawActionMenu();
    static void drawRallyLog(const std::vector<Touch>& touches);
    static void showMessage(const std::string& msg);
};