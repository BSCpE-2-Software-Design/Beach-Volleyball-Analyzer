#include "Scoring/ScoreKeeper.h"
#include "Rules/Rules.h"
#include <iostream>

ScoreKeeper::ScoreKeeper()
    : m_teamAScore(0), m_teamBScore(0), m_servingTeam(0),
    m_currentServerA(0), m_currentServerB(2) {
}

void ScoreKeeper::addPoint(int team) {
    if (team == 0) {
        m_teamAScore++;
    }       
    else {
        m_teamBScore++;
    }
    // When a team scores a point, they will serve next.
    if (team == 0 || team == 1) {
        m_servingTeam = team;
    }
}

void ScoreKeeper::handleServeResult(int servingPlayer, bool pointWon) {
    int team = (servingPlayer < 2) ? 0 : 1;

    std::cout << "=== DEBUG ===" << std::endl;
    std::cout << "Serving player: " << servingPlayer << " (Team " << team << ")" << std::endl;
    std::cout << "Point won: " << pointWon << std::endl;
    std::cout << "Current serving team before: " << m_servingTeam << std::endl;

    if (pointWon == true) {
        // SERVER WON THE POINT
        addPoint(team);
        // Same team serves, same player serves again
        m_servingTeam = team;
        // Keep the same server
        if (team == 0) {
            m_currentServerA = servingPlayer;
        }
        else {
            m_currentServerB = servingPlayer;
        }
        std::cout << "WIN: Team " << team << " keeps serve with Player " << servingPlayer << std::endl;
    }
    else {
        // SERVER LOST THE POINT - Point goes to OTHER team
        int otherTeam = (team == 0) ? 1 : 0;
        addPoint(otherTeam);

        // SWITCH SERVE TO THE OTHER TEAM
        m_servingTeam = otherTeam;

        if (team == 0) {
            // Team A lost - choose the other player from the one who just served
            m_currentServerA = (servingPlayer == 0) ? 1 : 0;
            std::cout << "Team A lost serve. Next Team A server will be: " << m_currentServerA << std::endl;
        }
        else {
            // Team B lost - choose the other player from the one who just served
            m_currentServerB = (servingPlayer == 2) ? 3 : 2;
            std::cout << "Team B lost serve. Next Team B server will be: " << m_currentServerB << std::endl;
        }

        std::cout << "LOSS: Point to Team " << otherTeam << ". ";
        std::cout << "Now Team " << otherTeam << " serves with Player " << getCurrentServer() << std::endl;
    }

    std::cout << "Serving team after: " << m_servingTeam << std::endl;
    std::cout << "Current server: " << getCurrentServer() << std::endl;
    std::cout << "Score: " << m_teamAScore << "-" << m_teamBScore << std::endl;
    std::cout << "==============" << std::endl;
}

int ScoreKeeper::getCurrentServer() const {
    if (m_servingTeam == 0) {
        return m_currentServerA;
    }
    else {
        return m_currentServerB;
    }
}

std::pair<int, int> ScoreKeeper::getScores() const {
    return { m_teamAScore, m_teamBScore };
}

bool ScoreKeeper::isSetFinished() const {
    return VolleyballRules::isGameOver(m_teamAScore, m_teamBScore);
}

int ScoreKeeper::getServingTeam() const {
    return m_servingTeam;
}

void ScoreKeeper::reset() {
    m_teamAScore = 0;
    m_teamBScore = 0;
    m_servingTeam = 0;
    m_currentServerA = 0;
    m_currentServerB = 2;
}

void ScoreKeeper::setServingTeam(int team) {
    if (team == 0 || team == 1) {
        m_servingTeam = team;
    }
}