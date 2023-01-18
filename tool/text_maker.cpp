#include "text_maker.hpp"

TextMaker::TextMaker(int thickness, const Color &color) : DrawingTool(ToolName::Text, thickness, color) {}

void TextMaker::processMouseEvent(MouseEvent event, int x, int y) {
    if(event == MouseEvent::LDOWN){
        left_down = {x, y};
        text.clear();
        _ready = true;
    }
}

void TextMaker::processKey(ASCIIKey key) {
    if(char(key) == '\n' || char(key) == '\r' || char(key) == '\0'){
        _final = true;
    }else{
        text.push_back(char(key));
    }
}

CommandDTO TextMaker::getCommand() {
    if(_final) {
        _ready = false;
        _final = false;
    }

    return {left_down, text, thickness, color};
}
