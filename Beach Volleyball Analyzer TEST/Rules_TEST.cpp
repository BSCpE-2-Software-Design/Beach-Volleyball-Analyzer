// Beach Volleyball Analyzer TEST\Rules_TEST.cpp

#include "doctest.h"
#include "Rules/Rules.h"

TEST_CASE("VolleyballRules - isFourTouchViolation delegated") {
    SUBCASE("3 touches - no violation") {
        CHECK(!VolleyballRules::isFourTouchViolation(3));
    }

    SUBCASE("4 touches - violation") {
        CHECK(VolleyballRules::isFourTouchViolation(4));
    }
}

TEST_CASE("VolleyballRules - isDoubleTouch delegated") {
    SUBCASE("Same player - double touch") {
        auto res = VolleyballRules::isDoubleTouch(1, 1);
        CHECK(res);
    }

    SUBCASE("Different players") {
        auto res = VolleyballRules::isDoubleTouch(0, 2);
        CHECK(!res);
    }
}

TEST_CASE("VolleyballRules - isGameOver delegated") {
    SUBCASE("Team A wins") {
        auto res = VolleyballRules::isGameOver(21, 19);
        CHECK(res);
    }

    SUBCASE("Game not finished") {
        auto res = VolleyballRules::isGameOver(20, 18);
        CHECK(!res);
    }
}

TEST_CASE("VolleyballRules - isSetWon delegated") {
    SUBCASE("Team wins set") {
        auto res = VolleyballRules::isSetWon(21, 15);
        CHECK(res);
    }

    SUBCASE("Team does not win") {
        auto res = VolleyballRules::isSetWon(20, 19);
        CHECK(!res);
    }
}

TEST_CASE("VolleyballRules - comprehensive game scenario") {
    SUBCASE("Full game simulation") {
        auto r0 = VolleyballRules::isGameOver(0, 0);
        CHECK(!r0);
        auto r1 = VolleyballRules::isGameOver(10, 8);
        CHECK(!r1);
        auto r2 = VolleyballRules::isGameOver(20, 19);
        CHECK(!r2);
        auto r3 = VolleyballRules::isGameOver(21, 19);
        CHECK(r3);
    }

    SUBCASE("Touch rules during rally") {
        CHECK(!VolleyballRules::isFourTouchViolation(1));
        CHECK(!VolleyballRules::isFourTouchViolation(2));
        CHECK(!VolleyballRules::isFourTouchViolation(3));
        CHECK(VolleyballRules::isFourTouchViolation(4));
    }
}