// Beach Volleyball Analyzer TEST\ScoringRules_TEST.cpp

#include "doctest.h"
#include "Rules/ScoringRules.h"

TEST_CASE("ScoringRules - isGameOver") {
    SUBCASE("Team A wins 21-19") {
        CHECK(ScoringRules::isGameOver(21, 19));
    }

    SUBCASE("Team B wins 21-15") {
        CHECK(ScoringRules::isGameOver(15, 21));
    }

    SUBCASE("Game not finished 20-20") {
        CHECK(!ScoringRules::isGameOver(20, 20));
    }

    SUBCASE("Deuce 25-23") {
        CHECK(ScoringRules::isGameOver(25, 23));
    }

    SUBCASE("Not enough score 20-18") {
        CHECK(!ScoringRules::isGameOver(20, 18));
    }

    SUBCASE("Equal high scores") {
        CHECK(!ScoringRules::isGameOver(25, 25));
    }
}

TEST_CASE("ScoringRules - isSetWon") {
    SUBCASE("Team wins 21-15") {
        CHECK(ScoringRules::isSetWon(21, 15));
    }

    SUBCASE("Team wins 21-19") {
        CHECK(ScoringRules::isSetWon(21, 19));
    }

    SUBCASE("Team does not win 20-15") {
        CHECK(!ScoringRules::isSetWon(20, 15));
    }

    SUBCASE("Equal scores") {
        CHECK(!ScoringRules::isSetWon(20, 20));
    }

    SUBCASE("Behind by 1") {
        CHECK(!ScoringRules::isSetWon(21, 20));
    }
}

TEST_CASE("ScoringRules - constants") {
    REQUIRE_EQ(ScoringRules::WINNING_SCORE, 21);
    REQUIRE_EQ(ScoringRules::NEED_WIN_BY, 2);
}