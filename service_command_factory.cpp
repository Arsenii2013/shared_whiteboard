#include "service_command_factory.hpp"

#include "service_commands/undo.hpp"
#include "service_commands/redo.hpp"
#include "service_commands/service_command_name.hpp"

std::unique_ptr<ServiceCommand> ServiceCommandFactory::create(const ServiceCommandDTO &cmd) {
    if(cmd.getName() == ServiceCommandName::ServiceUndoName){
        return std::make_unique<Undo>();
    }else if(cmd.getName() == ServiceCommandName::ServiceRedoName){
        return std::make_unique<Redo>();
    } else{
        return {};
    }
}
