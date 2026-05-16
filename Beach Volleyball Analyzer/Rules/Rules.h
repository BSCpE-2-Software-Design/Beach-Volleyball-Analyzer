// Beach Volleyball Analyzer\Rules.h
#pragma once

#include "TouchRules.h"
#include "ScoringRules.h"

class VolleyballRules {
public:
    // Access touch rules
    static bool isFourTouchViolation(int touches) {
        return TouchRules::isFourTouchViolation(touches);
    }

    static bool isDoubleTouch(int lastPlayer, int currentPlayer) {
        return TouchRules::isDoubleTouch(lastPlayer, currentPlayer);
    }

    // Access scoring rules
    static bool isGameOver(int scoreA, int scoreB) {
        return ScoringRules::isGameOver(scoreA, scoreB);
    }

    static bool isSetWon(int teamScore, int opponentScore) {
        return ScoringRules::isSetWon(teamScore, opponentScore);
    }
};