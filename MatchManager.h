#pragma once

#include "RallyRecorder.h"
#include "ScoreKeeper.h"
#include "StatTracker.h"

class MatchManager {
private:
    RallyRecorder m_recorder;
    ScoreKeeper m_score;
    StatTracker m_stats;
    bool m_running;
    int m_selectedPlayer; // added: track currently selected player

public:
    MatchManager();
    void run();
    void recordTouch(int playerId, const std::string& action);
    void recordError(const std::string& errorType, int playerId);
    void showHelp(); // renamed to match implementation in MatchManager.cpp
};