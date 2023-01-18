#ifndef SHARED_WHITEBOARD_RECTANGLE_MAKER_HPP
#define SHARED_WHITEBOARD_RECTANGLE_MAKER_HPP
#include "drawing_tool.hpp"
#include "tool_name.hpp"


class RectangleMaker final : public DrawingTool{
    int x1{}, x2{};
    int y1{}, y2{};

    bool _ready{false};
    bool _final{false};
public:
    RectangleMaker(int thickness, const Color &color);

    void processMouseEvent(MouseEvent event, int x, int y) override;;
    void processKey(ASCIIKey key) override {};

    bool ready() override {return _ready;};
    bool final() override {return _final;};

    CommandDTO getCommand() override;;
};
#endif //SHARED_WHITEBOARD_RECTANGLE_MAKER_HPP
