#pragma once

#include "Core/RallyRecorder.h"
#include "Scoring/ScoreKeeper.h"
#include "Statistics/StatTracker.h"
#include "Core/ServeHandler.h"
#include "Core/PassHandler.h"
#include "Core/SetHandler.h"
#include "Core/AttackHandler.h"
#include "Core/DigHandler.h"

class MatchManager {
private:
    RallyRecorder m_recorder;
    ScoreKeeper m_score;
    StatTracker m_stats;
    int m_selectedPlayer;
    bool m_waitingForAction;

    ServeHandler m_serveHandler;
    PassHandler m_passHandler;
    SetHandler m_setHandler;
    AttackHandler m_attackHandler;
    DigHandler m_digHandler;

public:
    MatchManager();
    void run();
    
    // Accessors for handlers
    RallyRecorder& getRecorder() { return m_recorder; }
    ScoreKeeper& getScore() { return m_score; }
    StatTracker& getStats() { return m_stats; }
    int getTeamFromPlayer(int playerId) const;
};