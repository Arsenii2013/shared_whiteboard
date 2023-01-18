#ifndef SHARED_WHITEBOARD_COLOR_CHANGER_HPP
#define SHARED_WHITEBOARD_COLOR_CHANGER_HPP
#include "tool_tool.hpp"
#include "tool_name.hpp"
#include "../tool_command/change_color.hpp"

class ColorChanger : public ToolTool{
    int x_min{}, x_max{};
    int y_min{}, y_max{};
    Color color;
public:
    explicit ColorChanger(Rectangle D);

    void processMouseEvent(MouseEvent event, int x, int y) override;;

    std::unique_ptr<ToolCommand> getCommand() override;;
};
#endif //SHARED_WHITEBOARD_COLOR_CHANGER_HPP
