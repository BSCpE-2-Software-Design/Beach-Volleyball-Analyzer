// Beach Volleyball Analyzer\PlayerAwardsDisplay.cpp
#include "Statistics/PlayerAwardsDisplay.h"
#include <iostream>
#include <map>
#include <algorithm>

int PlayerAwardsDisplay::calculateMVP(int playerId, const AttackStats& attackStats,
                                       const DefenseStats& defenseStats,
                                       const ErrorStats& errorStats) {
    int score = 0;
    score += attackStats.getAttacks(playerId) * 2;      // Attack attempts
    score += attackStats.getAceServes(playerId) * 3;    // Ace serves (valuable)
    score += attackStats.getAssists(playerId) * 2;      // Assists
    score += defenseStats.getBlockPoints(playerId) * 3; // Block points
    score += defenseStats.getDigAttempts(playerId);     // Dig attempts
    score += errorStats.getPoints(playerId) * 2;        // Points scored
    score -= errorStats.getErrors(playerId) * 2;        // Errors (penalty)
    return score;
}

void PlayerAwardsDisplay::displayAwards(const AttackStats& attackStats,
                                        const DefenseStats& defenseStats,
                                        const ErrorStats& errorStats) {
    std::cout << "\n";
    std::cout << "====================================================================\n";
    std::cout << "                          PLAYER AWARDS\n";
    std::cout << "====================================================================\n";

    // Find MVP (0-3 players)
    int mvpPlayer = -1;
    int mvpScore = -999;
    for (int i = 0; i < 4; ++i) {
        int score = calculateMVP(i, attackStats, defenseStats, errorStats);
        if (score > mvpScore) {
            mvpScore = score;
            mvpPlayer = i;
        }
    }

    // Find best attacker
    int bestAttacker = -1;
    int bestAttackCount = -1;
    for (int i = 0; i < 4; ++i) {
        int attacks = attackStats.getAttacks(i) - attackStats.getAttackErrors(i);
        if (attacks > bestAttackCount) {
            bestAttackCount = attacks;
            bestAttacker = i;
        }
    }

    // Find best blocker
    int bestBlocker = -1;
    int bestBlockCount = -1;
    for (int i = 0; i < 4; ++i) {
        int blocks = defenseStats.getBlockPoints(i);
        if (blocks > bestBlockCount) {
            bestBlockCount = blocks;
            bestBlocker = i;
        }
    }

    // Find best digger
    int bestDigger = -1;
    int bestDigCount = -1;
    for (int i = 0; i < 4; ++i) {
        int digs = defenseStats.getDigAttempts(i) - defenseStats.getDigErrors(i);
        if (digs > bestDigCount) {
            bestDigCount = digs;
            bestDigger = i;
        }
    }

    // Display awards
    if (mvpPlayer != -1) {
        std::cout << "MVP: Player " << mvpPlayer << "\n";
    }

    if (bestAttacker != -1) {
        std::cout << "Best Attacker: Player " << bestAttacker 
                  << " (" << bestAttackCount << " successful attacks)\n";
    }

    if (bestBlocker != -1) {
        std::cout << " Best Blocker: Player " << bestBlocker 
                  << " (" << bestBlockCount << " block points)\n";
    }

    if (bestDigger != -1) {
        std::cout << "Best Digger: Player " << bestDigger 
                  << " (" << bestDigCount << " successful digs)\n";
    }

    std::cout << "====================================================================\n\n";
}