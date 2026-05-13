#pragma once

#include <map>

class AttackStats {
private:
    std::map<int, int> m_attacks;           // Total attack attempts
    std::map<int, int> m_attackErrors;      // Attack errors
    std::map<int, int> m_aceServes;         // Ace serves
    std::map<int, int> m_assists;           // Assists

public:
    void recordAttack(int playerId, bool error = false);
    void recordAceServe(int playerId);
    void recordAssist(int playerId);

    int getAttacks(int playerId) const;
    int getAttackErrors(int playerId) const;
    int getAceServes(int playerId) const;
    int getAssists(int playerId) const;

    void printAttackStats() const;
};