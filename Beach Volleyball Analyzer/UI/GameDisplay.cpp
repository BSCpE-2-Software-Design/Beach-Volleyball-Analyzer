#include "GameDisplay.h"
#include <iostream>

void GameDisplay::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void GameDisplay::drawScoreboard(int scoreA, int scoreB, int servingTeam, int currentServer) {
    std::cout << "\n=========================================\n";
    std::cout << "     BEACH VOLLEYBALL RALLY ANALYZER\n";
    std::cout << "=========================================\n";
    std::cout << "   Team A: " << scoreA << "      Team B: " << scoreB << "\n";
    std::cout << "   Serving: Team " << (servingTeam == 0 ? "A" : "B");
    std::cout << " (Player " << currentServer << ")\n";
    std::cout << "=========================================\n";
}

void GameDisplay::drawPlayerGrid() {
    std::cout << "\n PLAYERS:\n";
    std::cout << " [0] Team A - Player 1     [1] Team A - Player 2\n";
    std::cout << " [2] Team B - Player 3     [3] Team B - Player 4\n";
}

void GameDisplay::drawActionMenu() {
    std::cout << "\n ACTIONS:\n";
    std::cout << " [S]erve  [P]ass  [E]set  [A]ttack  [B]lock  [D]ig\n";
    std::cout << " [T] Stats  [Q]uit\n";
}

void GameDisplay::drawRallyLog(const std::vector<Touch>& touches) {
    if (touches.empty()) return;
    std::cout << "\n CURRENT RALLY:\n";
    for (size_t i = 0; i < touches.size(); i++) {
        std::string team = (touches[i].teamId == 0) ? "A" : "B";
        std::cout << "  " << (i + 1) << ". Player " << touches[i].playerId
            << " (Team " << team << "): " << touches[i].action << "\n";
    }
}

void GameDisplay::showMessage(const std::string& msg) {
    std::cout << "\n>>> " << msg << " <<<\n";
    std::cout << "Press Enter...";
    std::cin.get();
    std::cin.get();
}