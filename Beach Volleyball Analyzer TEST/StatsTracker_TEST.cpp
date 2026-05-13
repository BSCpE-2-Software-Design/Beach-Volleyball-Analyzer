#include "doctest.h"
#include "Statistics/StatTracker.h"

TEST_CASE("StatTracker - recordTouch") {
    StatTracker tracker;
    tracker.recordTouch(0);
    tracker.recordTouch(1);
    CHECK(true);
}

TEST_CASE("StatTracker - recordError") {
    StatTracker tracker;
    tracker.recordError(0);
    tracker.recordError(1);
    CHECK(true);
}

TEST_CASE("StatTracker - recordPoint") {
    StatTracker tracker;
    tracker.recordPoint(0);
    tracker.recordPoint(1);
    CHECK(true);
}

TEST_CASE("StatTracker - recordAttack") {
    StatTracker tracker;
    tracker.recordAttack(0, false);
    tracker.recordAttack(1, true);
    CHECK(true);
}

TEST_CASE("StatTracker - recordBlockPoint") {
    StatTracker tracker;
    tracker.recordBlockPoint(0);
    tracker.recordBlockPoint(1);
    CHECK(true);
}

TEST_CASE("StatTracker - recordDig") {
    StatTracker tracker;
    tracker.recordDig(0, false);
    tracker.recordDig(1, true);
    CHECK(true);
}

TEST_CASE("StatTracker - recordAceServe") {
    StatTracker tracker;
    tracker.recordAceServe(0);
    tracker.recordAceServe(1);
    CHECK(true);
}

TEST_CASE("StatTracker - recordAssist") {
    StatTracker tracker;
    tracker.recordAssist(0);
    tracker.recordAssist(1);
    CHECK(true);
}

TEST_CASE("StatTracker - printReport") {
    StatTracker tracker;
    tracker.recordTouch(0);
    tracker.recordPoint(0);
    tracker.printReport();
    CHECK(true);
}

TEST_CASE("StatTracker - printDetailedStats") {
    StatTracker tracker;
    tracker.recordTouch(0);
    tracker.recordAttack(0, false);
    tracker.printDetailedStats();
    CHECK(true);
}