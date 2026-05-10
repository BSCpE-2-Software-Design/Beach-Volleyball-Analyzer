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

                    // Special handling for serve: allow marking error
                    if (action == "serve") {
                        std::cout << "Was the serve an error? (Y/N): ";
                        char servErr;
                        std::cin >> servErr;
                        servErr = std::toupper(servErr);

                        if (servErr == 'Y') {
                            // Serve error: point to other team and switch serve
                            int otherTeam = (teamId == 0) ? 1 : 0;
                            m_score.handleServeResult(m_selectedPlayer, false);
                            m_stats.recordError(m_selectedPlayer);
                            GameDisplay::showMessage("SERVE ERROR - Point to Team " + std::string(otherTeam == 0 ? "A" : "B") + ", serve switches");
                            m_recorder.clearRally();
                        }
                    }
                    // Special handling for attack: allow marking error or result (block/dig/in)
                    else if (action == "attack") {
                        std::cout << "Was the attack an error? (Y/N): ";
                        char attErr;
                        std::cin >> attErr;
                        attErr = std::toupper(attErr);

                        if (attErr == 'Y') {
                            // Attack error: award point to other team and switch serve
                            int otherTeam = (teamId == 0) ? 1 : 0;
                            int servingPlayer = m_recorder.getServingPlayer();
                            if (servingPlayer == -1) servingPlayer = m_score.getCurrentServer();
                            m_score.handleServeResult(servingPlayer, false);
                            m_stats.recordError(m_selectedPlayer);
                            GameDisplay::showMessage("ATTACK ERROR - Point to Team " + std::string(otherTeam == 0 ? "A" : "B") + ", serve switches");
                            m_recorder.clearRally();
                        }
                        else {
                            // Attack was good - ask what happened on the other side
                            std::cout << "Attack result? [B]lock  [D]ig  [I]n (point): ";
                            char res;
                            std::cin >> res;
                            res = std::toupper(res);

                            int otherTeam = (teamId == 0) ? 1 : 0;

                            if (res == 'I') {
                                // Attack landed: point to attacking team
                                int scoringTeam = teamId;
                                int servingPlayer = m_recorder.getServingPlayer();
                                if (servingPlayer == -1) servingPlayer = m_score.getCurrentServer();
                                int servingTeam = getTeamFromPlayer(servingPlayer);
                                bool pointWon = (scoringTeam == servingTeam);
                                m_score.handleServeResult(servingPlayer, pointWon);
                                m_stats.recordPoint(m_selectedPlayer);
                                GameDisplay::showMessage("POINT! Team " + std::string(teamId == 0 ? "A" : "B") + " scores! Serve " + (pointWon ? "continues" : "switches"));
                                m_recorder.clearRally();
                            }
                            else if (res == 'D') {
                                // Other team digs: ask which defending player performed the dig
                                std::cout << "Select defending player (" << (otherTeam == 0 ? "0 or 1" : "2 or 3") << "): ";
                                int defPlayer;
                                std::cin >> defPlayer;
                                if (getTeamFromPlayer(defPlayer) != otherTeam) {
                                    // default to first player of the defending team
                                    defPlayer = otherTeam * 2;
                                }

                                bool added = m_recorder.addTouch(defPlayer, "dig", otherTeam);
                                if (added) {
                                    m_stats.recordTouch(defPlayer);
                                }
                                else {
                                    GameDisplay::showMessage(std::string("Could not record dig: ") + m_recorder.getLastError());
                                    m_recorder.clearRally();
                                }
                            }
                            else if (res == 'B') {
                                // Other team blocks: ask which player and whether block was successful
                                std::cout << "Select blocking player (" << (otherTeam == 0 ? "0 or 1" : "2 or 3") << "): ";
                                int blkPlayer;
                                std::cin >> blkPlayer;
                                if (getTeamFromPlayer(blkPlayer) != otherTeam) {
                                    blkPlayer = otherTeam * 2;
                                }

                                // Record the block touch
                                bool added = m_recorder.addTouch(blkPlayer, "block", otherTeam);
                                if (added) {
                                    m_stats.recordTouch(blkPlayer);
                                }
                                else {
                                    GameDisplay::showMessage(std::string("Could not record block: ") + m_recorder.getLastError());
                                    m_recorder.clearRally();
                                }

                                std::cout << "Was the block successful (point to blocking team)? (Y/N): ";
                                char blkSucc;
                                std::cin >> blkSucc;
                                blkSucc = std::toupper(blkSucc);

                                if (blkSucc == 'Y') {
                                    int scoringTeam = otherTeam;
                                    int servingPlayer = m_recorder.getServingPlayer();
                                    if (servingPlayer == -1) servingPlayer = m_score.getCurrentServer();
                                    int servingTeam = getTeamFromPlayer(servingPlayer);
                                    bool pointWon = (scoringTeam == servingTeam);
                                    m_score.handleServeResult(servingPlayer, pointWon);
                                    m_stats.recordPoint(blkPlayer);
                                    GameDisplay::showMessage("POINT! Team " + std::string(otherTeam == 0 ? "A" : "B") + " scores! Serve " + (pointWon ? "continues" : "switches"));
                                    m_recorder.clearRally();
                                }
                                // if block not successful, rally continues after recording the block touch
                            }
                        }
                    }
                    else {
                        // Non-attack, non-serve actions: no special immediate processing here
                    }
                }
                else {
                    // Violation occurred
                    std::string error = m_recorder.getLastError();
                    int servingPlayer = m_recorder.getServingPlayer();
                    if (servingPlayer == -1) servingPlayer = m_score.getCurrentServer();
                    int otherTeam = (teamId == 0) ? 1 : 0;

                    // Award point to other team and switch serve
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
                int otherTeam = (getTeamFromPlayer(m_selectedPlayer) == 0) ? 1 : 0;
                m_score.handleServeResult(m_selectedPlayer, false);
                GameDisplay::showMessage("SERVE ERROR - Point to Team " + std::string(otherTeam == 0 ? "A" : "B") + ", serve switches");
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
                GameDisplay::showMessage("ERROR - Point to Team " + std::string(otherTeam == 0 ? "A" : "B") + ", serve switches");
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
    std::cout << "\nGAME OVER!\n";
    std::cout << "Final: Team A " << scores.first << " - " << scores.second << " Team B\n";
    m_stats.printReport();
}