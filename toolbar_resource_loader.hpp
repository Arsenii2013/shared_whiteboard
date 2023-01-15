#ifndef SHARED_WHITEBOARD_TOOLBAR_RESOURCE_LOADER_HPP
#define SHARED_WHITEBOARD_TOOLBAR_RESOURCE_LOADER_HPP

#include <filesystem>

#include "tool/tool_name.hpp"
#include "image.hpp"

class ToolbarResourceLoader final{
    std::map<std::string, Image> resources;
public:
    explicit ToolbarResourceLoader(const std::filesystem::path& dir){
        // file format: prefix_name.jpg
        for (auto const& dir_entry : std::filesystem::directory_iterator{dir})
        {
            std::string stem = dir_entry.path().stem();
            resources.emplace(stem, dir_entry.path());
        }
    }

    Image get(const std::string& tool_name){
        if(resources.contains(tool_name)){
            return resources[tool_name];
        } else{
            return {100, 100, Color(256, 256, 256)};
        }
    }
};
#endif //SHARED_WHITEBOARD_TOOLBAR_RESOURCE_LOADER_HPP
