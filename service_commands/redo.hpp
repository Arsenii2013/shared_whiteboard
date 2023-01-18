#ifndef SHARED_WHITEBOARD_REDO_HPP
#define SHARED_WHITEBOARD_REDO_HPP
#include "service_command.hpp"
#include "service_command_name.hpp"

class Redo : public ServiceCommand{
public:
    explicit Redo();

    void execute(Whiteboard & whiteboard) override;;
};
#endif //SHARED_WHITEBOARD_REDO_HPP
