#pragma once

#include "RallyRecorder.h"
#include "ScoreKeeper.h"
#include "StatTracker.h"

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