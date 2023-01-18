#ifndef SHARED_WHITEBOARD_SERVICE_TOOL_HPP
#define SHARED_WHITEBOARD_SERVICE_TOOL_HPP
#include "tool.hpp"
#include "tool_name.hpp"
#include "../service_commands/service_command_dto.hpp"

class ServiceTool : public Tool{
public:
    explicit ServiceTool(const std::string &name) : Tool(ToolName::ServicePrefix + name) {}

    virtual bool ready() {return false;};
    virtual ServiceCommandDTO getCommand() { return {}; };
};
#endif //SHARED_WHITEBOARD_SERVICE_TOOL_HPP
