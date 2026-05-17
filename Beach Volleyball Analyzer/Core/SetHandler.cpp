// Beach Volleyball Analyzer\SetHandler.cpp
#include "Core/SetHandler.h"
#include "Core/MatchManager.h"
#include "UI/GameDisplay.h"
#include <iostream>
SetHandler::SetHandler(MatchManager* match) : m_match(match) {}

void SetHandler::handle(int playerId, int teamId) {
    std::cout << "Was the set successful? (Y/N): ";
    char setSucc;
    std::cin >> setSucc;
    setSucc = std::toupper(setSucc);

    if (setSucc == 'N') {
        int otherTeam = (teamId == 0) ? 1 : 0;
        int servingPlayer = m_match->getRecorder().getServingPlayer();
        if (servingPlayer == -1) servingPlayer = m_match->getScore().getCurrentServer();
        m_match->getScore().handleServeResult(servingPlayer, false);
        m_match->getStats().recordError(playerId);
        GameDisplay::showMessage("SET ERROR - Point to Team " + std::string(otherTeam == 0 ? "A" : "B") + ", serve switches");
        m_match->getRecorder().clearRally();
    }
    else {
        std::cout << "Good set. Rally continues...\n";
    }
}