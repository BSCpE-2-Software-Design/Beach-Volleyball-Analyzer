#pragma once

#include <vector>
#include <string>

struct Touch {
    int playerId;
    std::string actionType;
    int teamId;
};

class RallyRecorder {
private:
    std::vector<Touch> m_currentRally;
    int m_teamATouches;      // NEW: Track Team A touches this rally
    int m_teamBTouches;      // NEW: Track Team B touches this rally
    int m_lastTouchPlayer;
    int m_lastTouchTeam;
    bool m_rallyEnded;
    std::string m_lastError;

public:
    RallyRecorder();
    bool addTouch(int playerId, const std::string& action, int teamId);
    bool checkFourTouchViolation(int teamId) const;  // CHANGED: takes teamId
    bool checkDoubleTouch(int playerId) const;
    void endRallyWithPoint(int scoringPlayer, int scoringTeam);
    void endRallyWithError(const std::string& errorType, int playerId, int teamId);
    void clearRally();
    bool isRallyEnded() const;
    std::string getLastError() const;
    std::vector<Touch> getCurrentRally() const;
    int getLastTouchTeam() const;
};