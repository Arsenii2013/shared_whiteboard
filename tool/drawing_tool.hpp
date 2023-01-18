#ifndef SHARED_WHITEBOARD_DRAWING_TOOL_HPP
#define SHARED_WHITEBOARD_DRAWING_TOOL_HPP
#include "tool.hpp"
#include "tool_name.hpp"
#include "../commands/command_dto.hpp"

class DrawingTool : public Tool{
protected:
    int thickness;
    Color color{0,0,0};
public:
    DrawingTool(const std::string &name, int thickness, Color color) :
                    Tool(ToolName::DrawPrefix + name),
                    thickness(thickness),
                    color(color) {}

    virtual bool ready() {return false;};
    virtual bool final() {return false;};
    virtual CommandDTO getCommand() { return {}; };

    void setThickness(int _thickness) {
        thickness = _thickness;
    }

    void setColor(const Color &_color) {
        color = _color;
    }
};

#endif //SHARED_WHITEBOARD_DRAWING_TOOL_HPP
