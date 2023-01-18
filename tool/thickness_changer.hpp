#ifndef SHARED_WHITEBOARD_THICKNESS_CHANGER_HPP
#define SHARED_WHITEBOARD_THICKNESS_CHANGER_HPP
#include "tool_tool.hpp"
#include "tool_name.hpp"
#include "../tool_command/change_thickness.hpp"

class ThicknessChanger : public ToolTool{
    int x_min{}, x_max{};
    int thickness{};
    int max_thickness{};
public:
    ThicknessChanger(int x_min, int x_max, int max_thickness);

    void processMouseEvent(MouseEvent event, int x, int y) override;;

    std::unique_ptr<ToolCommand> getCommand() override;;
};
#endif //SHARED_WHITEBOARD_THICKNESS_CHANGER_HPP
