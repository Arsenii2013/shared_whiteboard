#include "user_editor.hpp"

#include "tool_factory.hpp"
#include "toolbar_resource_loader.hpp"

#include "tool/tool_name.hpp"
#include "tool/drawing_tool.hpp"
#include "tool/service_tool.hpp"
#include "tool/tool_tool.hpp"

#include "service_command_factory.hpp"
#include "command_factory.hpp"

UserEditor::UserEditor(const Settings &settings) :
        board(settings.getWhiteboardWight(), settings.getWhiteboardHeight(), settings.getWhiteboardBackground())
{
    toolbar = Toolbar{settings.getToolbarOrientation()};
    toolbar_up_left = settings.getToolbarUpLeft();

    ToolbarResourceLoader loader{settings.getResourcePath()};

    for(const std::string& tool_name: settings.getToolkit()) {
        if (tool_name.starts_with(ToolName::DrawPrefix)) {

            toolbar.addTool(
                    ToolFactory::create(tool_name,
                                        settings.getDefaultDrawThickness(),
                                        settings.getDefaultDrawColor()),
                    loader.get(tool_name));
        }else if(tool_name.starts_with(ToolName::ServicePrefix)){

            toolbar.addTool(
                    ToolFactory::create(tool_name),
                    loader.get(tool_name));
        }else if(tool_name.starts_with(ToolName::ToolPrefix)){
            if(tool_name.ends_with(ToolName::Color)){

                Rectangle tool_D;

                if(settings.getToolbarOrientation() == Toolbar::Orientation::Vertical){
                    tool_D = Rectangle{0, loader.get(tool_name).getX(),
                                       toolbar.height(), toolbar.height() + loader.get(tool_name).getY()};
                }else if(settings.getToolbarOrientation() == Toolbar::Orientation::Horizontal){
                    tool_D = Rectangle{toolbar.wight(), toolbar.wight() + loader.get(tool_name).getX(),
                                       0, loader.get(tool_name).getY()};
                }

                toolbar.addTool(
                        ToolFactory::create(tool_name,
                                                      tool_D),
                        loader.get(tool_name));
            }else if(tool_name.ends_with(ToolName::Thickness)){

                int x_min, x_max;

                if(settings.getToolbarOrientation() == Toolbar::Orientation::Vertical){
                    x_min = 0;
                    x_max = loader.get(tool_name).getX();
                }else if(settings.getToolbarOrientation() == Toolbar::Orientation::Horizontal){
                    x_min = toolbar.wight();
                    x_max = toolbar.wight() + loader.get(tool_name).getX();
                }

                toolbar.addTool(
                        ToolFactory::create(tool_name,
                                                         x_min,
                                                         x_max,
                                             settings.getMaxThickness()),
                        loader.get(tool_name));
            }
        }else{
            toolbar.addTool(
                    ToolFactory::create(tool_name),
                    loader.get(tool_name));
        }
    }
}

void UserEditor::get_data_from_active_tool() {
    if(toolbar.getActiveTool().getName().starts_with(ToolName::ToolPrefix)){
        auto& ttool = dynamic_cast<ToolTool &>(toolbar.getActiveTool());
        toolbar.forEachDrawingTool(ttool.getCommand());
    }else if(toolbar.getActiveTool().getName().starts_with(ToolName::DrawPrefix)) {
        auto& dwtool = dynamic_cast<DrawingTool &>(toolbar.getActiveTool());
        if (dwtool.ready()) {
            bool final = dwtool.final();
            auto cmd = dwtool.getCommand();
            board.add_and_redo(DrawCommandFactory::create(cmd));
            draw_image(getImage());
            if(!final){
                board.undo_and_remove();
            }else{
                send_cmd(cmd);
            }
        }
    }else if(toolbar.getActiveTool().getName().starts_with(ToolName::ServicePrefix)){
        auto& stool = dynamic_cast<ServiceTool &>(toolbar.getActiveTool());
        if (stool.ready()) {
            auto cmd = stool.getCommand();
            ServiceCommandFactory::create(cmd)->execute(board);
            draw_image(getImage());
            send_service_cmd(cmd);
        }
    }
}

void UserEditor::processMouseEvent(MouseEvent event, int x, int y) {
    if(Rectangle{toolbar_up_left.getX(), toolbar_up_left.getX() + toolbar.wight(),
                 toolbar_up_left.getY(), toolbar_up_left.getX() + toolbar.height()}.in(x, y)){
        x -= toolbar_up_left.getX();
        y -= toolbar_up_left.getY();
        toolbar.processMouseEvent(event, x, y);
        if(toolbar.getActiveTool().getName().starts_with(ToolName::ToolPrefix)){
            toolbar.getActiveTool().processMouseEvent(event, x, y);
            get_data_from_active_tool();
        }
    }else{
        toolbar.getActiveTool().processMouseEvent(event, x, y);
        get_data_from_active_tool();
    }
}

void UserEditor::processKey(ASCIIKey key) {
    toolbar.getActiveTool().processKey(key);
    get_data_from_active_tool();
    //draw_image(getImage());
}

Image UserEditor::getImage() const {
    auto tmp = board.getBoard();
    tmp.drawImage(toolbar_up_left, toolbar.getImage());
    return tmp;
}

void UserEditor::setDrawFunction(std::function<void(const Image &)> _draw_image) {
    draw_image = std::move(_draw_image);
    draw_image(getImage());
}

void UserEditor::setSendCommand(std::function<void(const CommandDTO &)> _send_cmd) {
    send_cmd = std::move(_send_cmd);
}

void UserEditor::setSendServiceCommand(std::function<void(const ServiceCommandDTO &)> _send_service_cmd) {
    send_service_cmd = std::move(_send_service_cmd);
}

void UserEditor::processExternal(const CommandDTO &cmd) {
    board.add_and_redo(DrawCommandFactory::create(cmd));
    draw_image(getImage());
}

void UserEditor::processExternal(const ServiceCommandDTO &cmd) {
    ServiceCommandFactory::create(cmd)->execute(board);
    draw_image(getImage());
}
