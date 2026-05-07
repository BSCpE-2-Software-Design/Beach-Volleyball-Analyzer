#pragma once

#include <map>
#include <string>

class StatTracker {
private:
    std::map<int, int> m_touches;
    std::map<int, int> m_errors;
    std::map<int, int> m_points;

public:
    void recordTouch(int playerId);
    void recordError(int playerId);
    void recordPoint(int playerId);
    void printReport() const;
};