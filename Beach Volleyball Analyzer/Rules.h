#pragma once

class VolleyballRules {
public:
    static const int MAX_TOUCHES = 3;
    static const int WINNING_SCORE = 21;
    static const int NEED_WIN_BY = 2;

    static bool isFourTouchViolation(int touches);
    static bool isDoubleTouch(int lastPlayer, int currentPlayer);
    static bool isGameOver(int scoreA, int scoreB);
};