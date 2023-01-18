#include "line_maker.hpp"

LineMaker::LineMaker(int thickness, const Color &color) : DrawingTool(ToolName::PolyLine, thickness, color) {}

void LineMaker::processMouseEvent(MouseEvent event, int x, int y) {
    if(event == MouseEvent::LDOWN){
        _ready = true;
        coords.emplace_back(x, y);
    }else if(event == MouseEvent::LUP){
        _final = true;
        coords.emplace_back(x, y);
    }else if(event == MouseEvent::MOVE){
        if(_ready){
            coords.emplace_back(x, y);
        }
    }
}

CommandDTO LineMaker::getCommand() {
    CommandDTO res{coords, thickness, color};
    if(_final) {
        _ready = false;
        _final = false;
        coords.clear();
    }
    return res; // NRVO!
}
