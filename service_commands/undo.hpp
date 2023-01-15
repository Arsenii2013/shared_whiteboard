#ifndef SHARED_WHITEBOARD_UNDO_HPP
#define SHARED_WHITEBOARD_UNDO_HPP
#include "service_command.hpp"

class Undo : public ServiceCommand{
public:
    explicit Undo();

    void execute(Whiteboard & whiteboard) override {
        whiteboard.undo();
    };
};
#endif //SHARED_WHITEBOARD_UNDO_HPP
