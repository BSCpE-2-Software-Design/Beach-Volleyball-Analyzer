#include "Core/RallyRecorder.h"

RallyRecorder::RallyRecorder()
    : m_consecutiveTouchesSameTeam(0), m_lastTouchPlayer(-1),
    m_lastTouchTeam(-1), m_hasServed(false), m_servingPlayer(-1) {
}

bool RallyRecorder::addTouch(int playerId, const std::string& action, int teamId) {
    // RULE 1: First action of every rally MUST be a serve
    if (!m_hasServed && action != "serve") {
        m_lastError = "RALLY MUST START WITH SERVE";
        return false;
    }

    // RULE 2: Can only serve ONCE per rally (at the beginning)
    if (m_hasServed && action == "serve") {
        m_lastError = "CANNOT SERVE AGAIN - Rally already started";
        return false;
    }

    // Mark that serve has occurred
    if (action == "serve") {
        m_hasServed = true;
        m_servingPlayer = playerId;
    }

    // RULE 3: Double touch (same player twice in a row on same team)
    if (m_lastTouchPlayer == playerId && m_lastTouchTeam == teamId) {
        m_lastError = "DOUBLE TOUCH";
        return false;
    }
    
    // RULE 4: Team change - reset consecutive counter
    if (m_lastTouchTeam != teamId && m_lastTouchTeam != -1) {
        m_consecutiveTouchesSameTeam = 0;
    }

    // Add touch
    Touch t = { playerId, action, teamId };
    m_currentRally.push_back(t);

    m_consecutiveTouchesSameTeam++;
    m_lastTouchPlayer = playerId;
    m_lastTouchTeam = teamId;

    // RULE 5: 4-touch violation (same team touched 4 times in a row)
    if (m_consecutiveTouchesSameTeam > 3) {
        m_lastError = "FOUR TOUCH VIOLATION - Same team touched 4 times";
        return false;
    }

    return true;
}

bool RallyRecorder::addUnsuccessfulBlock(int playerId, int teamId) {
    // NEW RULE: Unsuccessful block does NOT count toward 4-touch limit
    // But it IS recorded in the rally log for reference
    
    // RULE 3: Double touch check
    if (m_lastTouchPlayer == playerId && m_lastTouchTeam == teamId) {
        m_lastError = "DOUBLE TOUCH";
        return false;
    }
    
    // RULE 4: Team change - reset consecutive counter
    if (m_lastTouchTeam != teamId && m_lastTouchTeam != -1) {
        m_consecutiveTouchesSameTeam = 0;
    }

    // Add touch to rally log (for record-keeping)
    Touch t = { playerId, "block (unsuccessful)", teamId };
    m_currentRally.push_back(t);

    // Update last touch info for double-touch checking
    m_lastTouchPlayer = playerId;
    m_lastTouchTeam = teamId;

    // DO NOT increment m_consecutiveTouchesSameTeam
    // This allows the 4-touch rule to be legal
    
    return true;
}

void RallyRecorder::clearRally() {
    m_currentRally.clear();
    m_consecutiveTouchesSameTeam = 0;
    m_lastTouchPlayer = -1;
    m_lastTouchTeam = -1;
    m_lastError = "";
    m_hasServed = false;
    m_servingPlayer = -1;
}

std::string RallyRecorder::getLastError() const {
    return m_lastError;
}

int RallyRecorder::getConsecutiveTouches() const {
    return m_consecutiveTouchesSameTeam;
}

int RallyRecorder::getLastTouchTeam() const {
    return m_lastTouchTeam;
}

std::vector<Touch> RallyRecorder::getCurrentRally() const {
    return m_currentRally;
}

bool RallyRecorder::hasServed() const {
    return m_hasServed;
}

int RallyRecorder::getServingPlayer() const {
    return m_servingPlayer;
}