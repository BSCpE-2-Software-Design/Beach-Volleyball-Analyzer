// Beach Volleyball Analyzer\AttackHandler.cpp
#include "Core/AttackHandler.h"
#include "Core/MatchManager.h"
#include "UI/GameDisplay.h"
#include <iostream>

AttackHandler::AttackHandler(MatchManager* match) : m_match(match) {}

void AttackHandler::handle(int playerId, int teamId) {
    std::cout << "Was the attack an error? (Y/N): ";
    char attErr;
    std::cin >> attErr;
    attErr = std::toupper(attErr);

    int otherTeam = (teamId == 0) ? 1 : 0;
    int servingPlayer = m_match->getRecorder().getServingPlayer();
    if (servingPlayer == -1) servingPlayer = m_match->getScore().getCurrentServer();

    if (attErr == 'Y') {
        // Force point to other team
        int otherTeam = (teamId == 0) ? 1 : 0;
        m_match->getScore().addPoint(otherTeam);
        m_match->getScore().setServingTeam(otherTeam);
        m_match->getStats().recordAttack(playerId, true);
        m_match->getStats().recordError(playerId);
        GameDisplay::showMessage("ATTACK ERROR - Point to Team " + std::string(otherTeam == 0 ? "A" : "B") + ", serve switches");
        m_match->getRecorder().clearRally();
    }
    else {
        m_match->getStats().recordAttack(playerId, false);

        std::cout << "Attack result? [B]lock  [D]ig  [I]n (point): ";
        char res;
        std::cin >> res;
        res = std::toupper(res);

        if (res == 'I') {
            int servingTeam = m_match->getTeamFromPlayer(servingPlayer);
            bool pointWon = (teamId == servingTeam);
            m_match->getScore().handleServeResult(servingPlayer, pointWon);
            m_match->getStats().recordPoint(playerId);
            GameDisplay::showMessage("POINT! Team " + std::string(teamId == 0 ? "A" : "B") + " scores! Serve " + (pointWon ? "continues" : "switches"));
            m_match->getRecorder().clearRally();
        }
        else if (res == 'D') {
            std::cout << "Select defending player (" << (otherTeam == 0 ? "0 or 1" : "2 or 3") << "): ";
            int defPlayer;
            std::cin >> defPlayer;
            if (m_match->getTeamFromPlayer(defPlayer) != otherTeam) {
                defPlayer = otherTeam * 2;
            }

            m_match->getStats().recordTouch(defPlayer);
            m_match->getStats().recordDig(defPlayer, false);
        }
        else if (res == 'B') {
            std::cout << "Select blocking player (" << (otherTeam == 0 ? "0 or 1" : "2 or 3") << "): ";
            int blkPlayer;
            std::cin >> blkPlayer;
            if (m_match->getTeamFromPlayer(blkPlayer) != otherTeam) {
                blkPlayer = otherTeam * 2;
            }

            std::cout << "Was the block successful? (Y/N): ";
            char blkSucc;
            std::cin >> blkSucc;
            blkSucc = std::toupper(blkSucc);

            if (blkSucc == 'Y') {
                int servingTeam = m_match->getTeamFromPlayer(servingPlayer);
                bool pointWon = (otherTeam == servingTeam);
                m_match->getScore().handleServeResult(servingPlayer, pointWon);
                m_match->getStats().recordBlockPoint(blkPlayer);
                m_match->getStats().recordPoint(blkPlayer);
                GameDisplay::showMessage("POINT! Team " + std::string(otherTeam == 0 ? "A" : "B") + " scores! Serve " + (pointWon ? "continues" : "switches"));
                m_match->getRecorder().clearRally();
            }
            else {
                m_match->getStats().recordUnsuccessfulBlock(blkPlayer);
            }
        }
    }
}