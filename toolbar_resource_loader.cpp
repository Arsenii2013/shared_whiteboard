#include "toolbar_resource_loader.hpp"

ToolbarResourceLoader::ToolbarResourceLoader(const std::filesystem::path &dir) {
    for (auto const& dir_entry : std::filesystem::directory_iterator{dir})
    {
        std::string stem = dir_entry.path().stem();
        resources.emplace(stem, dir_entry.path());
    }
}

Image ToolbarResourceLoader::get(const std::string &tool_name) {
    if(resources.contains(tool_name)){
        return resources[tool_name];
    } else{
        return {100, 100, Color(256, 256, 256)};
    }
}
