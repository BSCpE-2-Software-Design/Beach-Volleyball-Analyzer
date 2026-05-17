#include "AttackStats.h"
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

void AttackStats::printAttackStats() const {
    std::cout << "\n=== ATTACK STATS ===\n";
    
    // Collect all unique player IDs from all maps
    std::set<int> allPlayers;
    for (const auto& pair : m_attacks) allPlayers.insert(pair.first);
    for (const auto& pair : m_aceServes) allPlayers.insert(pair.first);
    for (const auto& pair : m_assists) allPlayers.insert(pair.first);
    for (const auto& pair : m_attackErrors) allPlayers.insert(pair.first);
    
    // Print stats for all players
    for (int playerId : allPlayers) {
        std::cout << "Player " << playerId << ": "
                  << "Attacks: " << getAttacks(playerId)
                  << " | Errors: " << getAttackErrors(playerId)
                  << " | Aces: " << getAceServes(playerId)
                  << " | Assists: " << getAssists(playerId) << "\n";
    }
}