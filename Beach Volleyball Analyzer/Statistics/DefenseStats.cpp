#include "DefenseStats.h"
#include <iostream>
#include <iomanip>
#include <set>

void DefenseStats::recordBlockPoint(int playerId) {
    m_blockPoints[playerId]++;
    m_blockAttempts[playerId]++;
}

void DefenseStats::recordUnsuccessfulBlock(int playerId) {
    m_blockAttempts[playerId]++;
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

int DefenseStats::getBlockAttempts(int playerId) const {
    auto it = m_blockAttempts.find(playerId);
    return it != m_blockAttempts.end() ? it->second : 0;
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

    // Collect all unique player IDs from all maps
    std::set<int> allPlayers;
    for (const auto& pair : m_blockPoints) allPlayers.insert(pair.first);
    for (const auto& pair : m_blockAttempts) allPlayers.insert(pair.first);
    for (const auto& pair : m_digAttempts) allPlayers.insert(pair.first);
    for (const auto& pair : m_digErrors) allPlayers.insert(pair.first);

    // Print header
    std::cout << std::left
        << std::setw(10) << "Player"
        << std::setw(15) << "Blocks"
        << std::setw(15) << "Block Points"
        << std::setw(12) << "Digs"
        << std::setw(12) << "Dig Errors" << "\n";
    std::cout << std::string(64, '-') << "\n";

    // Print stats for all players
    for (int playerId : allPlayers) {
        int blockAttempts = getBlockAttempts(playerId);
        int blockPoints = getBlockPoints(playerId);
        std::string blockStr = std::to_string(blockPoints) + "/" + std::to_string(blockAttempts);

        std::cout << std::left
            << std::setw(10) << playerId
            << std::setw(15) << blockStr
            << std::setw(15) << blockPoints
            << std::setw(12) << getDigAttempts(playerId)
            << std::setw(12) << getDigErrors(playerId) << "\n";
    }
}