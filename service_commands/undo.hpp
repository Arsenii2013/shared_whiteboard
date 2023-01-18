#ifndef SHARED_WHITEBOARD_UNDO_HPP
#define SHARED_WHITEBOARD_UNDO_HPP
#include "service_command.hpp"
#include "service_command_name.hpp"

class Undo : public ServiceCommand{
public:
    explicit Undo();

    void execute(Whiteboard & whiteboard) override;;
};
#endif //SHARED_WHITEBOARD_UNDO_HPP
