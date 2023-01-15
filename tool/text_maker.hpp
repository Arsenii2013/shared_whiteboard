#ifndef SHARED_WHITEBOARD_TEXT_MAKER_HPP
#define SHARED_WHITEBOARD_TEXT_MAKER_HPP
#include "drawing_tool.hpp"
#include "../commands/draw_text.hpp"
#include "tool_name.hpp"

class TextMaker final : public DrawingTool{
    Point2D left_down;
    std::string text;

    bool _final{false};
    bool _ready{false};
public:
    TextMaker(int thickness, const Color &color) : DrawingTool(ToolName::Text, thickness, color) {}

    void processMouseEvent(MouseEvent event, int x, int y) override {
        if(event == MouseEvent::LDOWN){
            left_down = {x, y};
            text.clear();
            _ready = true;
        }
    };

    void processKey(ASCIIKey key) override {
        if(char(key) == '\n' || char(key) == '\r' || char(key) == '\0'){
            _final = true;
        }else{
            text.push_back(char(key));
        }
    };

    bool ready() override {return _ready;};
    bool final() override {return _final;};

    std::unique_ptr<Command> getCommand() override {
        if(_final) {
            _ready = false;
            _final = false;
        }

        return std::make_unique<DrawText>(left_down, text, thickness, color);
    };
};
#endif //SHARED_WHITEBOARD_TEXT_MAKER_HPP
