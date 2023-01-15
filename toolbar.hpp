#ifndef SHARED_WHITEBOARD_TOOLBAR_HPP
#define SHARED_WHITEBOARD_TOOLBAR_HPP

#include <utility>

#include "tool/tool.hpp"
#include "tool_command/tool_command.hpp"

#include <stdexcept>
#include <map>

class Toolbar final{
    Image vision;
    std::vector<std::pair<std::shared_ptr<Tool>, Rectangle>> toolkit;
    std::shared_ptr<Tool> active;

public:
    explicit Toolbar(const std::vector<std::pair<std::shared_ptr<Tool>, Image>>& _toolkit) {
        for(const auto& pair: _toolkit){
            auto s_rows = vision.getStorage().rows;
            vision.addImage(pair.second, Image::ImageEdge::Down);
            toolkit.emplace_back(pair.first, Rectangle{0, vision.getStorage().cols, s_rows, vision.getStorage().rows});
        }
        active = toolkit.begin()->first;
    }

    void processMouseEvent(MouseEvent event, int x, int y) {
        if (event == MouseEvent::LDOWN) {
            active = std::find_if(toolkit.begin(), toolkit.end(),
                                  [x, y](const std::pair<std::shared_ptr<Tool>, Rectangle> &p) {
                                      return p.second.in(x, y);
                                  })->first;

        }
    }

    Tool& getActiveTool(){
        return *active;
    }

    void for_each_drawing_tool(std::unique_ptr<ToolCommand> cmd){
        for(auto& pair: toolkit){
            auto tool_ptr = pair.first;
            if(tool_ptr->getName().substr(0, 5) == ToolName::DrawPrefix) {
                cmd->execute(*std::dynamic_pointer_cast<DrawingTool>(tool_ptr));
            }
        }
    }

    Image getImage(){
        return vision;
    }
};

#endif //SHARED_WHITEBOARD_TOOLBAR_HPP
