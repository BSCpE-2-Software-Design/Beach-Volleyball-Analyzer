#pragma once

#include <utility>

class ScoreKeeper {
private:
    int m_teamAScore;
    int m_teamBScore;
    int m_servingTeam;
    int m_currentServerA;   // Current server for Team A (0 or 1)
    int m_currentServerB;   // Current server for Team B (2 or 3)

public:
    ScoreKeeper();
    void addPoint(int team);
    void handleServeResult(int servingPlayer, bool pointWon);
    int getCurrentServer() const;
    std::pair<int, int> getScores() const;
    bool isSetFinished() const;
    int getServingTeam() const;
    void reset();
    void setServingTeam(int team);
};