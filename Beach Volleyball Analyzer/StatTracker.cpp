#include "StatTracker.h"
#include <iostream>

void StatTracker::recordTouch(int playerId) {
    m_touches[playerId]++;
}

void StatTracker::recordError(int playerId) {
    m_errors[playerId]++;
}

void StatTracker::recordPoint(int playerId) {
    m_points[playerId]++;
}

void StatTracker::printReport() const {
    std::cout << "\n========== STATISTICS ==========\n";
    for (int i = 0; i < 4; i++) {
        auto t = m_touches.find(i);
        auto e = m_errors.find(i);
        auto p = m_points.find(i);

        int touches = (t != m_touches.end()) ? t->second : 0;
        int errors = (e != m_errors.end()) ? e->second : 0;
        int points = (p != m_points.end()) ? p->second : 0;

        std::cout << "Player " << i << ": "
            << touches << " touches, "
            << errors << " errors, "
            << points << " points\n";
    }
    std::cout << "================================\n";
}