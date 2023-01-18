#include "whiteboard.hpp"

Whiteboard::Whiteboard(int x, int y, Color color) : board(x, y, color) {}

void Whiteboard::undo() {
    if(redoed.empty()){
        return;
    }
    undoed.push(std::move(redoed.top()));
    redoed.pop();
    undoed.top()->undo(board);
}

void Whiteboard::redo() {
    if(undoed.empty()){
        return;
    }
    redoed.push(std::move(undoed.top()));
    undoed.pop();
    redoed.top()->redo(board);
}

void Whiteboard::add_and_redo(std::unique_ptr<Command> cmd) {
    redoed.push(std::move(cmd));
    redoed.top()->redo(board);
}

void Whiteboard::undo_and_remove() {
    redoed.top()->undo(board);
    redoed.pop();
}

const Image &Whiteboard::getBoard() const {
    return board;
}

