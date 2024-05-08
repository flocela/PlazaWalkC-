#ifndef PRINTER__H
#define PRINTER__H

#include <unordered_map>

#include "Color.h"
#include "RecorderListener.h"
#include "Rectangle.h"
#include "SDL.h"


/*
Uses SDL_Renderer to render Boxes and in-and-out bound rectangles on screen. In-and-out bound rectangles are the rectangles where the Boxes start and end at.
*/
class Printer : public RecorderListener {


    public:
    Printer(SDL_Renderer* renderer);
    Printer() = delete;
    Printer(const Printer& o) = delete;
    Printer(Printer&& o) noexcept = delete;
    Printer& operator=(const Printer& printer) = delete;
    Printer& operator=(Printer&& o) noexcept = delete;
    ~Printer() noexcept = default;

    /*
    These are rectangles where Boxes start and end at. They are printed as dark grey rectangles on the board.
    */
    void addInOutBoundRectangle(Rectangle rectangle);
    void addInOutBoundRectangles(std::vector<Rectangle> rectangles);

    /*
    Set the Color for each group of Boxes, per the Boxes' group number.
    */  
    void setGroupColors(std::unordered_map<int, Color> colorPerGroupNumber);

    /*
    Prints Boxes and the in-and-out bound rectangles on the Board.
    */
    void receiveAllDropsAllBoxes(std::unordered_set<Drop> drops, std::unordered_map<int, BoxInfo> boxes) override;


    private:
    SDL_Renderer* _renderer;
    std::unordered_map<int, Color> _colorPerGroupNumber{};
    std::unordered_map<int, int> _numOfShadesPerGroupNumber{}; 
    std::vector<Rectangle> _endRectangles{};

    void print(std::unordered_set<Drop>& drops, std::unordered_map<int, BoxInfo>& boxes);
    
};

#endif
