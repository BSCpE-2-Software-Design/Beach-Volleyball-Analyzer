#include "MatchManager.h"
#include "GameDisplay.h"
#include <iostream>
#include <cctype>

MatchManager::MatchManager() : m_selectedPlayer(-1), m_waitingForAction(false) {}

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

        // Show serve requirement
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

            // If serve hasn't happened yet, only the correct server can be selected
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
                // Prevent non-serve actions if serve hasn't happened yet
                if (!m_recorder.hasServed() && action != "serve") {
                    GameDisplay::showMessage("RALLY MUST START WITH SERVE! Press S to serve.");
                    m_waitingForAction = false;
                    m_selectedPlayer = -1;
                    continue;
                }

                // Prevent serve after rally has started
                if (action == "serve" && m_recorder.hasServed()) {
                    GameDisplay::showMessage("CANNOT SERVE - Rally already in progress!");
                    m_waitingForAction = false;
                    m_selectedPlayer = -1;
                    continue;
                }

                bool success = m_recorder.addTouch(m_selectedPlayer, action, teamId);

                if (success) {
                    m_stats.recordTouch(m_selectedPlayer);

                    // Check if attack on 3rd consecutive touch by same team
                    if (action == "attack" && m_recorder.getConsecutiveTouches() == 3) {
                        // Won the rally!
                        int scoringTeam = teamId;
                        // Determine who served this rally (fallback to current server)
                        int servingPlayer = m_recorder.getServingPlayer();
                        if (servingPlayer == -1) servingPlayer = m_score.getCurrentServer();
                        int servingTeam = getTeamFromPlayer(servingPlayer);
                        bool pointWon = (scoringTeam == servingTeam);

                        // Let ScoreKeeper handle adding the point and rotating serve
                        m_score.handleServeResult(servingPlayer, pointWon);
                        m_stats.recordPoint(m_selectedPlayer);
                        GameDisplay::showMessage("POINT! Team " + std::string(teamId == 0 ? "A" : "B") + " scores!");
                        m_recorder.clearRally();
                    }
                }
                else {
                    // Violation occurred
                    std::string error = m_recorder.getLastError();

                    // Check if it was a serve error
                    if (action == "serve") {
                        // Serve error: point to other team. Use handleServeResult so
                        // ScoreKeeper can rotate servers properly based on who served.
                        m_score.handleServeResult(m_selectedPlayer, false);
                        GameDisplay::showMessage("SERVE ERROR - Point to other team, serve switches");
                    }
                    else {
                        // Non-serve violation: award point to other team and switch serve
                        int servingPlayer = m_recorder.getServingPlayer();
                        if (servingPlayer == -1) servingPlayer = m_score.getCurrentServer();
                        m_score.handleServeResult(servingPlayer, false);
                        m_stats.recordError(m_selectedPlayer);
                        int otherTeam = (teamId == 0) ? 1 : 0;
                        GameDisplay::showMessage(error + " - Point to Team " + std::string(otherTeam == 0 ? "A" : "B"));
                    }
                    m_recorder.clearRally();
                }

                m_waitingForAction = false;
                m_selectedPlayer = -1;
            }
            continue;
        }

        // Error handling (X key)
        char upper = std::toupper(input);
        if (upper == 'X') {
            if (m_selectedPlayer == -1) {
                int expectedServer = m_score.getCurrentServer();
                std::cout << "Select player " << expectedServer << " first\n";
                continue;
            }

            // If serve hasn't happened yet, it's a serve error
            if (!m_recorder.hasServed()) {
                m_score.handleServeResult(m_selectedPlayer, false);
                GameDisplay::showMessage("SERVE ERROR - Point to other team, serve switches");
                m_recorder.clearRally();
                m_waitingForAction = false;
                m_selectedPlayer = -1;
            }
            else {
                // General error after serve: award point to other team and switch serve
                int teamId = getTeamFromPlayer(m_selectedPlayer);
                int otherTeam = (teamId == 0) ? 1 : 0;
                // Use the recorded serving player for this rally
                m_score.handleServeResult(m_recorder.getServingPlayer(), false);
                m_stats.recordError(m_selectedPlayer);
                GameDisplay::showMessage("ERROR - Point to Team " + std::string(otherTeam == 0 ? "A" : "B"));
                m_recorder.clearRally();
                m_waitingForAction = false;
                m_selectedPlayer = -1;
            }
            continue;
        }

        // Stats
        if (upper == 'T') {
            m_stats.printReport();
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
    std::cout << "\nGAME OVER!w\n";
    std::cout << "Final: Team A " << scores.first << " - " << scores.second << " Team B\n";
    m_stats.printReport();
}