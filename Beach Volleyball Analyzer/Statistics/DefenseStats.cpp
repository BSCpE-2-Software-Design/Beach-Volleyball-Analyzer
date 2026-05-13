// Beach Volleyball Analyzer\DefenseStats.cpp
#include "DefenseStats.h"
#include <iostream>
#include <iomanip>

void DefenseStats::recordBlockPoint(int playerId) {
    m_blockPoints[playerId]++;
}

void DefenseStats::recordUnsuccessfulBlock(int playerId) {
    // Block attempted but unsuccessful - no stat recorded
}

void DefenseStats::recordDig(int playerId, bool error) {
    m_digAttempts[playerId]++;
    if (error) {
        m_digErrors[playerId]++;
    }
}

int DefenseStats::getBlockPoints(int playerId) const {
    auto it = m_blockPoints.find(playerId);
    return it != m_blockPoints.end() ? it->second : 0;
}

int DefenseStats::getDigAttempts(int playerId) const {
    auto it = m_digAttempts.find(playerId);
    return it != m_digAttempts.end() ? it->second : 0;
}

int DefenseStats::getDigErrors(int playerId) const {
    auto it = m_digErrors.find(playerId);
    return it != m_digErrors.end() ? it->second : 0;
}

void DefenseStats::printDefenseStats() const {
    std::cout << "\n=== DEFENSE STATS ===\n";
    for (const auto& pair : m_blockPoints) {
        int playerId = pair.first;
        std::cout << "Player " << playerId << ": "
                  << "Block Points: " << getBlockPoints(playerId) << "\n";
    }
    for (const auto& pair : m_digAttempts) {
        int playerId = pair.first;
        std::cout << "Player " << playerId << ": "
                  << "Digs: " << getDigAttempts(playerId)
                  << " | Errors: " << getDigErrors(playerId) << "\n";
    }
}