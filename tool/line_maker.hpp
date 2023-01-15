#ifndef SHARED_WHITEBOARD_LINE_MAKER_HPP
#define SHARED_WHITEBOARD_LINE_MAKER_HPP
#include "drawing_tool.hpp"
#include "../commands/draw_poly_line.hpp"
#include "tool_name.hpp"

class LineMaker final : public DrawingTool{
    std::list<Point2D> coords;

    bool _ready{false};
    bool _final{false};
public:
    LineMaker(int thickness, const Color &color) : DrawingTool(ToolName::PolyLine, thickness, color) {}

    void processMouseEvent(MouseEvent event, int x, int y) override {
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
    };
    void processKey(ASCIIKey key) override {};

    bool ready() override {return _ready;};
    bool final() override {return _final;};

    std::unique_ptr<Command> getCommand() override {
        auto res = std::make_unique<DrawPolyLine>(coords, thickness, color);
        if(_final) {
            _ready = false;
            _final = false;
            coords.clear();
        }
        return std::move(res);
    };
};
#endif //SHARED_WHITEBOARD_LINE_MAKER_HPP
