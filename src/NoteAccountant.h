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

    void callback(BoardNote boardNote, Position position) override;

    std::vector< std::pair< std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote > > getNotes() const;
    
private:
    // TODO board should be const.
   std::vector<std::pair<std::chrono::time_point<std::chrono::high_resolution_clock>, BoardNote>> _receivedBoardNotes; 

};

#endif
   
