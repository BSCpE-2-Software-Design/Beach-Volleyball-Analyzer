#include "StatTracker.h"
#include <iostream>

void StatTracker::recordTouch(int playerId, const std::string& action) {
    m_touchesByPlayer[playerId]++;
}

void StatTracker::recordError(int playerId, const std::string& errorType) {
    m_errorsByPlayer[playerId]++;
}

void StatTracker::recordPoint(int playerId) {
    m_pointsByPlayer[playerId]++;
}

void StatTracker::printReport() const {
    std::cout << "\n=========================================\n";
    std::cout << "         FINAL STATISTICS\n";
    std::cout << "=========================================\n";
    std::cout << "Player  | Touches | Errors | Points\n";
    std::cout << "--------|---------|--------|-------\n";
    for (int i = 0; i < 4; i++) {
        printf("  %d      |    %d    |   %d    |   %d\n",
            i, getTouches(i), getErrors(i), getPoints(i));
    }
    std::cout << "=========================================\n";
}

int StatTracker::getTouches(int playerId) const {
    auto it = m_touchesByPlayer.find(playerId);
    return (it != m_touchesByPlayer.end()) ? it->second : 0;
}

int StatTracker::getErrors(int playerId) const {
    auto it = m_errorsByPlayer.find(playerId);
    return (it != m_errorsByPlayer.end()) ? it->second : 0;
}

int StatTracker::getPoints(int playerId) const {
    auto it = m_pointsByPlayer.find(playerId);
    return (it != m_pointsByPlayer.end()) ? it->second : 0;
}

void StatTracker::reset() {
    m_touchesByPlayer.clear();
    m_errorsByPlayer.clear();
    m_pointsByPlayer.clear();
}