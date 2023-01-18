#include "draw_rectangle.hpp"

DrawRectangle::DrawRectangle(const Point2D &p1, const Point2D &p2, int thickness, const Color &color) :
        Command(CommandName::DrawRectangleName),
        p1(p1),
        p2(p2),
        thickness(thickness),
        color(color) {}

void DrawRectangle::redo(Image &image) {
    auto x_min = std::min(p1.getX(), p2.getX());
    auto x_max = std::max(p1.getX(), p2.getX());
    auto y_min = std::min(p1.getY(), p2.getY());
    auto y_max = std::max(p1.getY(), p2.getY());
    saved = image.subImage({x_min - thickness, x_max + thickness,
                            y_min - thickness, y_max + thickness});
    if(saved.empty()){
        return;
    }
    image.drawRectangle(p1, p2, thickness, color);
}

void DrawRectangle::undo(Image &image) {
    auto x_min = std::min(p1.getX(), p2.getX());
    auto y_min = std::min(p1.getY(), p2.getY());
    image.drawImage({x_min - thickness, y_min - thickness}, saved);
}
