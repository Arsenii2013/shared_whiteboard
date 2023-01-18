#include "draw_image.hpp"

DrawImage::DrawImage(Point2D up_left, Image toDraw) : Command(CommandName::DrawImageName),
                                                      up_left(up_left),
                                                      to_draw(std::move(toDraw)) {}

DrawImage::DrawImage(Point2D up_left, Image toDraw, Image mask) : Command(CommandName::DrawImageName),
                                                                  up_left(up_left),
                                                                  to_draw(std::move(toDraw)),
                                                                  mask(std::move(mask)) {}

void DrawImage::redo(Image &image) {
    saved = image.subImage({up_left.getX(), up_left.getX() + to_draw.getStorage().cols,
                            up_left.getY(), up_left.getY() + to_draw.getStorage().rows});
    if(saved.empty()){
        return;
    }
    if(mask.getStorage().empty()) {
        image.drawImage(up_left, to_draw);
    }else{
        image.drawImage(up_left, to_draw, mask);
    }
}

void DrawImage::undo(Image &image) {
    image.drawImage(up_left, saved);
}
