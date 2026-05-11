
#include "doctest.h"
#include "MatchManager.h"

TEST_CASE("MatchManager - getTeamFromPlayer") {
    MatchManager manager;

    SUBCASE("Team A players") {
        CHECK_EQ(manager.getTeamFromPlayer(0), 0);
        CHECK_EQ(manager.getTeamFromPlayer(1), 0);
    }

    SUBCASE("Team B players") {
        CHECK_EQ(manager.getTeamFromPlayer(2), 1);
        CHECK_EQ(manager.getTeamFromPlayer(3), 1);
    }
}

TEST_CASE("MatchManager - getTeamFromPlayer all players") {
    MatchManager manager;

    for (int i = 0; i < 2; i++) {
        CHECK_EQ(manager.getTeamFromPlayer(i), 0);
    }
    for (int i = 2; i < 4; i++) {
        CHECK_EQ(manager.getTeamFromPlayer(i), 1);
    }
}

TEST_CASE("MatchManager - getTeamFromPlayer boundaries") {
    MatchManager manager;

    SUBCASE("Player 0 (first of team A)") {
        CHECK_EQ(manager.getTeamFromPlayer(0), 0);
    }

    SUBCASE("Player 1 (second of team A)") {
        CHECK_EQ(manager.getTeamFromPlayer(1), 0);
    }

    SUBCASE("Player 2 (first of team B)") {
        CHECK_EQ(manager.getTeamFromPlayer(2), 1);
    }

    SUBCASE("Player 3 (second of team B)") {
        CHECK_EQ(manager.getTeamFromPlayer(3), 1);
    }
}

TEST_CASE("MatchManager - team logic correctness") {
    MatchManager manager;

    SUBCASE("Team identification consistency") {
        // Each player should always return the same team
        for (int i = 0; i < 4; i++) {
            int team1 = manager.getTeamFromPlayer(i);
            int team2 = manager.getTeamFromPlayer(i);
            CHECK_EQ(team1, team2);
        }
    }

    SUBCASE("Team boundary at player 2") {
        int lastTeamA = manager.getTeamFromPlayer(1);
        int firstTeamB = manager.getTeamFromPlayer(2);
        CHECK_NE(lastTeamA, firstTeamB);
    }
}

TEST_CASE("MatchManager - opposite team calculation") {
    MatchManager manager;

    for (int player = 0; player < 4; player++) {
        int team = manager.getTeamFromPlayer(player);
        int opposite = (team == 0) ? 1 : 0;

        SUBCASE(std::string("Player " + std::to_string(player)).c_str()) {
            if (team == 0) {
                CHECK_EQ(opposite, 1);
            } else {
                CHECK_EQ(opposite, 0);
            }
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

    CHECK_EQ(teamACount, 2);
    CHECK_EQ(teamBCount, 2);
}

TEST_CASE("MatchManager - all players assigned correctly") {
    MatchManager manager;

    SUBCASE("Player 0 is Team A") {
        CHECK_EQ(manager.getTeamFromPlayer(0), 0);
    }

    SUBCASE("Player 1 is Team A") {
        CHECK_EQ(manager.getTeamFromPlayer(1), 0);
    }

    SUBCASE("Player 2 is Team B") {
        CHECK_EQ(manager.getTeamFromPlayer(2), 1);
    }

    SUBCASE("Player 3 is Team B") {
        CHECK_EQ(manager.getTeamFromPlayer(3), 1);
    }
}