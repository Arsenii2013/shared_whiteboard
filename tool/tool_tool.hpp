#ifndef SHARED_WHITEBOARD_TOOL_TOOL_HPP
#define SHARED_WHITEBOARD_TOOL_TOOL_HPP
#include "tool.hpp"
#include "tool_name.hpp"
#include "../tool_command/tool_command.hpp"

class ToolTool : public Tool{
public:
    explicit ToolTool(const std::string &name) : Tool(ToolName::ToolPrefix + name) {}

    virtual std::unique_ptr<ToolCommand> getCommand() { return {}; };
};

#endif //SHARED_WHITEBOARD_TOOL_TOOL_HPP
