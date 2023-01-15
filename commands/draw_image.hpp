#ifndef SHARED_WHITEBOARD_DRAW_IMAGE_HPP
#define SHARED_WHITEBOARD_DRAW_IMAGE_HPP
#include <utility>

#include "command.hpp"
#include "command_name.hpp"
#include "../utilities.hpp"

class DrawImage final: public Command{
    Point2D up_left;
    Image to_draw{};
    Image mask{};
    Image saved{};
public:
    DrawImage(Point2D up_left, Image toDraw) : Command(CommandName::DrawImageName), up_left(up_left), to_draw(std::move(toDraw)) {}
    DrawImage(Point2D up_left, Image toDraw, Image mask) : Command(CommandName::DrawImageName), up_left(up_left), to_draw(std::move(toDraw)), mask(std::move(mask)) {}

    void redo(Image & image) override {
        saved = image.subImage({up_left.getX(), up_left.getX() + to_draw.getStorage().cols,
                                    up_left.getY(), up_left.getY() + to_draw.getStorage().rows});
        if(mask.getStorage().empty()) {
            image.drawImage(up_left, to_draw);
        }else{
            image.drawImage(up_left, to_draw, mask);
        }
    };

    void undo(Image & image) override {
        image.drawImage(up_left, saved);
    };
};
#endif //SHARED_WHITEBOARD_DRAW_IMAGE_HPP
