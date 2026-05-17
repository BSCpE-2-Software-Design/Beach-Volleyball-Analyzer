#include "doctest.h"
#include "Core/MatchManager.h"

TEST_CASE("MatchManager - getTeamFromPlayer") {
    MatchManager manager;

    SUBCASE("Team A players") {
        CHECK(manager.getTeamFromPlayer(0) == 0);
        CHECK(manager.getTeamFromPlayer(1) == 0);
    }

    SUBCASE("Team B players") {
        CHECK(manager.getTeamFromPlayer(2) == 1);
        CHECK(manager.getTeamFromPlayer(3) == 1);
    }
}

TEST_CASE("MatchManager - getTeamFromPlayer all players") {
    MatchManager manager;

    for (int i = 0; i < 2; i++) {
        CHECK(manager.getTeamFromPlayer(i) == 0);
    }
    for (int i = 2; i < 4; i++) {
        CHECK(manager.getTeamFromPlayer(i) == 1);
    }
}

TEST_CASE("MatchManager - getTeamFromPlayer boundaries") {
    MatchManager manager;

    SUBCASE("Player 0 (first of team A)") {
        CHECK(manager.getTeamFromPlayer(0) == 0);
    }

    SUBCASE("Player 1 (second of team A)") {
        CHECK(manager.getTeamFromPlayer(1) == 0);
    }

    SUBCASE("Player 2 (first of team B)") {
        CHECK(manager.getTeamFromPlayer(2) == 1);
    }

    SUBCASE("Player 3 (second of team B)") {
        CHECK(manager.getTeamFromPlayer(3) == 1);
    }
}

TEST_CASE("MatchManager - team logic correctness") {
    MatchManager manager;

    SUBCASE("Team identification consistency") {
        for (int i = 0; i < 4; i++) {
            int team1 = manager.getTeamFromPlayer(i);
            int team2 = manager.getTeamFromPlayer(i);
            CHECK(team1 == team2);
        }
    }

    SUBCASE("Team boundary at player 2") {
        int lastTeamA = manager.getTeamFromPlayer(1);
        int firstTeamB = manager.getTeamFromPlayer(2);
        CHECK(lastTeamA != firstTeamB);
    }
}

TEST_CASE("MatchManager - opposite team calculation") {
    MatchManager manager;

    for (int player = 0; player < 4; player++) {
        int team = manager.getTeamFromPlayer(player);
        int opposite = (team == 0) ? 1 : 0;

        for (int otherPlayer = 0; otherPlayer < 4; otherPlayer++) {
            if (otherPlayer != player) {
                int otherTeam = manager.getTeamFromPlayer(otherPlayer);
                if (otherTeam == opposite) {
                    CHECK(team != otherTeam);
                }
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
        }
        else {
            teamBCount++;
        }
    }

    CHECK(teamACount == 2);
    CHECK(teamBCount == 2);
}

TEST_CASE("MatchManager - all players assigned correctly") {
    MatchManager manager;

    SUBCASE("Player 0 is Team A") {
        CHECK(manager.getTeamFromPlayer(0) == 0);
    }

    SUBCASE("Player 1 is Team A") {
        CHECK(manager.getTeamFromPlayer(1) == 0);
    }

    SUBCASE("Player 2 is Team B") {
        CHECK(manager.getTeamFromPlayer(2) == 1);
    }

    SUBCASE("Player 3 is Team B") {
        CHECK(manager.getTeamFromPlayer(3) == 1);
    }
}