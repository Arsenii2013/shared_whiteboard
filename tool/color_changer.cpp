#include "color_changer.hpp"

ColorChanger::ColorChanger(Rectangle D) :
        ToolTool(ToolName::Thickness),
        x_min(D.getXL()),
        x_max(D.getXR()),
        y_min(D.getYU()),
        y_max(D.getYD()) {}

void ColorChanger::processMouseEvent(MouseEvent event, int x, int y) {
    if (event == MouseEvent::LDOWN) {
        if (x_min < x && x < x_max) {
            if(y_min < y && y < y_min + (y_max - y_min) / 3){
                color.setR((x - x_min) * 256 / (x_max - x_min));
            }else if(y_min + (y_max - y_min) / 3 < y && y < y_min + (y_max - y_min) * 2 / 3){
                color.setG((x - x_min) * 256 / (x_max - x_min));
            }else if(y_min + (y_max - y_min) * 2 / 3 < y && y < y_max ){
                color.setB((x - x_min) * 256 / (x_max - x_min));
            }
        }
    }
}

std::unique_ptr<ToolCommand> ColorChanger::getCommand() {
    return std::make_unique<ChangeColor>(color);
}
