#include "redo_maker.hpp"

RedoMaker::RedoMaker() : ServiceTool(ToolName::Redo) {}

void RedoMaker::processMouseEvent(MouseEvent event, int x, int y) {
    if(event == MouseEvent::LDOWN){

    }else if(event == MouseEvent::LUP){
        _ready = true;
    }
}

ServiceCommandDTO RedoMaker::getCommand() {
    _ready = false;
    return ServiceCommandDTO{ServiceCommandName::ServiceRedoName};
}
