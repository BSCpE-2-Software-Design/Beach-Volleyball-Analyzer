#include "RallyRecorder.h"
#include "Rules.h"

RallyRecorder::RallyRecorder()
    : m_teamATouches(0), m_teamBTouches(0), m_lastTouchPlayer(-1), m_lastTouchTeam(-1), m_rallyEnded(false) {
}

bool RallyRecorder::addTouch(int playerId, const std::string& action, int teamId) {
    if (m_rallyEnded) return false;

    // Check double touch
    if (checkDoubleTouch(playerId)) {
        m_lastError = "Double touch";
        m_rallyEnded = true;
        return false;
    }

    // Check if same team as last touch? No issue - ball goes back and forth

    // Add touch
    Touch t;
    t.playerId = playerId;
    t.actionType = action;
    t.teamId = teamId;
    m_currentRally.push_back(t);

    // Track touches per team
    if (teamId == 0) {
        m_teamATouches++;
    }
    else {
        m_teamBTouches++;
    }

    m_lastTouchPlayer = playerId;
    m_lastTouchTeam = teamId;

    // Check 4-touch violation for THIS team
    if (checkFourTouchViolation(teamId)) {
        m_lastError = "4-touch violation";
        m_rallyEnded = true;
        return false;
    }

    return true;
}

bool RallyRecorder::checkFourTouchViolation(int teamId) const {
    if (teamId == 0) {
        return m_teamATouches > VolleyballRules::MAX_TOUCHES;
    }
    else {
        return m_teamBTouches > VolleyballRules::MAX_TOUCHES;
    }
}

bool RallyRecorder::checkDoubleTouch(int playerId) const {
    return VolleyballRules::isDoubleTouch(m_lastTouchPlayer, playerId);
}

void RallyRecorder::endRallyWithPoint(int scoringPlayer, int scoringTeam) {
    m_rallyEnded = true;
}

void RallyRecorder::endRallyWithError(const std::string& errorType, int playerId, int teamId) {
    m_rallyEnded = true;
    m_lastError = errorType;
}

void RallyRecorder::clearRally() {
    m_currentRally.clear();
    m_teamATouches = 0;
    m_teamBTouches = 0;
    m_lastTouchPlayer = -1;
    m_lastTouchTeam = -1;
    m_rallyEnded = false;
    m_lastError = "";
}

bool RallyRecorder::isRallyEnded() const {
    return m_rallyEnded;
}

std::string RallyRecorder::getLastError() const {
    return m_lastError;
}

std::vector<Touch> RallyRecorder::getCurrentRally() const {
    return m_currentRally;
}

int RallyRecorder::getLastTouchTeam() const {
    return m_lastTouchTeam;
}