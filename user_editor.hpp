#ifndef SHARED_WHITEBOARD_USER_EDITOR_HPP
#define SHARED_WHITEBOARD_USER_EDITOR_HPP
#include <functional>
#include <utility>

#include "settings.hpp"
#include "whiteboard.hpp"
#include "toolbar.hpp"
#include "service_commands/service_command_dto.hpp"

class UserEditor final{
    Whiteboard board;
    Toolbar toolbar;

    Point2D toolbar_up_left;

    std::function<void (const Image&)> draw_image;
    std::function<void (const CommandDTO&)> send_cmd;
    std::function<void (const ServiceCommandDTO&)> send_service_cmd;

    void get_data_from_active_tool();

    [[nodiscard]] Image getImage() const;
public:
    explicit UserEditor(const Settings& settings);

    void processMouseEvent(MouseEvent event, int x, int y);

    void processKey(ASCIIKey key);

    void setDrawFunction(std::function<void (const Image&)> _draw_image);
    void setSendCommand(std::function<void (const CommandDTO&)> _send_cmd);;
    void setSendServiceCommand(std::function<void (const ServiceCommandDTO&)> _send_service_cmd);;

    void processExternal(const CommandDTO& cmd);
    void processExternal(const ServiceCommandDTO& cmd);

};

#endif //SHARED_WHITEBOARD_USER_EDITOR_HPP
