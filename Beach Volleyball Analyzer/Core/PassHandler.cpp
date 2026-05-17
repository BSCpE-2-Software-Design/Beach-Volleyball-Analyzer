// Beach Volleyball Analyzer\PassHandler.cpp
#include "Core/PassHandler.h"
#include "Core/MatchManager.h"
#include "UI/GameDisplay.h"
#include <iostream>

PassHandler::PassHandler(MatchManager* match) : m_match(match) {}

void PassHandler::handle(int playerId, int teamId) {
    std::cout << "Was the pass successful? (Y/N): ";
    char passSucc;
    std::cin >> passSucc;
    passSucc = std::toupper(passSucc);

    if (passSucc == 'N') {
        int otherTeam = (teamId == 0) ? 1 : 0;
        int servingPlayer = m_match->getRecorder().getServingPlayer();
        if (servingPlayer == -1) servingPlayer = m_match->getScore().getCurrentServer();
        m_match->getScore().handleServeResult(servingPlayer, false);
        m_match->getStats().recordError(playerId);
        GameDisplay::showMessage("PASS ERROR - Point to Team " + std::string(otherTeam == 0 ? "A" : "B") + ", serve switches");
        m_match->getRecorder().clearRally();
    }
    else {
        std::cout << "Good pass. Rally continues...\n";
    }
}