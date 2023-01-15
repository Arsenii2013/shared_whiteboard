#ifndef SHARED_WHITEBOARD_DRAW_TEXT_HPP
#define SHARED_WHITEBOARD_DRAW_TEXT_HPP
#include <utility>

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
    DrawText(const Point2D &leftDown, std::string text, int thickness, const Color &color)
            : Command(CommandName::DrawTextName), left_down(leftDown), text(std::move(text)), thickness(thickness), color(color) {}

    void redo(Image & image) override {
        saved = image.subImage({left_down.getX(), left_down.getX() + Image::textWidthByHeight(text, thickness) + 1,
                                     left_down.getY() - thickness, left_down.getY() + thickness});

        image.drawText(text, left_down, thickness, color);
    };

    void undo(Image & image) override {
        image.drawImage({left_down.getX(), left_down.getY() - thickness}, saved);
    };
};

#endif //SHARED_WHITEBOARD_DRAW_TEXT_HPP
