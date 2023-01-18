#ifndef SHARED_WHITEBOARD_DRAW_IMAGE_HPP
#define SHARED_WHITEBOARD_DRAW_IMAGE_HPP
#include "command.hpp"
#include "command_name.hpp"
#include "../utilities.hpp"

class DrawImage final: public Command{
    Point2D up_left;
    Image to_draw{};
    Image mask{};
    Image saved{};
public:
    DrawImage(Point2D up_left, Image toDraw);
    DrawImage(Point2D up_left, Image toDraw, Image mask);

    void redo(Image & image) override;;

    void undo(Image & image) override;;
};
#endif //SHARED_WHITEBOARD_DRAW_IMAGE_HPP
