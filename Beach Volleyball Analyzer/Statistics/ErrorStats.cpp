// Beach Volleyball Analyzer\ErrorStats.cpp
#include "ErrorStats.h"
#include <iostream>
#include <iomanip>

void ErrorStats::recordTouch(int playerId) {
    m_touches[playerId]++;
}

void ErrorStats::recordError(int playerId) {
    m_errors[playerId]++;
}

void ErrorStats::recordPoint(int playerId) {
    m_points[playerId]++;
}

int ErrorStats::getTouches(int playerId) const {
    auto it = m_touches.find(playerId);
    return it != m_touches.end() ? it->second : 0;
}

int ErrorStats::getErrors(int playerId) const {
    auto it = m_errors.find(playerId);
    return it != m_errors.end() ? it->second : 0;
}

int ErrorStats::getPoints(int playerId) const {
    auto it = m_points.find(playerId);
    return it != m_points.end() ? it->second : 0;
}

void ErrorStats::printErrorStats() const {
    std::cout << "\n=== ERROR STATS ===\n";
    for (const auto& pair : m_touches) {
        int playerId = pair.first;
        std::cout << "Player " << playerId << ": "
                  << "Touches: " << getTouches(playerId)
                  << " | Errors: " << getErrors(playerId)
                  << " | Points: " << getPoints(playerId) << "\n";
    }
}