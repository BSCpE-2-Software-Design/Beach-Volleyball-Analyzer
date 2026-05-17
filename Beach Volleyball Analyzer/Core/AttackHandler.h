// Beach Volleyball Analyzer\AttackHandler.h
#pragma once

class AttackHandler {
private:
    class MatchManager* m_match;
    
public:
    AttackHandler(class MatchManager* match);
    void handle(int playerId, int teamId);
};
