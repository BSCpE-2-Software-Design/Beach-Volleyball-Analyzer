// Beach Volleyball Analyzer\ServeHandler.cpp
#include "Core/ServeHandler.h"
#include "Core/MatchManager.h"
#include "UI/GameDisplay.h"
#include <iostream>
ServeHandler::ServeHandler(MatchManager* match) : m_match(match) {}

void ServeHandler::handle(int playerId, int teamId) {
    std::cout << "Serve result? [A]ce  [E]rror  [O]ther: ";
    char servRes;
    std::cin >> servRes;
    servRes = std::toupper(servRes);

    int otherTeam = (teamId == 0) ? 1 : 0;

    if (servRes == 'A') {
        m_match->getScore().handleServeResult(playerId, true);
        m_match->getStats().recordAceServe(playerId);
        m_match->getStats().recordPoint(playerId);
        GameDisplay::showMessage("SERVICE ACE! Team " + std::string(teamId == 0 ? "A" : "B") + " scores, serve continues");
        m_match->getRecorder().clearRally();
    }
    else if (servRes == 'E') {
        m_match->getScore().handleServeResult(playerId, false);
        m_match->getStats().recordError(playerId);
        GameDisplay::showMessage("SERVE ERROR - Point to Team " + std::string(otherTeam == 0 ? "A" : "B") + ", serve switches");
        m_match->getRecorder().clearRally();
    }
    else if (servRes == 'O') {
        std::cout << "Serve recorded. Rally continues...\n";
    }
}