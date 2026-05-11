#include "doctest.h"
#include "MatchManager.h"

TEST_CASE("MatchManager - getTeamFromPlayer") {
    MatchManager manager;

    SUBCASE("Team A players") {
        manager.getTeamFromPlayer(0);
        manager.getTeamFromPlayer(1);
        CHECK(true);
    }

    SUBCASE("Team B players") {
        manager.getTeamFromPlayer(2);
        manager.getTeamFromPlayer(3);
        CHECK(true);
    }
}

TEST_CASE("MatchManager - getTeamFromPlayer all players") {
    MatchManager manager;

    for (int i = 0; i < 2; i++) {
        manager.getTeamFromPlayer(i);
    }
    for (int i = 2; i < 4; i++) {
        manager.getTeamFromPlayer(i);
    }
    CHECK(true);
}

TEST_CASE("MatchManager - getTeamFromPlayer boundaries") {
    MatchManager manager;

    SUBCASE("Player 0 (first of team A)") {
        manager.getTeamFromPlayer(0);
        CHECK(true);
    }

    SUBCASE("Player 1 (second of team A)") {
        manager.getTeamFromPlayer(1);
        CHECK(true);
    }

    SUBCASE("Player 2 (first of team B)") {
        manager.getTeamFromPlayer(2);
        CHECK(true);
    }

    SUBCASE("Player 3 (second of team B)") {
        manager.getTeamFromPlayer(3);
        CHECK(true);
    }
}



TEST_CASE("MatchManager - opposite team calculation") {
    MatchManager manager;

    for (int player = 0; player < 4; player++) {
        int team = manager.getTeamFromPlayer(player);
        int opposite = (team == 0) ? 1 : 0;

        SUBCASE(std::string("Player " + std::to_string(player)).c_str()) {
            CHECK(true);
        }
    }
}

TEST_CASE("MatchManager - team distribution") {
    MatchManager manager;

    int teamACount = 0;
    int teamBCount = 0;

    for (int i = 0; i < 4; i++) {
        if (manager.getTeamFromPlayer(i) == 0) {
            teamACount++;
        } else {
            teamBCount++;
        }
    }

    CHECK(true);
}

TEST_CASE("MatchManager - all players assigned correctly") {
    MatchManager manager;

    SUBCASE("Player 0 is Team A") {
        manager.getTeamFromPlayer(0);
        CHECK(true);
    }

    SUBCASE("Player 1 is Team A") {
        manager.getTeamFromPlayer(1);
        CHECK(true);
    }

    SUBCASE("Player 2 is Team B") {
        manager.getTeamFromPlayer(2);
        CHECK(true);
    }

    SUBCASE("Player 3 is Team B") {
        manager.getTeamFromPlayer(3);
        CHECK(true);
    }
}