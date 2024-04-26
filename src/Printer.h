#ifndef PRINTER__H
#define PRINTER__H

#include <shared_mutex>
#include <unordered_map>

#include "Color.h"
#include "RecorderListener.h"
#include "Recorder.h"
#include "SDL.h"

class Printer : public RecorderListener {


    public:
    Printer(SDL_Renderer* renderer);
    Printer() = delete;
    Printer(const Printer& o) = delete;
    Printer(Printer&& o) noexcept = delete;
    Printer& operator=(const Printer& printer) = delete;
    Printer& operator=(Printer&& o) noexcept = delete;
    ~Printer() noexcept = default;

    // These are rectangles where Boxes start and end at. They are printed as dark grey rectangles on the board.
    void addInOutBoundRectangle(Position topLeft, Position bottomRight);
    void addInOutBoundRectangles(std::vector<std::pair<Position, Position>> rectangles);

    //  
    void setGroupColors(std::unordered_map<int, Color> colorPerGroupNumber);

    // Prints these Boxes on the Board.
    void receiveAllDropsAllBoxes(std::unordered_set<Drop> drops, std::unordered_map<int, BoxInfo> boxes) override;


    private:
    SDL_Renderer* _renderer;
    std::unordered_map<int, Color> _colorPerGroupNumber{};
    std::unordered_map<int, int> _numOfShadesPerGroupNumber{}; 
    std::vector<std::pair<Position, Position>> _endRectangles{};

    void print(std::unordered_set<Drop> drops, std::unordered_map<int, BoxInfo> boxes);
    
};

#endif
