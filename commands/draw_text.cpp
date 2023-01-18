#include "draw_text.hpp"

DrawText::DrawText(const Point2D &leftDown, std::string text, int thickness, const Color &color)
        : Command(CommandName::DrawTextName), left_down(leftDown), text(std::move(text)), thickness(thickness), color(color) {}

void DrawText::redo(Image &image) {
    saved = image.subImage({left_down.getX(), left_down.getX() + Image::textWidthByHeight(text, thickness) + 1,
                            left_down.getY() - thickness, left_down.getY() + thickness});
    if(saved.empty()){
        return;
    }
    image.drawText(text, left_down, thickness, color);
}

void DrawText::undo(Image &image) {
    image.drawImage({left_down.getX(), left_down.getY() - thickness}, saved);
}
