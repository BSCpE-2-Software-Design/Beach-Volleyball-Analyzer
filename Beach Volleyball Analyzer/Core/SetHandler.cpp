#include "Core/SetHandler.h"
#include "Core/MatchManager.h"
#include "UI/GameDisplay.h"
#include "UI/InputValidator.h"
#include <iostream>

SetHandler::SetHandler(MatchManager* match) : m_match(match) {}

void SetHandler::handle(int playerId, int teamId) {
    bool setSucc = InputValidator::getYesNo("Was the set successful? (Y/N): ");

    int otherTeam = (teamId == 0) ? 1 : 0;

    if (!setSucc) {
        // Set failed - point goes to OTHER team (the attacking team)
        m_match->getScore().addPoint(otherTeam);
        m_match->getScore().setServingTeam(otherTeam);
        m_match->getStats().recordError(playerId);
        GameDisplay::showMessage("SET ERROR - Point to Team " + std::string(otherTeam == 0 ? "A" : "B") + ", serve switches");
        m_match->getRecorder().clearRally();
    }
    else {
        m_match->getStats().recordAssist(playerId);
        GameDisplay::showMessage("Good set. Rally continues...");
    }
}