#ifndef SHARED_WHITEBOARD_COMMAND_FACTORY_HPP
#define SHARED_WHITEBOARD_COMMAND_FACTORY_HPP
#include "commands/command_dto.hpp"
#include "commands/command.hpp"

class DrawCommandFactory{
public:
    [[nodiscard]] static std::unique_ptr<Command> create(const CommandDTO& cmd);
};
#endif //SHARED_WHITEBOARD_COMMAND_FACTORY_HPP
