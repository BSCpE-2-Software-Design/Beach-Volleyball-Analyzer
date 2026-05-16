// Beach Volleyball Analyzer\TouchRules.h
#pragma once

class TouchRules {
public:
    static const int MAX_TOUCHES = 3;

    static bool isFourTouchViolation(int touches);
    static bool isDoubleTouch(int lastPlayer, int currentPlayer);
};
