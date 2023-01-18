#include "tool_factory.hpp"

#include "tool/circle_maker.hpp"
#include "tool/rectangle_maker.hpp"
#include "tool/line_maker.hpp"
#include "tool/text_maker.hpp"
#include "tool/undo_maker.hpp"
#include "tool/redo_maker.hpp"
#include "tool/color_changer.hpp"
#include "tool/thickness_changer.hpp"

std::unique_ptr<Tool> ToolFactory::create(const std::string &name) {
    if(name.starts_with(ToolName::ServicePrefix)){
        if(name.ends_with(ToolName::Undo)){
            return std::make_unique<UndoMaker>();
        }else if(name.ends_with(ToolName::Redo)){
            return std::make_unique<RedoMaker>();
        }
    }
    return std::make_unique<Tool>(name);
}

std::unique_ptr<Tool> ToolFactory::create(const std::string &name, int thickness, Color color) {
    if(name.starts_with(ToolName::DrawPrefix)) {
        if(name.ends_with(ToolName::Circle)){
            return std::make_unique<CircleMaker>(thickness, color);
        }else if(name.ends_with(ToolName::Rectangle)){
            return std::make_unique<RectangleMaker>(thickness, color);
        }else if(name.ends_with(ToolName::PolyLine)){
            return std::make_unique<LineMaker>(thickness, color);
        }else if(name.ends_with(ToolName::Text)){
            return std::make_unique<TextMaker>(thickness, color);
        }
    }
    return std::make_unique<Tool>(name);
}

std::unique_ptr<Tool> ToolFactory::create(const std::string &name, Rectangle D) {
    if(name.starts_with(ToolName::ToolPrefix)) {
        if(name.ends_with(ToolName::Color)){
            return std::make_unique<ColorChanger>(D);
        }
    }
    return std::make_unique<Tool>(name);
}

std::unique_ptr<Tool> ToolFactory::create(const std::string &name, int x_min, int x_max, int max_thickness) {
    if(name.starts_with(ToolName::ToolPrefix)) {
        if(name.ends_with(ToolName::Thickness)){
            return std::make_unique<ThicknessChanger>(x_min, x_max, max_thickness);
        }
    }
    return std::make_unique<Tool>(name);
}
