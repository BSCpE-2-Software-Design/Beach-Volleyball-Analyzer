#include "Rules.h"
#include <cmath>

bool VolleyballRules::isFourTouchViolation(int teamTouches) {
    return teamTouches > MAX_TOUCHES;  // Same team touches > 3 = violation
}

bool VolleyballRules::isDoubleTouch(int lastPlayer, int currentPlayer) {
    return (lastPlayer == currentPlayer);
}

bool VolleyballRules::isGameOver(int scoreA, int scoreB) {
    if (scoreA >= WINNING_SCORE || scoreB >= WINNING_SCORE) {
        int diff = abs(scoreA - scoreB);
        if (diff >= NEED_WIN_BY) {
            return true;
        }
        if (scoreA >= MAX_SCORE || scoreB >= MAX_SCORE) {
            return true;
        }
    }
    return false;
}

int VolleyballRules::getPointWinnerOnError(int faultTeam) {
    return (faultTeam == 0) ? 1 : 0;
}