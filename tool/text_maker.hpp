#ifndef SHARED_WHITEBOARD_TEXT_MAKER_HPP
#define SHARED_WHITEBOARD_TEXT_MAKER_HPP
#include "drawing_tool.hpp"
#include "tool_name.hpp"

class TextMaker final : public DrawingTool{
    Point2D left_down;
    std::string text;

    bool _final{false};
    bool _ready{false};
public:
    TextMaker(int thickness, const Color &color);

    void processMouseEvent(MouseEvent event, int x, int y) override;;

    void processKey(ASCIIKey key) override;;

    bool ready() override {return _ready;};
    bool final() override {return _final;};

    CommandDTO getCommand() override;;
};
#endif //SHARED_WHITEBOARD_TEXT_MAKER_HPP
