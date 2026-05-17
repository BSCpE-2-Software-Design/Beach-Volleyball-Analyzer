#pragma once
#include <map>
#include <string>

class DefenseStats {
private:
    std::map<int, int> m_blockPoints;           // Successful block points
    std::map<int, int> m_blockAttempts;         // Total block attempts
    std::map<int, int> m_digAttempts;           // Total dig attempts
    std::map<int, int> m_digErrors;             // Dig errors

public:
    void recordBlockPoint(int playerId);
    void recordUnsuccessfulBlock(int playerId);
    void recordDig(int playerId, bool error = false);

    int getBlockPoints(int playerId) const;
    int getBlockAttempts(int playerId) const;
    int getDigAttempts(int playerId) const;
    int getDigErrors(int playerId) const;

    void printDefenseStats() const;
};