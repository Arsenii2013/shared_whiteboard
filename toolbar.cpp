#include "toolbar.hpp"

Toolbar::Toolbar(std::vector<std::pair<std::unique_ptr<Tool>, Image>> &&_toolkit, Orientation _orientation)  {
    orientation = _orientation;
    for(auto& pair: _toolkit){
        addTool(std::move(pair.first), pair.second);
    }
    active = toolkit.begin();
}

void Toolbar::processMouseEvent(MouseEvent event, int x, int y) {
    if (event == MouseEvent::LDOWN) {
        active = std::find_if(toolkit.begin(), toolkit.end(),
                              [x, y](const std::pair<Rectangle, std::unique_ptr<Tool>> &p) {
                                  return p.first.in(x, y);
                              });
    }
}

void Toolbar::forEachDrawingTool(std::unique_ptr<ToolCommand> cmd) {
    std::for_each(toolkit.begin(), toolkit.end(), [this, &cmd](const std::pair<Rectangle, std::unique_ptr<Tool>>& p){
        auto& tool_ptr = p.second;
        if(tool_ptr->getName().substr(0, ToolName::DrawPrefix.size()) == ToolName::DrawPrefix) {
            cmd->execute(dynamic_cast<DrawingTool &>(*tool_ptr));
        }
    });
}

void Toolbar::addTool(std::unique_ptr<Tool> tool_ptr, const Image& image) {
    auto s_rows = vision.getStorage().rows;
    auto s_cols = vision.getStorage().cols;
    if(orientation == Orientation::Vertical) {
        vision.addImage(image, Image::ImageEdge::Down);
    }else if(orientation == Orientation::Horizontal){
        vision.addImage(image, Image::ImageEdge::Right);
    }
    if(orientation == Orientation::Vertical) {
        toolkit.emplace_back(Rectangle{0, vision.getStorage().cols, s_rows, vision.getStorage().rows},
                             std::move(tool_ptr));
    }else if(orientation == Orientation::Horizontal ){
        toolkit.emplace_back(Rectangle{s_cols, vision.getStorage().cols, 0, vision.getStorage().rows},
                             std::move(tool_ptr));
    }
    active = toolkit.begin();
}
