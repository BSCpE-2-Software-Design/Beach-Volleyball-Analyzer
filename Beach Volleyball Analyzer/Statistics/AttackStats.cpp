#include "Statistics/AttackStats.h"
#include <iostream>
#include <iomanip>
#include <set>

void AttackStats::recordAttack(int playerId, bool error) {
    m_attacks[playerId]++;
    if (error) {
        m_attackErrors[playerId]++;
    }
}

void AttackStats::recordAceServe(int playerId) {
    m_aceServes[playerId]++;
}

void AttackStats::recordAssist(int playerId) {
    m_assists[playerId]++;
}

void AttackStats::recordPoint(int playerId) {
    m_points[playerId]++;
}

int AttackStats::getAttacks(int playerId) const {
    auto it = m_attacks.find(playerId);
    return it != m_attacks.end() ? it->second : 0;
}

int AttackStats::getAttackErrors(int playerId) const {
    auto it = m_attackErrors.find(playerId);
    return it != m_attackErrors.end() ? it->second : 0;
}

int AttackStats::getAceServes(int playerId) const {
    auto it = m_aceServes.find(playerId);
    return it != m_aceServes.end() ? it->second : 0;
}

int AttackStats::getAssists(int playerId) const {
    auto it = m_assists.find(playerId);
    return it != m_assists.end() ? it->second : 0;
}

int AttackStats::getPoints(int playerId) const {
    auto it = m_points.find(playerId);
    return it != m_points.end() ? it->second : 0;
}

void AttackStats::printAttackStats() const {
    std::cout << "\n=== ATTACK STATS ===\n";

    // Collect all unique player IDs from all maps
    std::set<int> allPlayers;
    for (const auto& pair : m_attacks) allPlayers.insert(pair.first);
    for (const auto& pair : m_aceServes) allPlayers.insert(pair.first);
    for (const auto& pair : m_assists) allPlayers.insert(pair.first);
    for (const auto& pair : m_attackErrors) allPlayers.insert(pair.first);
    for (const auto& pair : m_points) allPlayers.insert(pair.first);

    // Print header
    std::cout << std::left
        << std::setw(10) << "Player"
        << std::setw(12) << "Attacks"
        << std::setw(12) << "Errors"
        << std::setw(10) << "Aces"
        << std::setw(12) << "Assists"
        << std::setw(10) << "Points" << "\n";
    std::cout << std::string(56, '-') << "\n";

    // Print stats for all players
    for (int playerId : allPlayers) {
        std::cout << std::left
            << std::setw(10) << playerId
            << std::setw(12) << getAttacks(playerId)
            << std::setw(12) << getAttackErrors(playerId)
            << std::setw(10) << getAceServes(playerId)
            << std::setw(12) << getAssists(playerId)
            << std::setw(10) << getPoints(playerId) << "\n";
    }
}