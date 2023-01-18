#include "redo.hpp"

Redo::Redo() : ServiceCommand(ServiceCommandName::ServiceRedoName) {}

void Redo::execute(Whiteboard &whiteboard) {
    whiteboard.redo();
}
