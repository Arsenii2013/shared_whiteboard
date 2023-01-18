#include "undo.hpp"

Undo::Undo() : ServiceCommand(ServiceCommandName::ServiceUndoName) {}

void Undo::execute(Whiteboard &whiteboard) {
    whiteboard.undo();
}
