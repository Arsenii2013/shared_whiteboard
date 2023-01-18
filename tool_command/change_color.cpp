#include "change_color.hpp"

void ChangeColor::execute(DrawingTool &tool) {
    tool.setColor(color);
}
