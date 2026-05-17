#include "doctest.h"
#include "Rules/ScoringRules.h"

TEST_CASE("ScoringRules - isGameOver") {
    SUBCASE("Team A wins 21-19") {
        CHECK(ScoringRules::isGameOver(21, 19) == true);
    }

    SUBCASE("Team B wins 21-15") {
        CHECK(ScoringRules::isGameOver(15, 21) == true);
    }

    SUBCASE("Game not finished 20-20") {
        CHECK(ScoringRules::isGameOver(20, 20) == false);
    }

    SUBCASE("Deuce 25-23") {
        CHECK(ScoringRules::isGameOver(25, 23) == true);
    }

    SUBCASE("Not enough score 20-18") {
        CHECK(ScoringRules::isGameOver(20, 18) == false);
    }

    SUBCASE("Equal high scores") {
        CHECK(ScoringRules::isGameOver(25, 25) == false);
    }
}

TEST_CASE("ScoringRules - isSetWon") {
    SUBCASE("Team wins 21-15") {
        CHECK(ScoringRules::isSetWon(21, 15) == true);
    }

    SUBCASE("Team wins 21-19") {
        CHECK(ScoringRules::isSetWon(21, 19) == true);
    }

    SUBCASE("Team does not win 20-15") {
        CHECK(ScoringRules::isSetWon(20, 15) == false);
    }

    SUBCASE("Equal scores") {
        CHECK(ScoringRules::isSetWon(20, 20) == false);
    }

    SUBCASE("Behind by 1") {
        CHECK(ScoringRules::isSetWon(21, 20) == false);
    }
}

TEST_CASE("ScoringRules - constants") {
    REQUIRE(ScoringRules::WINNING_SCORE == 21);
    REQUIRE(ScoringRules::NEED_WIN_BY == 2);
}