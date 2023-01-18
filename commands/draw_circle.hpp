#ifndef SHARED_WHITEBOARD_DRAW_CIRCLE_HPP
#define SHARED_WHITEBOARD_DRAW_CIRCLE_HPP
#include "command.hpp"
#include "command_name.hpp"
#include "../utilities.hpp"

class DrawCircle final: public Command{
    Point2D center;
    int radius;
    Color color;
    int thickness;
    Image saved{};
public:
    DrawCircle(const Point2D &center, int radius, int thickness, const Color &color);

    void redo(Image & image) override;;

    void undo(Image & image) override;;
};

#endif //SHARED_WHITEBOARD_DRAW_CIRCLE_HPP
