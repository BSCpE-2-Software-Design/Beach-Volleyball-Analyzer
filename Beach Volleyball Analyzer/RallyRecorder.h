#pragma once

#include <vector>
#include <string>
#include "Touch.h"

class RallyRecorder {
private:
    std::vector<Touch> m_currentRally;
    int m_consecutiveTouchesSameTeam;
    int m_lastTouchPlayer;
    int m_lastTouchTeam;
    std::string m_lastError;
    bool m_hasServed;

public:
    RallyRecorder();
    bool addTouch(int playerId, const std::string& action, int teamId);
    void clearRally();
    std::string getLastError() const;
    int getConsecutiveTouches() const;
    int getLastTouchTeam() const;
    std::vector<Touch> getCurrentRally() const;
    bool hasServed() const;
};