#ifndef SHARED_WHITEBOARD_RECTANGLE_MAKER_HPP
#define SHARED_WHITEBOARD_RECTANGLE_MAKER_HPP
#include "drawing_tool.hpp"
#include "../commands/draw_rectangle.hpp"
#include "tool_name.hpp"

class RectangleMaker final : public DrawingTool{
    int x1{}, x2{};
    int y1{}, y2{};

    bool _ready{false};
    bool _final{false};
public:
    RectangleMaker(int thickness, const Color &color) : DrawingTool(ToolName::Rectangle, thickness, color) {}

    void processMouseEvent(MouseEvent event, int x, int y) override {
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
    };
    void processKey(ASCIIKey key) override {};

    bool ready() override {return _ready;};
    bool final() override {return _final;};

    std::unique_ptr<Command> getCommand() override {
        if(_final) {
            _ready = false;
            _final = false;
        }
        return std::make_unique<DrawRectangle>(Point2D{x1, y1}, Point2D{x2, y2}, thickness, color);
    };
};
#endif //SHARED_WHITEBOARD_RECTANGLE_MAKER_HPP
