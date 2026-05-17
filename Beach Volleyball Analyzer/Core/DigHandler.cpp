#include "Core/DigHandler.h"
#include "Core/MatchManager.h"
#include "UI/GameDisplay.h"
#include "UI/InputValidator.h"
#include <iostream>

DigHandler::DigHandler(MatchManager* match) : m_match(match) {}

void DigHandler::handle(int playerId, int teamId) {
    bool digSucc = InputValidator::getYesNo("Was the dig successful? (Y/N): ");

    int otherTeam = (teamId == 0) ? 1 : 0;

    if (!digSucc) {
        m_match->getScore().addPoint(otherTeam);
        m_match->getScore().setServingTeam(otherTeam);
        m_match->getStats().recordError(playerId);
        GameDisplay::showMessage("DIG ERROR - Point to Team " + std::string(otherTeam == 0 ? "A" : "B") + ", serve switches");
        m_match->getRecorder().clearRally();
    }
    else {
        // Dig was successful - record it
        m_match->getStats().recordDig(playerId, false);
        m_match->getStats().recordTouch(playerId);

        // Ask what happens after the dig
        char digResult = InputValidator::getValidChar("Dig result? [P]ass continues  [I]n (point): ", "PI");

        if (digResult == 'P') {
            GameDisplay::showMessage("DIG! Rally continues...");
        }
        else if (digResult == 'I') {
            // Dig directly resulted in a point
            int servingTeam = m_match->getTeamFromPlayer(m_match->getRecorder().getServingPlayer() != -1
                ? m_match->getRecorder().getServingPlayer()
                : m_match->getScore().getCurrentServer());
            bool pointWon = (teamId == servingTeam);
            m_match->getScore().handleServeResult(m_match->getRecorder().getServingPlayer() != -1
                ? m_match->getRecorder().getServingPlayer()
                : m_match->getScore().getCurrentServer(), pointWon);
            m_match->getStats().recordPoint(playerId);
            GameDisplay::showMessage("DIG POINT! Team " + std::string(teamId == 0 ? "A" : "B") + " scores! Serve " + (pointWon ? "continues" : "switches"));
            m_match->getRecorder().clearRally();
        }
    }
}