#include "Rules.h"
#include <cstdlib>

bool VolleyballRules::isFourTouchViolation(int touches) {
    return touches > MAX_TOUCHES;
}

bool VolleyballRules::isDoubleTouch(int lastPlayer, int currentPlayer) {
    return lastPlayer == currentPlayer;
}

bool VolleyballRules::isGameOver(int scoreA, int scoreB) {
    if (scoreA >= WINNING_SCORE || scoreB >= WINNING_SCORE) {
        int diff = abs(scoreA - scoreB);
        if (diff >= NEED_WIN_BY) return true;
    }
    return false;
}