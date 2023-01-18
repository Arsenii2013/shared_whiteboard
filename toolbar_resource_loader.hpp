#ifndef SHARED_WHITEBOARD_TOOLBAR_RESOURCE_LOADER_HPP
#define SHARED_WHITEBOARD_TOOLBAR_RESOURCE_LOADER_HPP

#include <filesystem>

#include "tool/tool_name.hpp"
#include "image.hpp"

class ToolbarResourceLoader final{
    std::map<std::string, Image> resources;
public:
    explicit ToolbarResourceLoader(const std::filesystem::path& dir);

    Image get(const std::string& tool_name);
};
#endif //SHARED_WHITEBOARD_TOOLBAR_RESOURCE_LOADER_HPP
