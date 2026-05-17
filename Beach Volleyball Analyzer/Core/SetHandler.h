// Beach Volleyball Analyzer\SetHandler.h
#pragma once

class SetHandler {
private:
    class MatchManager* m_match;
    
public:
    SetHandler(class MatchManager* match);
    void handle(int playerId, int teamId);
};
