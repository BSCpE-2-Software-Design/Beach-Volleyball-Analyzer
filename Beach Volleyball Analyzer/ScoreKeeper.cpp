#include "ScoreKeeper.h"
#include "Rules.h"

ScoreKeeper::ScoreKeeper() : m_teamAScore(0), m_teamBScore(0), m_servingTeam(0) {}

void ScoreKeeper::addPoint(int team) {
    if (team == 0) {
        m_teamAScore++;
    }
    else {
        m_teamBScore++;
    }
}

std::pair<int, int> ScoreKeeper::getScores() const {
    return { m_teamAScore, m_teamBScore };
}

bool ScoreKeeper::isSetFinished() const {
    return VolleyballRules::isGameOver(m_teamAScore, m_teamBScore);
}

int ScoreKeeper::getWinner() const {
    if (!isSetFinished()) return -1;
    return (m_teamAScore > m_teamBScore) ? 0 : 1;
}

void ScoreKeeper::switchServe() {
    m_servingTeam = (m_servingTeam == 0) ? 1 : 0;
}

int ScoreKeeper::getServingTeam() const {
    return m_servingTeam;
}

void ScoreKeeper::reset() {
    m_teamAScore = 0;
    m_teamBScore = 0;
    m_servingTeam = 0;
}