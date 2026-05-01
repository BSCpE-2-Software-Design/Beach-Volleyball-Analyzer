#pragma once

#include <map>
#include <string>

class StatTracker {
private:
    std::map<int, int> m_touchesByPlayer;
    std::map<int, int> m_errorsByPlayer;
    std::map<int, int> m_pointsByPlayer;

public:
    void recordTouch(int playerId, const std::string& action);
    void recordError(int playerId, const std::string& errorType);
    void recordPoint(int playerId);
    void printReport() const;
    int getTouches(int playerId) const;
    int getErrors(int playerId) const;
    int getPoints(int playerId) const;
    void reset();
};

