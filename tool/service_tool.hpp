#ifndef SHARED_WHITEBOARD_SERVICE_TOOL_HPP
#define SHARED_WHITEBOARD_SERVICE_TOOL_HPP
#include "tool.hpp"
#include "tool_name.hpp"

class ServiceTool : public Tool{
public:
    explicit ServiceTool(const std::string &name) : Tool(ToolName::ServicePrefix + name) {}

    virtual bool ready() {return false;};
    virtual std::unique_ptr<ServiceCommand> getCommand() { return {}; };
};
#endif //SHARED_WHITEBOARD_SERVICE_TOOL_HPP
