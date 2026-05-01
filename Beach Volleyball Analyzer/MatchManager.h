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
    int m_selectedPlayer;

public:
    MatchManager();
    void run();
    void processInput();
    void displayAll();
    bool isGameRunning() const;
};