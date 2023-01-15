#ifndef SHARED_WHITEBOARD_TOOL_COMMAND_HPP
#define SHARED_WHITEBOARD_TOOL_COMMAND_HPP
#include "../tool/drawing_tool.hpp"
class ToolCommand{
protected:
    std::string name;
public:
    ToolCommand() = default;

    explicit ToolCommand(std::string name) : name(std::move(name)) {}

    [[nodiscard]] const std::string &get_name() const {
        return name;
    }

    virtual void execute(DrawingTool &) {};

    virtual ~ToolCommand() = default;
};
#endif //SHARED_WHITEBOARD_TOOL_COMMAND_HPP
