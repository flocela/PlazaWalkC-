#include "catch.hpp"
#include "../src/Board.h"

using namespace std;

TEST_CASE("getHeight() and getWidth() return the Board's dimensions")
{
    Board board{20, 10};
    REQUIRE(board.getHeight() == 10);
    REQUIRE(board.getWidth() == 20); 
}

TEST_CASE("Add BoardNotes, then Spot should contain corresponding box and type.")
{   
    Board board{20, 10};
    
    // BoardNote(int type, int boxId)
    board.addNote(Position{5, 5}, BoardNote{10, 2});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{10, 2});

    board.addNote(Position{5, 5}, BoardNote{10, 4});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{10, 4});

    board.addNote(Position{5, 5}, BoardNote{10, 1});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{10, 1});

    board.addNote(Position{5, 5}, BoardNote{10, 3});
    REQUIRE(board.getNoteAt(Position{5, 5}) == BoardNote{-1, -1});
}


// TODO these addNote() tests are really already tested in test_spot.cpp. Maybe delete them.
TEST_CASE("Spot has a box with type -1. It's empty.")
{
    Board board{20, 10};

    SECTION("Adding a box with any type other than 2, results in an exception.")
    {
        // BoardNote{boxId, type}
        REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{10, -1}));
        REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{10, 3}));
        REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{10, 4}));
    }
}

TEST_CASE("Spot has a box with type 1.")
{
    Board board{20, 10};
    board.addNote(Position{5, 5}, BoardNote{10, 2});
    board.addNote(Position{5, 5}, BoardNote{10, 4});
    board.addNote(Position{5, 5}, BoardNote{10, 1});

    SECTION("Adding a box with the same boxId")
    {
        SECTION(" and with type 3, results in an empty spot")
        {
            // BoardNote{boxId, type}
            REQUIRE(board.addNote(Position{5, 5}, BoardNote{10, 3}));
            REQUIRE(BoardNote{-1, -1} == board.getNoteAt(Position{5, 5}));
        }
        SECTION(" and with any types other than 3 results in an exception.")
        {
            // BoardNote{boxId, type}
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{10, 1}));
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{10, 2}));
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{10, 4}));
        }
    }
    SECTION("Adding a box with a different boxId")
    {
        SECTION(" and with type 2, results in false.")
        {
            // BoardNote{boxId, type}
            // BoardNote{boxId, type}
            REQUIRE(false == board.addNote(Position{5, 5}, BoardNote{9, 2}));
            REQUIRE(BoardNote{10, 1} == board.getNoteAt(Position{5, 5}));
        }
        SECTION(" and with any type other than 2, results in an exception.")
        {
            // BoardNote{boxId, type}
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{9, 1}));
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{9, 3}));
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{9, 4}));
        }
    }
}

TEST_CASE("Spot has a box with type 2.")
{
    Board board{20, 10};
    board.addNote(Position{5, 5}, BoardNote{10, 2});

    SECTION("Adding a box with the same boxId")
    {
        SECTION(" and with type 4, results in type changing to 4")
        {
            // BoardNote{boxId, type}
            REQUIRE(board.addNote(Position{5, 5}, BoardNote{10, 4}));
            REQUIRE(BoardNote{10, 4} == board.getNoteAt(Position{5, 5}));
        }
        SECTION(" and with any types other than 4 results in an exception.")
        {
            // BoardNote{boxId, type}
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{10, 1}));
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{10, 2}));
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{10, 3}));
        }
    }
    SECTION("Adding a box with a different boxId")
    {
        SECTION(" and with type 2, results in false.")
        {
            // BoardNote{boxId, type}
            // BoardNote{boxId, type}
            REQUIRE(false == board.addNote(Position{5, 5}, BoardNote{9, 2}));
            REQUIRE(BoardNote{10, 2} == board.getNoteAt(Position{5, 5}));
        }
        SECTION(" and with any type other than 2, results in an exception.")
        {
            // BoardNote{boxId, type}
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{9, 1}));
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{9, 3}));
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{9, 4}));
        }
    }
}

TEST_CASE("Spot has a box with type 4.")
{
    Board board{20, 10};
    board.addNote(Position{5, 5}, BoardNote{10, 2});
    board.addNote(Position{5, 5}, BoardNote{10, 4});

    SECTION("Adding a box with the same boxId")
    {
        SECTION(" and with type 1, results in type changing to 1")
        {
            // BoardNote{boxId, type}
            REQUIRE(board.addNote(Position{5, 5}, BoardNote{10, 1}));
            REQUIRE(BoardNote{10, 1} == board.getNoteAt(Position{5, 5}));
        }
        SECTION(" and with any types other than 1 results in an exception.")
        {
            // BoardNote{boxId, type}
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{10, 2}));
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{10, 3}));
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{10, 4}));
        }
    }
    SECTION("Adding a box with a different boxId")
    {
        SECTION(" and with type 2, results in false.")
        {
            // BoardNote{boxId, type}
            // BoardNote{boxId, type}
            REQUIRE(false == board.addNote(Position{5, 5}, BoardNote{9, 2}));
            REQUIRE(BoardNote{10, 4} == board.getNoteAt(Position{5, 5}));
        }
        SECTION(" and with any type other than 2, results in an exception.")
        {
            // BoardNote{boxId, type}
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{9, 1}));
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{9, 3}));
            REQUIRE_THROWS(board.addNote(Position{5, 5}, BoardNote{9, 4}));
        }
    }
}


