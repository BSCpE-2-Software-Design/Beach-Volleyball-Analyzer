#include "Statistics/StatTracker.h"
#include <iostream>
#include <iomanip>

void StatTracker::recordAttack(int playerId, bool error) {
    m_attackStats.recordAttack(playerId, error);
}

void StatTracker::recordAceServe(int playerId) {
    m_attackStats.recordAceServe(playerId);
}

void StatTracker::recordAssist(int playerId) {
    m_attackStats.recordAssist(playerId);
}

void StatTracker::recordBlockPoint(int playerId) {
    m_defenseStats.recordBlockPoint(playerId);
}

void StatTracker::recordUnsuccessfulBlock(int playerId) {
    m_defenseStats.recordUnsuccessfulBlock(playerId);
}

void StatTracker::recordDig(int playerId, bool error) {
    m_defenseStats.recordDig(playerId, error);
}

void StatTracker::recordTouch(int playerId) {
    m_errorStats.recordTouch(playerId);
}

void StatTracker::recordError(int playerId) {
    m_errorStats.recordError(playerId);
}

void StatTracker::recordPoint(int playerId) {
    m_errorStats.recordPoint(playerId);
}

void StatTracker::printReport() const {
    std::cout << "\n====== MATCH STATISTICS ======\n";
    m_errorStats.printErrorStats();
    m_attackStats.printAttackStats();
    m_defenseStats.printDefenseStats();
    PlayerAwardsDisplay::displayAwards(m_attackStats, m_defenseStats, m_errorStats);
}

void StatTracker::printDetailedStats() const {
    printReport();
}