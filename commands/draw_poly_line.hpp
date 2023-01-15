#ifndef SHARED_WHITEBOARD_DRAW_POLY_LINE_HPP
#define SHARED_WHITEBOARD_DRAW_POLY_LINE_HPP
#include <utility>

#include "command.hpp"
#include "command_name.hpp"
#include "../utilities.hpp"

class DrawPolyLine final: public Command{
    std::list<Point2D> coords;
    Color color;
    int thickness;
    Image saved{};
    int _x_min, _x_max;
    int _y_min, _y_max;
public:
    DrawPolyLine(std::list<Point2D> _coords, int thickness, const Color &color)
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

    void redo(Image & image) override {
        saved = image.subImage({_x_min, _x_max,_y_min , _y_max});
        image.drawPolyLine(coords, thickness, color);
    };

    void undo(Image & image) override {
        image.drawImage({_x_min, _y_min}, saved);
    };
};
#endif //SHARED_WHITEBOARD_DRAW_POLY_LINE_HPP
