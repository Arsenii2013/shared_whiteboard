#ifndef SHARED_WHITEBOARD_CHANGE_COLOR_HPP
#define SHARED_WHITEBOARD_CHANGE_COLOR_HPP
#include "tool_command.hpp"

class ChangeColor : public ToolCommand{
    Color color;
public:
    explicit ChangeColor(Color color) : color(color){};

    void execute(DrawingTool & tool) override;;
};
#endif //SHARED_WHITEBOARD_CHANGE_COLOR_HPP
