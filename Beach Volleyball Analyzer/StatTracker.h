#pragma once

#include <map>
#include <string>

class StatTracker {
private:
    std::map<int, int> m_touches;
    std::map<int, int> m_errors;
    std::map<int, int> m_points;
    std::map<int, int> m_attacks;           // Total attack attempts
    std::map<int, int> m_attackErrors;      // Attack errors
    std::map<int, int> m_blockPoints;       // Points from blocks
    std::map<int, int> m_digAttempts;       // Total dig attempts
    std::map<int, int> m_digErrors;         // Dig errors
    std::map<int, int> m_aceServes;         // Ace serves (direct point on serve)
    std::map<int, int> m_assists;           // Assist count (sets leading to points)

public:
    void recordTouch(int playerId);
    void recordError(int playerId);
    void recordPoint(int playerId);
    void recordAttack(int playerId, bool error = false);
    void recordBlockPoint(int playerId);
    void recordDig(int playerId, bool error = false);
    void recordAceServe(int playerId);
    void recordAssist(int playerId);
    void printReport() const;
    void printDetailedStats() const;  // New detailed stats display
};