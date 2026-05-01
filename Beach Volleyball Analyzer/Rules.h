#pragma once

#include <string>

class VolleyballRules {
public:
    static const int MAX_TOUCHES = 3;      // Max touches per team
    static const int WINNING_SCORE = 21;
    static const int NEED_WIN_BY = 2;
    static const int MAX_SCORE = 23;

    static bool isFourTouchViolation(int teamTouches);  // CHANGED
    static bool isDoubleTouch(int lastPlayer, int currentPlayer);
    static bool isGameOver(int scoreA, int scoreB);
    static int getPointWinnerOnError(int faultTeam);
};