// Beach Volleyball Analyzer\DigHandler.cpp
#include "Core/DigHandler.h"
#include "Core/MatchManager.h"
#include "UI/GameDisplay.h"
#include <iostream>

DigHandler::DigHandler(MatchManager* match) : m_match(match) {}

void DigHandler::handle(int playerId, int teamId) {
    std::cout << "Was the dig successful? (Y/N): ";
    char digSucc;
    std::cin >> digSucc;
    digSucc = std::toupper(digSucc);

    if (digSucc == 'N') {
        int otherTeam = (teamId == 0) ? 1 : 0;
        int servingPlayer = m_match->getRecorder().getServingPlayer();
        if (servingPlayer == -1) servingPlayer = m_match->getScore().getCurrentServer();
        m_match->getScore().handleServeResult(servingPlayer, false);
        m_match->getStats().recordError(playerId);
        GameDisplay::showMessage("DIG ERROR - Point to Team " + std::string(otherTeam == 0 ? "A" : "B") + ", serve switches");
        m_match->getRecorder().clearRally();
    }
    else {
        m_match->getStats().recordDig(playerId, false);
        std::cout << "Good dig. Rally continues...\n";
    }
}