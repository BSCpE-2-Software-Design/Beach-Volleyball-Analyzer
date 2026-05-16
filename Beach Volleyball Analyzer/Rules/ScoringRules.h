// Beach Volleyball Analyzer\ScoringRules.h
#pragma once

class ScoringRules {
public:
    static const int WINNING_SCORE = 21;
    static const int NEED_WIN_BY = 2;

    static bool isGameOver(int scoreA, int scoreB);
    static bool isSetWon(int teamScore, int opponentScore);
};
