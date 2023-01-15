#ifndef SHARED_WHITEBOARD_CIRCLE_MAKER_HPP
#define SHARED_WHITEBOARD_CIRCLE_MAKER_HPP
#include "drawing_tool.hpp"
#include "../commands/draw_circle.hpp"
#include "tool_name.hpp"

class CircleMaker final : public DrawingTool{
    int x1{}, x2{};
    int y1{}, y2{};

    bool _final{false};
    bool _ready{false};
public:
    CircleMaker(int thickness, const Color &color) : DrawingTool(ToolName::Circle, thickness, color) {}

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
        int radius = std::max(std::abs((x1 - x2)/2), std::abs((y1 - y2)/2));
        return std::make_unique<DrawCircle>(Point2D{(x1+x2)/2, (y1 + y2)/2}, radius, thickness, color);
    };
};
#endif //SHARED_WHITEBOARD_CIRCLE_MAKER_HPP
