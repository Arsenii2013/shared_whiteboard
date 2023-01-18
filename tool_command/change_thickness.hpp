#ifndef SHARED_WHITEBOARD_CHANGE_THICKNESS_HPP
#define SHARED_WHITEBOARD_CHANGE_THICKNESS_HPP
#include "tool_command.hpp"

class ChangeThickness : public ToolCommand{
    int thickness{};
public:
    explicit ChangeThickness(int thickness) : thickness(thickness){};
    void execute(DrawingTool & tool) override;;
};

#endif //SHARED_WHITEBOARD_CHANGE_THICKNESS_HPP
