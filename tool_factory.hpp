#ifndef SHARED_WHITEBOARD_TOOL_FACTORY_HPP
#define SHARED_WHITEBOARD_TOOL_FACTORY_HPP
#include "tool/tool_name.hpp"
#include "tool/tool.hpp"

#include <memory>

class ToolFactory{
public:

    [[nodiscard]] static std::unique_ptr<Tool> create(const std::string& name);

    [[nodiscard]] static std::unique_ptr<Tool> create(const std::string& name, int thickness, Color color);

    [[nodiscard]] static std::unique_ptr<Tool> create(const std::string& name, Rectangle D);

    [[nodiscard]] static std::unique_ptr<Tool> create(const std::string& name, int x_min, int x_max, int max_thickness);
};
#endif //SHARED_WHITEBOARD_TOOL_FACTORY_HPP
