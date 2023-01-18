#include "rectangle_maker.hpp"

RectangleMaker::RectangleMaker(int thickness, const Color &color) : DrawingTool(ToolName::Rectangle, thickness, color) {}

void RectangleMaker::processMouseEvent(MouseEvent event, int x, int y) {
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

CommandDTO RectangleMaker::getCommand() {
    if(_final) {
        _ready = false;
        _final = false;
    }
    return {Point2D{x1, y1}, Point2D{x2, y2}, thickness, color};
}
