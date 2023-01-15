#ifndef SHARED_WHITEBOARD_SERVICE_COMMAND_HPP
#define SHARED_WHITEBOARD_SERVICE_COMMAND_HPP
#include "../whiteboard.hpp"
class ServiceCommand{
protected:
    std::string name;
public:
    ServiceCommand() = default;

    explicit ServiceCommand(std::string name) : name(std::move(name)) {}

    [[nodiscard]] const std::string &get_name() const {
        return name;
    }

    virtual void execute(Whiteboard &) {};

    virtual ~ServiceCommand() = default;
};
#endif //SHARED_WHITEBOARD_SERVICE_COMMAND_HPP
