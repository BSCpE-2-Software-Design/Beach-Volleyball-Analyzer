#include "Core/AttackHandler.h"
#include "Core/MatchManager.h"
#include "UI/GameDisplay.h"
#include "UI/InputValidator.h"
#include <iostream>

AttackHandler::AttackHandler(MatchManager* match) : m_match(match) {}

void AttackHandler::handle(int playerId, int teamId) {
    bool attErr = InputValidator::getYesNo("Was the attack an error? (Y/N): ");

    int otherTeam = (teamId == 0) ? 1 : 0;
    int servingPlayer = m_match->getRecorder().getServingPlayer();
    if (servingPlayer == -1) servingPlayer = m_match->getScore().getCurrentServer();

    if (attErr) {
        m_match->getScore().addPoint(otherTeam);
        m_match->getScore().setServingTeam(otherTeam);
        m_match->getStats().recordAttack(playerId, true);
        m_match->getStats().recordError(playerId);
        GameDisplay::showMessage("ATTACK ERROR - Point to Team " + std::string(otherTeam == 0 ? "A" : "B") + ", serve switches");
        m_match->getRecorder().clearRally();
    }
    else {
        m_match->getStats().recordAttack(playerId, false);

        char res = InputValidator::getValidChar("Attack result? [B]lock  [D]ig  [I]n (point): ", "BDI");

        if (res == 'I') {
            int servingTeam = m_match->getTeamFromPlayer(servingPlayer);
            bool pointWon = (teamId == servingTeam);
            m_match->getScore().handleServeResult(servingPlayer, pointWon);
            m_match->getStats().recordPoint(playerId);
            GameDisplay::showMessage("POINT! Team " + std::string(teamId == 0 ? "A" : "B") + " scores! Serve " + (pointWon ? "continues" : "switches"));
            m_match->getRecorder().clearRally();
        }
        else if (res == 'D') {
            int minPlayer = (otherTeam == 0) ? 0 : 2;
            int maxPlayer = (otherTeam == 0) ? 1 : 3;
            int defPlayer = InputValidator::getValidInt("Select defending player (" + std::to_string(minPlayer) + " or " + std::to_string(maxPlayer) + "): ", minPlayer, maxPlayer);

            // Ask if dig was successful
            bool digSucc = InputValidator::getYesNo("Was the dig successful? (Y/N): ");

            if (!digSucc) {
                // Dig failed - point to attacking team
                m_match->getScore().addPoint(teamId);
                m_match->getScore().setServingTeam(teamId);
                m_match->getStats().recordError(defPlayer);
                GameDisplay::showMessage("DIG ERROR - Point to Team " + std::string(teamId == 0 ? "A" : "B") + ", serve switches");
                m_match->getRecorder().clearRally();
            }
            else {
                // Dig successful - record it
                bool success = m_match->getRecorder().addTouch(defPlayer, "dig", otherTeam);
                m_match->getStats().recordTouch(defPlayer);
                m_match->getStats().recordDig(defPlayer, false);

                // Ask what happens after the dig
                char digResult = InputValidator::getValidChar("Dig result? [P]ass continues  [I]n (point): ", "PI");

                if (digResult == 'P') {
                    GameDisplay::showMessage("DIG! Rally continues...");
                }
                else if (digResult == 'I') {
                    // Dig resulted in a point for defending team
                    int servingTeam = m_match->getTeamFromPlayer(servingPlayer);
                    bool pointWon = (otherTeam == servingTeam);
                    m_match->getScore().handleServeResult(servingPlayer, pointWon);
                    m_match->getStats().recordPoint(defPlayer);
                    GameDisplay::showMessage("DIG POINT! Team " + std::string(otherTeam == 0 ? "A" : "B") + " scores! Serve " + (pointWon ? "continues" : "switches"));
                    m_match->getRecorder().clearRally();
                }
            }
        }
        else if (res == 'B') {
            int minPlayer = (otherTeam == 0) ? 0 : 2;
            int maxPlayer = (otherTeam == 0) ? 1 : 3;
            int blkPlayer = InputValidator::getValidInt("Select blocking player (" + std::to_string(minPlayer) + " or " + std::to_string(maxPlayer) + "): ", minPlayer, maxPlayer);

            bool blkSucc = InputValidator::getYesNo("Was the block successful? (Y/N): ");

            if (blkSucc) {
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
                GameDisplay::showMessage("BLOCKED BUT FAILED! Rally continues...");
            }
        }
    }
}