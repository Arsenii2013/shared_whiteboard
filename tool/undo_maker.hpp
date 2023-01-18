#ifndef SHARED_WHITEBOARD_UNDO_MAKER_HPP
#define SHARED_WHITEBOARD_UNDO_MAKER_HPP
#include "service_tool.hpp"
#include "tool_name.hpp"
#include "../service_commands/service_command_name.hpp"

class UndoMaker final : public ServiceTool{
    bool _ready{false};
public:
    UndoMaker();

    void processMouseEvent(MouseEvent event, int x, int y) override;;
    void processKey(ASCIIKey key) override {};

    bool ready() override {return _ready;};

    ServiceCommandDTO getCommand() override;;
};

#endif //SHARED_WHITEBOARD_UNDO_MAKER_HPP
