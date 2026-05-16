// Beach Volleyball Analyzer\TouchRules.cpp
#include "TouchRules.h"

bool TouchRules::isFourTouchViolation(int touches) {
    return touches > MAX_TOUCHES;
}

bool TouchRules::isDoubleTouch(int lastPlayer, int currentPlayer) {
    return lastPlayer == currentPlayer;
}