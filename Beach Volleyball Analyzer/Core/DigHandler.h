#pragma once

class DigHandler {
private:
    class MatchManager* m_match;
    
public:
    DigHandler(class MatchManager* match);
    void handle(int playerId, int teamId);
};
