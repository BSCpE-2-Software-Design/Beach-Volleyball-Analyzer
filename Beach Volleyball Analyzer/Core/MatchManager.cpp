#include "Core/MatchManager.h"
#include "UI/GameDisplay.h"
#include <iostream>
#include <cctype>

MatchManager::MatchManager() 
    : m_selectedPlayer(-1), m_waitingForAction(false),
      m_serveHandler(this), m_passHandler(this), m_setHandler(this),
      m_attackHandler(this), m_digHandler(this) {}

int MatchManager::getTeamFromPlayer(int playerId) const {
    return (playerId < 2) ? 0 : 1;
}

void MatchManager::run() {
    while (!m_score.isSetFinished()) {
        GameDisplay::clearScreen();

        auto scores = m_score.getScores();
        int currentServer = m_score.getCurrentServer();
        GameDisplay::drawScoreboard(scores.first, scores.second, m_score.getServingTeam(), currentServer);
        GameDisplay::drawPlayerGrid();
        GameDisplay::drawActionMenu();

        auto rally = m_recorder.getCurrentRally();
        GameDisplay::drawRallyLog(rally);

        if (!m_recorder.hasServed()) {
            std::cout << "\nSERVE REQUIRED! Player " << currentServer << " must serve\n";
        }

        std::cout << "\n> ";
        char input;
        std::cin >> input;

        // Player selection (0-3)
        if (input >= '0' && input <= '3') {
            int selected = input - '0';
            int expectedServer = m_score.getCurrentServer();

            if (!m_recorder.hasServed() && selected != expectedServer) {
                std::cout << "RALLY MUST START WITH SERVE! Player " << expectedServer << " must serve.\n";
                continue;
            }

            m_selectedPlayer = selected;
            m_waitingForAction = true;
            std::cout << "Selected Player " << m_selectedPlayer << ". Choose action.\n";
            continue;
        }

        // Action selection
        if (m_waitingForAction && m_selectedPlayer != -1) {
            int teamId = getTeamFromPlayer(m_selectedPlayer);
            char upper = std::toupper(input);
            std::string action;

            switch (upper) {
            case 'S': action = "serve"; break;
            case 'P': action = "pass"; break;
            case 'E': action = "set"; break;
            case 'A': action = "attack"; break;
            case 'B': action = "block"; break;
            case 'D': action = "dig"; break;
            default: action = "";
            }

            if (!action.empty()) {
                if (!m_recorder.hasServed() && action != "serve") {
                    GameDisplay::showMessage("RALLY MUST START WITH SERVE! Press S to serve.");
                    m_waitingForAction = false;
                    m_selectedPlayer = -1;
                    continue;
                }

                if (action == "serve" && m_recorder.hasServed()) {
                    GameDisplay::showMessage("CANNOT SERVE - Rally already in progress!");
                    m_waitingForAction = false;
                    m_selectedPlayer = -1;
                    continue;
                }

                bool success = m_recorder.addTouch(m_selectedPlayer, action, teamId);

                if (success) {
                    m_stats.recordTouch(m_selectedPlayer);

                    if (action == "serve") {
                        m_serveHandler.handle(m_selectedPlayer, teamId);
                    }
                    else if (action == "pass") {
                        m_passHandler.handle(m_selectedPlayer, teamId);
                    }
                    else if (action == "set") {
                        m_setHandler.handle(m_selectedPlayer, teamId);
                    }
                    else if (action == "attack") {
                        m_attackHandler.handle(m_selectedPlayer, teamId);
                    }
                    else if (action == "dig") {
                        m_digHandler.handle(m_selectedPlayer, teamId);
                    }
                }
                else {
                    std::string error = m_recorder.getLastError();
                    int otherTeam = (teamId == 0) ? 1 : 0;
                    int servingPlayer = m_recorder.getServingPlayer();
                    if (servingPlayer == -1) servingPlayer = m_score.getCurrentServer();

                    m_score.handleServeResult(servingPlayer, false);
                    m_stats.recordError(m_selectedPlayer);
                    GameDisplay::showMessage(error + " - Point to Team " + std::string(otherTeam == 0 ? "A" : "B") + ", serve switches");
                    m_recorder.clearRally();
                }

                m_waitingForAction = false;
                m_selectedPlayer = -1;
            }
            continue;
        }

        // Error handling
        char upper = std::toupper(input);
        if (upper == 'X') {
            if (m_selectedPlayer == -1) {
                int expectedServer = m_score.getCurrentServer();
                std::cout << "Select player " << expectedServer << " first\n";
                continue;
            }

            int teamId = getTeamFromPlayer(m_selectedPlayer);
            int otherTeam = (teamId == 0) ? 1 : 0;
            m_score.handleServeResult(m_recorder.getServingPlayer() != -1 ? m_recorder.getServingPlayer() : m_score.getCurrentServer(), false);
            m_stats.recordError(m_selectedPlayer);
            GameDisplay::showMessage("ERROR - Point to Team " + std::string(otherTeam == 0 ? "A" : "B") + ", serve switches");
            m_recorder.clearRally();
            m_waitingForAction = false;
            m_selectedPlayer = -1;
            continue;
        }

        // Stats
        if (upper == 'T') {
            std::cout << "\n[1] Basic Stats\n[2] Detailed Stats\nSelect: ";
            char statChoice;
            std::cin >> statChoice;
            if (statChoice == '2') {
                m_stats.printDetailedStats();
            } else {
                m_stats.printReport();
            }
            std::cout << "Press Enter...";
            std::cin.ignore();
            std::cin.get();
            continue;
        }

        // Quit
        if (upper == 'Q') {
            std::cout << "Goodbye!\n";
            break;
        }
    }

    // Game over
    auto scores = m_score.getScores();
    std::cout << "\n";
    std::cout << "##########################################################################\n";
    std::cout << "#                          GAME OVER!                                    #\n";
    int winningTeam = (scores.first > scores.second) ? 0 : 1;
    std::cout << "#                         Team " << (winningTeam == 0 ? "A" : "B") << " WINS!                                   #\n";
    std::cout << "##########################################################################\n";
    std::cout << "\nFinal Score: Team A " << scores.first << " - " << scores.second << " Team B\n";

    std::cout << "\n[1] Basic Stats\n[2] Detailed Stats\nSelect: ";
    char statChoice;
    std::cin >> statChoice;
    if (statChoice == '2') {
        m_stats.printDetailedStats();
    } else {
        m_stats.printReport();
    }
}