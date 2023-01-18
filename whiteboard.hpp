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
    Whiteboard(int x, int y, Color color);

    void undo();

    void redo();

    void add_and_redo(std::unique_ptr<Command> cmd);

    void undo_and_remove();

    [[nodiscard]] const Image &getBoard() const;
};
#endif //SHARED_WHITEBOARD_WHITEBOARD_HPP
