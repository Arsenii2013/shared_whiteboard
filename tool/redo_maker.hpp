#ifndef SHARED_WHITEBOARD_REDO_MAKER_HPP
#define SHARED_WHITEBOARD_REDO_MAKER_HPP
#include "service_tool.hpp"
#include "../service_commands/redo.hpp"
#include "tool_name.hpp"

class RedoMaker final : public ServiceTool{
    bool _ready{false};
public:
    RedoMaker() : ServiceTool(ToolName::Redo) {}

    void processMouseEvent(MouseEvent event, int x, int y) override {
        if(event == MouseEvent::LDOWN){

        }else if(event == MouseEvent::LUP){
            _ready = true;
        }
    };
    void processKey(ASCIIKey key) override {};

    bool ready() override {return _ready;};

    std::unique_ptr<ServiceCommand> getCommand() override {
        _ready = false;
        return std::make_unique<Redo>();
    };
};

#endif //SHARED_WHITEBOARD_REDO_MAKER_HPP
