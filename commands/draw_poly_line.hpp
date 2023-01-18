#ifndef SHARED_WHITEBOARD_DRAW_POLY_LINE_HPP
#define SHARED_WHITEBOARD_DRAW_POLY_LINE_HPP
#include "command.hpp"
#include "command_name.hpp"
#include "../utilities.hpp"

class DrawPolyLine final: public Command{
    std::list<Point2D> coords;
    Color color;
    int thickness;
    Image saved{};
    int _x_min, _x_max;
    int _y_min, _y_max;
public:
    DrawPolyLine(std::list<Point2D> _coords, int thickness, const Color &color);

    void redo(Image & image) override;;

    void undo(Image & image) override;;
};
#endif //SHARED_WHITEBOARD_DRAW_POLY_LINE_HPP
