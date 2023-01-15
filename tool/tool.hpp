#ifndef SHARED_WHITEBOARD_TOOL_HPP
#define SHARED_WHITEBOARD_TOOL_HPP
#include <utility>

#include "../commands/command.hpp"
#include "../service_commands/service_command.hpp"
#include "../utilities.hpp"

class Tool{
    std::string name;
public:

    explicit Tool(std::string name) : name(std::move(name)) {}

    [[nodiscard]] const std::string &getName() const {
        return name;
    }

    virtual void processMouseEvent(MouseEvent event, int x, int y) {};
    virtual void processKey(ASCIIKey key) {};

    virtual ~Tool() = default;
};

#endif //SHARED_WHITEBOARD_TOOL_HPP
