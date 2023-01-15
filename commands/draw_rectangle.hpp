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
    DrawRectangle(const Point2D &p1, const Point2D &p2, int thickness, const Color &color) :
                                            Command(CommandName::DrawRectangleName),
                                            p1(p1),
                                            p2(p2),
                                            thickness(thickness),
                                            color(color) {}

    void redo(Image & image) override {
        auto x_min = std::min(p1.getX(), p2.getX());
        auto x_max = std::max(p1.getX(), p2.getX());
        auto y_min = std::min(p1.getY(), p2.getY());
        auto y_max = std::max(p1.getY(), p2.getY());
        saved = image.subImage({x_min - thickness, x_max + thickness,
                                     y_min - thickness, y_max + thickness});
        image.drawRectangle(p1, p2, thickness, color);
    };

    void undo(Image & image) override {
        auto x_min = std::min(p1.getX(), p2.getX());
        auto y_min = std::min(p1.getY(), p2.getY());
        image.drawImage({x_min - thickness, y_min - thickness}, saved);
    };
};
#endif //SHARED_WHITEBOARD_DRAW_RECTANGLE_HPP
