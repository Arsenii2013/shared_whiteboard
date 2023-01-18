#ifndef SHARED_WHITEBOARD_DRAW_RECTANGLE_HPP
#define SHARED_WHITEBOARD_DRAW_RECTANGLE_HPP
#include "command.hpp"
#include "command_name.hpp"
#include "../utilities.hpp"

class DrawRectangle final: public Command{
    Point2D p1;
    Point2D p2;
    int thickness;
    Color color;
    Image saved{};
public:
    DrawRectangle(const Point2D &p1, const Point2D &p2, int thickness, const Color &color);

    void redo(Image & image) override;;

    void undo(Image & image) override;;
};
#endif //SHARED_WHITEBOARD_DRAW_RECTANGLE_HPP
