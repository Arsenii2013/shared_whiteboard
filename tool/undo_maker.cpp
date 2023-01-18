#include "undo_maker.hpp"

UndoMaker::UndoMaker() : ServiceTool(ToolName::Undo) {}

void UndoMaker::processMouseEvent(MouseEvent event, int x, int y) {
    if(event == MouseEvent::LDOWN){

    }else if(event == MouseEvent::LUP){
        _ready = true;
    }
}

ServiceCommandDTO UndoMaker::getCommand() {
    _ready = false;
    return ServiceCommandDTO{ServiceCommandName::ServiceUndoName};
}
