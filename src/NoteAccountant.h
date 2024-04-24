#ifndef NOTEACCOUNTANT__H
#define NOTEACCOUNTANT__H

#include <unordered_map>
#include <utility>
#include <vector>
#include "BoardNote.h"
#include "NoteSubscriber.h"
#include "Position.h"

class NoteAccountant : public NoteSubscriber 
{
public:
    NoteAccountant();
    NoteAccountant(const NoteAccountant& o) = delete;
    NoteAccountant(NoteAccountant&& o) noexcept = delete;
    NoteAccountant& operator=(const NoteAccountant& o) = delete;
    NoteAccountant& operator=(NoteAccountant&& o) noexcept = delete;
    ~NoteAccountant() noexcept = default;

    // Saves the newBoardNote with a time stamp.
    void callback(BoardNote boardNote) override;

    // Returns all the BoardNotes that have been sent so far.
    std::vector< std::pair< std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote > > getNotes() const override;
    
private:
   std::vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote>> _receivedBoardNotes; 

};

#endif
   
