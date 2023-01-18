#include "draw_poly_line.hpp"

DrawPolyLine::DrawPolyLine(std::list<Point2D> _coords, int thickness, const Color &color)
        : Command(CommandName::DrawPolyLineName), coords(std::move(_coords)), color(color), thickness(thickness) {
    _x_min = coords.begin()->getX();
    _x_max = coords.begin()->getX();
    _y_min = coords.begin()->getY();
    _y_max = coords.begin()->getY();
    for(const auto& point: coords){
        _x_min = std::min(_x_min, point.getX());
        _x_max = std::max(_x_max, point.getX());
        _y_min = std::min(_y_min, point.getY());
        _y_max = std::max(_y_max, point.getY());
    }
    _x_max += thickness;
    _x_min -= thickness;
    _y_max += thickness;
    _y_min -= thickness;
}

void DrawPolyLine::redo(Image &image) {
    saved = image.subImage({_x_min, _x_max,_y_min , _y_max});
    if(saved.empty()){
        return;
    }
    image.drawPolyLine(coords, thickness, color);
}

void DrawPolyLine::undo(Image &image) {
    image.drawImage({_x_min, _y_min}, saved);
}
