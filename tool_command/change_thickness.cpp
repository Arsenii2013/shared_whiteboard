#include "change_thickness.hpp"

void ChangeThickness::execute(DrawingTool &tool) {
    tool.setThickness(thickness);
}
