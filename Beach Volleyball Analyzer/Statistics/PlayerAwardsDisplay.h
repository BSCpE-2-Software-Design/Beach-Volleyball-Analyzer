#pragma once

#include "Statistics/AttackStats.h"
#include "Statistics/DefenseStats.h"
#include "Statistics/ErrorStats.h"

class PlayerAwardsDisplay {
public:
    static void displayAwards(const AttackStats& attackStats, 
                              const DefenseStats& defenseStats, 
                              const ErrorStats& errorStats);
    
private:
    static int calculateMVP(int playerId, const AttackStats& attackStats, 
                            const DefenseStats& defenseStats, 
                            const ErrorStats& errorStats);
};
