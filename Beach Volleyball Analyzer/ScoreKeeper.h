#pragma once

#include <utility>

class ScoreKeeper {
private:
    int m_teamAScore;
    int m_teamBScore;
    int m_servingTeam;

public:
    ScoreKeeper();
    void addPoint(int team);
    std::pair<int, int> getScores() const;
    bool isSetFinished() const;
    int getWinner() const;
    void switchServe();
    int getServingTeam() const;
    void reset();
};

