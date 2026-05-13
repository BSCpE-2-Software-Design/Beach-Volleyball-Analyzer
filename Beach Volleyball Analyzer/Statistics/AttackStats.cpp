// Beach Volleyball Analyzer\AttackStats.cpp
#include "AttackStats.h"
#include <iostream>
#include <iomanip>

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
    for (const auto& pair : m_attacks) {
        int playerId = pair.first;
        std::cout << "Player " << playerId << ": "
                  << "Attacks: " << getAttacks(playerId)
                  << " | Errors: " << getAttackErrors(playerId)
                  << " | Aces: " << getAceServes(playerId)
                  << " | Assists: " << getAssists(playerId) << "\n";
    }
}