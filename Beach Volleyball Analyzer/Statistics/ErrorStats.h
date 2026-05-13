// Beach Volleyball Analyzer\ErrorStats.h
#pragma once

#include <map>

class ErrorStats {
private:
    std::map<int, int> m_touches;
    std::map<int, int> m_errors;
    std::map<int, int> m_points;

public:
    void recordTouch(int playerId);
    void recordError(int playerId);
    void recordPoint(int playerId);
    
    int getTouches(int playerId) const;
    int getErrors(int playerId) const;
    int getPoints(int playerId) const;
    
    void printErrorStats() const;
};
