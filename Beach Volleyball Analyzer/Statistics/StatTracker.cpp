#include "Statistics/StatTracker.h"
#include <iostream>
#include <iomanip>

void StatTracker::recordTouch(int playerId) {
    m_touches[playerId]++;
}

void StatTracker::recordError(int playerId) {
    m_errors[playerId]++;
}

void StatTracker::recordPoint(int playerId) {
    m_points[playerId]++;
}

void StatTracker::recordAttack(int playerId, bool error) {
    m_attacks[playerId]++;
    if (error) {
        m_attackErrors[playerId]++;
    }
}

void StatTracker::recordBlockPoint(int playerId) {
    m_blockPoints[playerId]++;
}

void StatTracker::recordDig(int playerId, bool error) {
    m_digAttempts[playerId]++;
    if (error) {
        m_digErrors[playerId]++;
    }
}

void StatTracker::recordAceServe(int playerId) {
    m_aceServes[playerId]++;
}

void StatTracker::recordAssist(int playerId) {
    m_assists[playerId]++;
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

void StatTracker::printDetailedStats() const {
    std::cout << "\n";
    std::cout << "##########################################################################\n";
    std::cout << "#                      DETAILED PLAYER STATISTICS                        #\n";
    std::cout << "##########################################################################\n";

    for (int i = 0; i < 4; i++) {
        // Get all stats for player i
        int touches = (m_touches.find(i) != m_touches.end()) ? m_touches.at(i) : 0;
        int errors = (m_errors.find(i) != m_errors.end()) ? m_errors.at(i) : 0;
        int points = (m_points.find(i) != m_points.end()) ? m_points.at(i) : 0;
        int attacks = (m_attacks.find(i) != m_attacks.end()) ? m_attacks.at(i) : 0;
        int attackErrors = (m_attackErrors.find(i) != m_attackErrors.end()) ? m_attackErrors.at(i) : 0;
        int blockPoints = (m_blockPoints.find(i) != m_blockPoints.end()) ? m_blockPoints.at(i) : 0;
        int digAttempts = (m_digAttempts.find(i) != m_digAttempts.end()) ? m_digAttempts.at(i) : 0;
        int digErrors = (m_digErrors.find(i) != m_digErrors.end()) ? m_digErrors.at(i) : 0;
        int aceServes = (m_aceServes.find(i) != m_aceServes.end()) ? m_aceServes.at(i) : 0;
        int assists = (m_assists.find(i) != m_assists.end()) ? m_assists.at(i) : 0;

        // Calculate attack percentage
        double attackPercentage = (attacks > 0) ? ((attacks - attackErrors) * 100.0 / attacks) : 0;

        // Calculate dig success rate
        double digSuccessRate = (digAttempts > 0) ? ((digAttempts - digErrors) * 100.0 / digAttempts) : 0;

        std::cout << "\n┌─ Player " << i << "#################################################\n";
        std::cout << "# ATTACKING STATS:\n";
        std::cout << "#   • Attack Attempts    : " << std::setw(3) << attacks << "\n";
        std::cout << "#   • Attack Errors      : " << std::setw(3) << attackErrors << "\n";
        std::cout << "#   • Attack %           : " << std::fixed << std::setprecision(1) << std::setw(6) << attackPercentage << "%\n";

        std::cout << "# BLOCKING STATS:\n";
        std::cout << "#   • Block Points       : " << std::setw(3) << blockPoints << "\n";                      
        std::cout << "# DIGGING STATS:\n";
        std::cout << "#   • Dig Attempts       : " << std::setw(3) << digAttempts << "\n";
        std::cout << "#   • Dig Errors         : " << std::setw(3) << digErrors << "\n";
        std::cout << "#   • Dig Success %      : " << std::fixed << std::setprecision(1) << std::setw(6) << digSuccessRate << "%\n";

        std::cout << "# SERVING & SCORING:\n";
        std::cout << "#   • Ace Serves         : " << std::setw(3) << aceServes << "\n";
        std::cout << "#   • Points             : " << std::setw(3) << points << "\n";
        std::cout << "#   • Assists            : " << std::setw(3) << assists << "\n";

        std::cout << "# GENERAL STATS:\n";
        std::cout << "#   • Total Errors       : " << std::setw(3) << errors << "\n";
        std::cout << "#   • Total Touches      : " << std::setw(3) << touches << "\n";
        std::cout << "########################################################################\n";
    }

    std::cout << "\n##########################################################################\n";
}