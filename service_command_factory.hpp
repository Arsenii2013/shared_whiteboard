#ifndef SHARED_WHITEBOARD_SERVICE_COMMAND_FACTORY_HPP
#define SHARED_WHITEBOARD_SERVICE_COMMAND_FACTORY_HPP
#include "service_commands/service_command.hpp"
#include "service_commands/service_command_dto.hpp"

class ServiceCommandFactory{
public:
    [[nodiscard]] static std::unique_ptr<ServiceCommand> create(const ServiceCommandDTO& cmd);
};
#endif //SHARED_WHITEBOARD_SERVICE_COMMAND_FACTORY_HPP
