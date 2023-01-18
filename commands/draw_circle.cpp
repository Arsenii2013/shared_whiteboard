#include "draw_circle.hpp"

DrawCircle::DrawCircle(const Point2D &center, int radius, int thickness, const Color &color) :
        Command(CommandName::DrawCircleName),
        center(center),
        radius(radius),
        color(color),
        thickness(thickness){}

void DrawCircle::redo(Image &image) {
    saved = image.subImage({center.getX() - radius - thickness/2, center.getX() + radius + thickness/2 + 1,
                            center.getY() - radius - thickness/2, center.getY() + radius + thickness/2 + 1});
    if(saved.empty()){
        return;
    }
    image.drawCircle(center, radius, thickness, color);
}

void DrawCircle::undo(Image &image) {
    image.drawImage({center.getX() - radius - thickness/2, center.getY() - radius - thickness/2}, saved);
}
