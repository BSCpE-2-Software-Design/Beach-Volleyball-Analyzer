#include "MatchManager.h"
#include "GameDisplay.h"
#include "Rules.h"
#include <iostream>
#include <limits>

MatchManager::MatchManager() : m_running(true), m_selectedPlayer(-1) {}

void MatchManager::run() {
    GameDisplay::clearScreen();

    while (m_running) {
        displayAll();

        auto scores = m_score.getScores();
        if (m_score.isSetFinished()) {
            GameDisplay::showMessage("\nGAME OVER! Team " +
                std::to_string(m_score.getWinner()) + " wins!");
            m_stats.printReport();
            break;
        }

        processInput();
    }
}

void MatchManager::displayAll() {
    GameDisplay::clearScreen();

    auto scores = m_score.getScores();
    GameDisplay::drawScoreboard(scores.first, scores.second, m_score.getServingTeam());
    GameDisplay::drawRallyLog(m_recorder.getCurrentRally());
    GameDisplay::drawPlayerGrid();
    GameDisplay::drawActionMenu();
    GameDisplay::showHelp();
}

void MatchManager::processInput() {
    // If rally ended, reset
    if (m_recorder.isRallyEnded()) {
        GameDisplay::showMessage("\nRally ended! Starting new rally...");
        GameDisplay::waitForEnter();
        m_recorder.clearRally();
        m_selectedPlayer = -1;
        return;
    }

    // Select player if not selected
    if (m_selectedPlayer == -1) {
        std::cout << "\nSelect player (0-3, or 9 to quit): ";
        int input;
        std::cin >> input;

        if (input == 9) {
            m_running = false;
            return;
        }

        if (input >= 1 && input <= 4) {
            m_selectedPlayer = input;
            std::cout << "Player " << m_selectedPlayer << " selected.\n";
        }
        else {
            GameDisplay::showError("Invalid player! Choose 1-4.");
        }
        return;
    }

    // Get action for selected player
    std::cout << "\nPlayer " << m_selectedPlayer << " selected.\n";
    std::cout << "Action (s=serve, p=pass, t=set, a=attack, b=block, d=dig, e=error, c=cancel): ";

    char choice;
    std::cin >> choice;

    int teamId = (m_selectedPlayer < 2) ? 0 : 1;

    switch (choice) {
    case 's':
    case 'p':
    case 't':
    case 'a':
    case 'b':
    case 'd':
    {
        std::string action;
        switch (choice) {
        case 's': action = "serve"; break;
        case 'p': action = "pass"; break;
        case 't': action = "set"; break;
        case 'a': action = "attack"; break;
        case 'b': action = "block"; break;
        case 'd': action = "dig"; break;
        }

        bool success = m_recorder.addTouch(m_selectedPlayer, action, teamId);

        if (success) {
            m_stats.recordTouch(m_selectedPlayer, action);
            GameDisplay::showMessage("✓ Recorded: Player " +
                std::to_string(m_selectedPlayer) + " - " + action);
            m_selectedPlayer = -1;

            // Check if attack scores (simplified)
            if (action == "attack") {
                m_recorder.endRallyWithPoint(m_selectedPlayer, teamId);
                m_score.addPoint(teamId);
                m_stats.recordPoint(m_selectedPlayer);
                GameDisplay::showMessage("POINT! Team " +
                    std::string(teamId == 0 ? "A" : "B") + " scores!");
                m_selectedPlayer = -1;
            }
        }
        else {
            GameDisplay::showError(m_recorder.getLastError());
            int winner = (teamId == 0) ? 1 : 0;
            m_score.addPoint(winner);
            m_stats.recordError(m_selectedPlayer, m_recorder.getLastError());
            m_selectedPlayer = -1;
        }
        break;
    }

    case 'e':  // Error
    {
        std::cout << "Error type:\n";
        std::cout << "  1 = 4-touch violation\n";
        std::cout << "  2 = Double touch\n";
        std::cout << "  3 = Ball out\n";
        std::cout << "  4 = Net touch\n";
        std::cout << "Choose (1-4): ";

        int errorType;
        std::cin >> errorType;

        std::string error;
        switch (errorType) {
        case 1: error = "four_touch"; break;
        case 2: error = "double_touch"; break;
        case 3: error = "ball_out"; break;
        case 4: error = "net_touch"; break;
        default: error = "unknown";
        }

        int winner = Rules::getPointWinnerOnError(teamId);
        m_score.addPoint(winner);
        m_stats.recordError(m_selectedPlayer, error);
        m_recorder.endRallyWithError(error, m_selectedPlayer, teamId);
        GameDisplay::showError(error + " - Point to Team " +
            std::string(winner == 0 ? "A" : "B"));
        m_selectedPlayer = -1;
        break;
    }

    case 'c':  // Cancel
        m_selectedPlayer = -1;
        GameDisplay::showMessage("Selection cancelled.");
        break;

    default:
        GameDisplay::showError("Invalid choice!");
        break;
    }

    GameDisplay::waitForEnter();
}

bool MatchManager::isGameRunning() const {
    return m_running;
}