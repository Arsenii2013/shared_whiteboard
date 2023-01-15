#ifndef SHARED_WHITEBOARD_REDO_HPP
#define SHARED_WHITEBOARD_REDO_HPP
#include "service_command.hpp"

class Redo : public ServiceCommand{
public:
    explicit Redo();

    void execute(Whiteboard & whiteboard) override {
        whiteboard.redo();
    };
};
#endif //SHARED_WHITEBOARD_REDO_HPP
