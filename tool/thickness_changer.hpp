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
    ThicknessChanger(int x_min, int x_max, int max_thickness) :
                            ToolTool(ToolName::Thickness),
                            x_min(x_min),
                            x_max(x_max),
                            max_thickness(max_thickness) {};

    void processMouseEvent(MouseEvent event, int x, int y) override {
        if (event == MouseEvent::LDOWN) {
            if (x_min < x && x < x_max) {
                thickness = (x - x_min) * max_thickness / (x_max - x_min);
            }
        }
    };

    std::unique_ptr<ToolCommand> getCommand() override {
        //_ready = false;
        return std::make_unique<ChangeThickness>(thickness);
    };
};
#endif //SHARED_WHITEBOARD_THICKNESS_CHANGER_HPP
