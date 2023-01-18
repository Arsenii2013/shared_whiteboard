#include "thickness_changer.hpp"

ThicknessChanger::ThicknessChanger(int x_min, int x_max, int max_thickness) :
        ToolTool(ToolName::Thickness),
        x_min(x_min),
        x_max(x_max),
        max_thickness(max_thickness) {}

void ThicknessChanger::processMouseEvent(MouseEvent event, int x, int y) {
    if (event == MouseEvent::LDOWN) {
        if (x_min < x && x < x_max) {
            thickness = (x - x_min) * max_thickness / (x_max - x_min);
        }
    }
}

std::unique_ptr<ToolCommand> ThicknessChanger::getCommand() {
    //_ready = false;
    return std::make_unique<ChangeThickness>(thickness);
}
