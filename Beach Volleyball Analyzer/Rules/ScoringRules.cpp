// Beach Volleyball Analyzer\ScoringRules.cpp
#include "ScoringRules.h"

bool ScoringRules::isGameOver(int scoreA, int scoreB) {
    if (scoreA >= WINNING_SCORE && scoreA - scoreB >= NEED_WIN_BY) {
        return true;
    }
    if (scoreB >= WINNING_SCORE && scoreB - scoreA >= NEED_WIN_BY) {
        return true;
    }
    return false;
}

bool ScoringRules::isSetWon(int teamScore, int opponentScore) {
    if (teamScore >= WINNING_SCORE && teamScore - opponentScore >= NEED_WIN_BY) {
        return true;
    }
    return false;
}