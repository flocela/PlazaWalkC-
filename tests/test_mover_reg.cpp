#include "catch.hpp"
#include "../src/Mover_Reg.cpp"

TEST_CASE("Moving a box on a board, adds the correct BoxNotes to the box and the correct BoardNotes to the board, in the correct order.")
{
    // BoardNotes from box 0
    BoardNote box0NoteType1{1, 0}; // box 1 is about to leave
    BoardNote box0NoteType2{2, 0}; // box 1 is about to arrive
    BoardNote box0NoteType3{3, 0}; // box 1 has left
    BoardNote box0NoteType4{4, 0}; // box 1 arrives

    Box box0{0, 10, 10};
    Board board{10, 10};

    Position pos0{5, 5};
    Position pos1{5, 6};

    BoardCallback callbackForPos0{};
    BoardCallback callbackForPos1{};
    board.registerCallback(pos0, callbackForPos0);
    board.registerCallback(pos1, callbackForPos1);

    Mover_Reg mover{box0, board};

    mover.addBox(pos0);
    mover.moveBox(pos1);

    // callbackForPos0 index 0 has a map of size 1, with box0NoteType2.
    REQUIRE( 1 == callbackForPos0.getNotes().at(0).second.size() );
    REQUIRE( box0NoteType2 == callbackForPos0.getNotes().at(0).second.at(0) );
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime = callbackForPos0.getNotes().at(0).first;

    // BoxNotes at index 0 has BoxNote{10, pos0, pos0, toArriveTime}.
   /* BoxNote toArriveAtPos0BoxNote = box0.getAllNotes().at(0);
    REQUIRE( 10 == toArriveAtPos0BoxNote.getType());
    REQUIRE( pos0 == toArriveAtPos0BoxNote.getToPosition() );
    REQUIRE( pos0 == toArriveAtPos0BoxNote.getFromPosition() );
    REQUIRE( (toArriveAtPos0BoxNote.getTimePoint() - lastTime).count() > 0 );
    lastTime = toArriveAtPos0BoxNote.getTimePoint(); 
   
    // BoxNotes at index 1 has BoxNote{11, pos0, pos0, ArrivalTime}.
    BoxNote arrivalAtPos0BoxNote = box0.getAllNotes().at(1);
    REQUIRE( 11 == arrivalAtPos0BoxNote.getType());
    REQUIRE( pos0 == arrivalAtPos0BoxNote.getToPosition() );
    REQUIRE( pos0 == arrivalAtPos0BoxNote.getFromPosition() );
    REQUIRE( (arrivalAtPos0BoxNote.getTimePoint() - lastTime).count() > 0 );
    lastTime = arrivalAtPos0BoxNote.getTimePoint(); 
    
    // callbackForPos0 index 1 has a map of size 1, with box0NoteType4.
    REQUIRE( 1 == callbackForPos0.getNotes().at(1).second.size() );
    REQUIRE( box0NoteType4 == callbackForPos0.getNotes().at(1).second.at(0) );
    REQUIRE( (callbackForPos0.getNotes().at(1).first - lastTime).count() > 0 );
    lastTime = callbackForPos0.getNotes().at(1).first;

    // callbackForPos1 index 0 has a map of size 1, with box0NoteType2.
    REQUIRE( 1 == callbackForPos1.getNotes().at(0).second.size() );
    REQUIRE( box0NoteType2 == callbackForPos1.getNotes().at(0).second.at(0) );
    REQUIRE( (callbackForPos1.getNotes().at(0).first - lastTime).count() > 0);
    lastTime = callbackForPos1.getNotes().at(0).first;
    
    // callbackForPos0 index 2 has a map of size 1, with box0NoteType1.
    REQUIRE( 1 == callbackForPos0.getNotes().at(2).second.size() );
    REQUIRE( box0NoteType1 == callbackForPos0.getNotes().at(2).second.at(0) );
    REQUIRE( (callbackForPos0.getNotes().at(2).first - lastTime).count() > 0);
    lastTime = callbackForPos0.getNotes().at(2).first;
    
    // BoxNotes at index 2 has BoxNote{10, pos1, pos0, toArriveTime}.
    BoxNote toArriveAtPos1BoxNote = box0.getAllNotes().at(2);
    REQUIRE( 10 == toArriveAtPos1BoxNote.getType());
    REQUIRE( pos1 == toArriveAtPos1BoxNote.getToPosition() );
    REQUIRE( pos0 == toArriveAtPos1BoxNote.getFromPosition() );
    REQUIRE( (toArriveAtPos1BoxNote.getTimePoint() - lastTime).count() > 0 );
    lastTime = toArriveAtPos1BoxNote.getTimePoint(); 
    
    // BoxNotes at index 3 has BoxNote{11, pos1, pos0, arrivalTime}.
    BoxNote arriveAtPos1BoxNote = box0.getAllNotes().at(3);
    REQUIRE( 11 == arriveAtPos1BoxNote.getType());
    REQUIRE( pos1 == arriveAtPos1BoxNote.getToPosition() );
    REQUIRE( pos0 == arriveAtPos1BoxNote.getFromPosition() );
    REQUIRE( (arriveAtPos1BoxNote.getTimePoint() - lastTime).count() > 0 );
    lastTime = arriveAtPos1BoxNote.getTimePoint(); 

    // callbackForPos0 index 3 has a map of size 0.
    REQUIRE( 0 == callbackForPos0.getNotes().at(3).second.size() );
    REQUIRE( (callbackForPos0.getNotes().at(3).first - lastTime).count() > 0 );
    lastTime = callbackForPos0.getNotes().at(3).first;

    // callbackForPos1 index 1 has a map of size 1, with box0NoteType4.
    REQUIRE( 1 == callbackForPos1.getNotes().at(1).second.size() );
    REQUIRE( box0NoteType4 == callbackForPos1.getNotes().at(1).second.at(0) );
    REQUIRE( (callbackForPos1.getNotes().at(1).first - lastTime).count() > 0 );
*/
}
