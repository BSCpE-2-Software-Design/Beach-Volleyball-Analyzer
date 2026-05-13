#pragma once

#include "Core/RallyRecorder.h"
#include "Scoring/ScoreKeeper.h"
#include "Statistics/StatTracker.h"

class MatchManager {
private:
    RallyRecorder m_recorder;
    ScoreKeeper m_score;
    StatTracker m_stats;
    int m_selectedPlayer;
    bool m_waitingForAction;

public:
    int getTeamFromPlayer(int playerId) const;

    MatchManager();
    void run();
};