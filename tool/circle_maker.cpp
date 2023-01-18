#include "circle_maker.hpp"

void CircleMaker::processMouseEvent(MouseEvent event, int x, int y) {
    if(event == MouseEvent::LDOWN){
        x1 = x;
        y1 = y;
        _ready = true;
    }else if(event == MouseEvent::LUP){
        x2 = x;
        y2 = y;
        _final = true;
    }else if(event == MouseEvent::MOVE){
        x2 = x;
        y2 = y;
    }
}

CommandDTO CircleMaker::getCommand() {
    if(_final) {
        _ready = false;
        _final = false;
    }
    int radius = std::max(std::abs((x1 - x2)/2), std::abs((y1 - y2)/2));
    return {Point2D{(x1+x2)/2, (y1 + y2)/2}, radius, thickness, color};
}
