// Beach Volleyball Analyzer\ServeHandler.h
#pragma once

class ServeHandler {
private:
    class MatchManager* m_match;
    
public:
    ServeHandler(class MatchManager* match);
    void handle(int playerId, int teamId);
};
