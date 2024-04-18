#ifndef PRINTER__H
#define PRINTER__H

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

    void addInOutBoundRectangle(Position topLeft, Position bottomRight);
    void addInOutBoundRectangles(std::vector<std::pair<Position, Position>> rectangles);

    void receiveAllDrops(std::unordered_map<SpotType, std::unordered_set<Drop>> setOfDropsPerType, std::unordered_map<int, BoxInfo> boxes) override;

private:
    SDL_Renderer* _renderer;
    void print(std::unordered_map<SpotType, std::unordered_set<Drop>> dropsPerType, std::unordered_map<int, BoxInfo> boxes);
    std::vector<std::pair<Position, Position>> _endRectangles{};
};

#endif
