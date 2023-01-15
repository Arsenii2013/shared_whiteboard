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
    DrawCircle(const Point2D &center, int radius, int thickness, const Color &color) :
                                                Command(CommandName::DrawCircleName),
                                                 center(center),
                                                 radius(radius),
                                                 color(color),
                                                 thickness(thickness){}

    void redo(Image & image) override {
        saved = image.subImage({center.getX() - radius - thickness, center.getX() + radius + thickness,
                                     center.getY() - radius - thickness, center.getY() + radius + thickness});
        image.drawCircle(center, radius, thickness, color);
    };

    void undo(Image & image) override {
        image.drawImage({center.getX() - radius - thickness, center.getY() - radius - thickness}, saved);
    };
};

#endif //SHARED_WHITEBOARD_DRAW_CIRCLE_HPP
