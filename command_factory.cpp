#include "command_factory.hpp"

#include "commands/command_name.hpp"
#include "commands/draw_circle.hpp"
#include "commands/draw_rectangle.hpp"
#include "commands/draw_poly_line.hpp"
#include "commands/draw_text.hpp"
#include "commands/draw_image.hpp"

std::unique_ptr<Command> DrawCommandFactory::create(const CommandDTO &cmd) {
    if(cmd.getName() == CommandName::DrawCircleName){
        return std::make_unique<DrawCircle>(cmd.getCenter(), cmd.getRadius(), cmd.getThickness(), cmd.getColor());
    }else if(cmd.getName() == CommandName::DrawRectangleName){
        return std::make_unique<DrawRectangle>(cmd.getP1(), cmd.getP2(), cmd.getThickness(), cmd.getColor());
    }else if(cmd.getName() == CommandName::DrawPolyLineName){
        return std::make_unique<DrawPolyLine>(cmd.getCoords(), cmd.getThickness(), cmd.getColor());
    }else if(cmd.getName() == CommandName::DrawTextName){
        return std::make_unique<DrawText>(cmd.getLeftDown(), cmd.getText(), cmd.getThickness(), cmd.getColor());
    }else if(cmd.getName() == CommandName::DrawImageName){
        return std::make_unique<DrawImage>(cmd.getUpLeft(), cmd.getToDraw(), cmd.getMask());
    } else{
        return {};
    }
}
