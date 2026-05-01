#include "GameDisplay.h"
#include <iostream>
#include <cstdlib>

void GameDisplay::drawScoreboard(int teamAScore, int teamBScore, int servingTeam) {
    std::cout << "\n=========================================\n";
    std::cout << "      BEACH VOLLEYBALL RALLY ANALYZER\n";
    std::cout << "=========================================\n";
    std::cout << "   Team A: " << teamAScore << "    Team B: " << teamBScore << "\n";
    std::cout << "   Serving: Team " << (servingTeam == 0 ? "A" : "B") << "\n";
    std::cout << "=========================================\n";
}

void GameDisplay::drawPlayerGrid() {
    std::cout << "\n--- PLAYERS ---\n";
    std::cout << "  [0] Team A - Player 1    [1] Team A - Player 2\n";
    std::cout << "  [2] Team B - Player 3    [3] Team B - Player 4\n";
}

void GameDisplay::drawActionMenu() {
    std::cout << "\n--- ACTIONS ---\n";
    std::cout << "  s = Serve    p = Pass    t = Set\n";
    std::cout << "  a = Attack   b = Block   d = Dig\n";
    std::cout << "  e = Error    c = Cancel\n";
}

void GameDisplay::drawRallyLog(const std::vector<Touch>& touches) {
    std::cout << "\n--- CURRENT RALLY ---\n";
    if (touches.empty()) {
        std::cout << "  (no touches yet)\n";
    }
    else {
        for (const auto& t : touches) {
            std::cout << "Player " << t.playerId << ": " << t.actionType << "\n";
        }
    }
}

void GameDisplay::showMessage(const std::string& message) {
    std::cout << "\n" << message << "\n";
}

void GameDisplay::showError(const std::string& message) {
    std::cout << "\nERROR: " << message << "\n";
}

void GameDisplay::showHelp() {
    std::cout << "\n--- HOW TO PLAY ---\n";
    std::cout << "1. Select a player (0-3)\n";
    std::cout << "2. Choose an action (s/p/t/a/b/d)\n";
    std::cout << "3. If error happens, press e and choose error type\n";
    std::cout << "4. Press 9 to quit\n";
}

void GameDisplay::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void GameDisplay::waitForEnter() {
    std::cout << "\nPress ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}