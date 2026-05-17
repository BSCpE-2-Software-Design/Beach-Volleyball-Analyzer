// Beach Volleyball Analyzer\PassHandler.h
#pragma once

class PassHandler {
private:
    class MatchManager* m_match;
    
public:
    PassHandler(class MatchManager* match);
    void handle(int playerId, int teamId);
};
