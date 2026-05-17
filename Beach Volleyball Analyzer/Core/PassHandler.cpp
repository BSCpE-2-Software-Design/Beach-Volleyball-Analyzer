#include "Core/PassHandler.h"
#include "Core/MatchManager.h"
#include "UI/GameDisplay.h"
#include "UI/InputValidator.h"
#include <iostream>

PassHandler::PassHandler(MatchManager* match) : m_match(match) {}

void PassHandler::handle(int playerId, int teamId) {
    bool passSucc = InputValidator::getYesNo("Was the pass successful? (Y/N): ");

    int otherTeam = (teamId == 0) ? 1 : 0;

    if (!passSucc) {
        // Pass failed - point goes to OTHER team (the attacking team)
        m_match->getScore().addPoint(otherTeam);
        m_match->getScore().setServingTeam(otherTeam);
        m_match->getStats().recordError(playerId);
        GameDisplay::showMessage("PASS ERROR - Point to Team " + std::string(otherTeam == 0 ? "A" : "B") + ", serve switches");
        m_match->getRecorder().clearRally();
    }
    else {
        GameDisplay::showMessage("Good pass. Rally continues...");
    }
}