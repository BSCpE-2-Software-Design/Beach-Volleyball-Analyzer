#pragma once

#include "AttackStats.h"
#include "DefenseStats.h"
#include "ErrorStats.h"

class StatTracker {
private:
    AttackStats m_attackStats;
    DefenseStats m_defenseStats;
    ErrorStats m_errorStats;

public:
    // Attack methods
    void recordAttack(int playerId, bool error = false);
    void recordAceServe(int playerId);
    void recordAssist(int playerId);
    
    // Defense methods
    void recordBlockPoint(int playerId);
    void recordUnsuccessfulBlock(int playerId);
    void recordDig(int playerId, bool error = false);
    
    // Error methods
    void recordTouch(int playerId);
    void recordError(int playerId);
    void recordPoint(int playerId);
    
    void printReport() const;
    void printDetailedStats() const;
};