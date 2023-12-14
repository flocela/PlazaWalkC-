#ifndef BOARDNOTE__H
#define BOARDNOTE__H

class BoardNote
{

public:
    BoardNote(int type, int boxId);
    BoardNote() = delete;
    BoardNote(const BoardNote& o) = default;
    BoardNote(BoardNote&& o) noexcept = default;
    BoardNote& operator=(const BoardNote& o) = delete;
    BoardNote& operator=(BoardNote&& o) noexcept = delete;
    ~BoardNote() = default;

    int getType() const;
    int getBoxId() const;

private:
    const int _type;
    const int _boxId;

};

#endif
