#ifndef SHARED_WHITEBOARD_WHITEBOARD_HPP
#define SHARED_WHITEBOARD_WHITEBOARD_HPP
#include "commands/command.hpp"
#include "image.hpp"

#include <stack>

class Whiteboard final{
    std::stack<std::unique_ptr<Command>> redoed{};
    std::stack<std::unique_ptr<Command>> undoed{};

    Image board{};

public:
    Whiteboard(int x, int y, Color color): board(x, y, color) {};

    void undo(){
        undoed.push(std::move(redoed.top()));
        redoed.pop();
        undoed.top()->undo(board);
    }

    void redo() {
        redoed.push(std::move(undoed.top()));
        undoed.pop();
        redoed.top()->redo(board);
    }

    void add_and_redo(std::unique_ptr<Command> cmd) {
        redoed.push(std::move(cmd));
        redoed.top()->redo(board);
    }

    void undo_and_remove(){
        redoed.top()->undo(board);
        redoed.pop();
    }

    [[nodiscard]] const Image &getBoard() const {
        return board;
    }
};
#endif //SHARED_WHITEBOARD_WHITEBOARD_HPP
