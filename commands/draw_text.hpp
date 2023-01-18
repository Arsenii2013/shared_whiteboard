#ifndef SHARED_WHITEBOARD_DRAW_TEXT_HPP
#define SHARED_WHITEBOARD_DRAW_TEXT_HPP
#include "command.hpp"
#include "command_name.hpp"
#include "../utilities.hpp"

class DrawText final: public Command{
    Point2D left_down;
    std::string text;
    int thickness;
    Color color;
    Image saved{};
public:
    DrawText(const Point2D &leftDown, std::string text, int thickness, const Color &color);

    void redo(Image & image) override;;

    void undo(Image & image) override;;
};

#endif //SHARED_WHITEBOARD_DRAW_TEXT_HPP
