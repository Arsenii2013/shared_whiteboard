#ifndef SHARED_WHITEBOARD_TOOLBAR_HPP
#define SHARED_WHITEBOARD_TOOLBAR_HPP

#include "tool/tool.hpp"
#include "tool_command/tool_command.hpp"

#include <stdexcept>

class Toolbar final{
public:
    enum class Orientation{
        Vertical,
        Horizontal,
    };
private:
    Image vision;
    std::vector<std::pair<Rectangle, std::unique_ptr<Tool>>> toolkit;
    std::vector<std::pair<Rectangle, std::unique_ptr<Tool>>>::iterator active;
    Orientation orientation{Orientation::Vertical};
public:
    Toolbar() = default;
    explicit Toolbar(Orientation _orientation): orientation(_orientation) {};
    Toolbar(std::vector<std::pair<std::unique_ptr<Tool>, Image>>&& _toolkit, Orientation _orientation);

    void addTool(std::unique_ptr<Tool> tool_ptr, const Image& image);

    void processMouseEvent(MouseEvent event, int x, int y);

    Tool& getActiveTool(){
        return *((*active).second);
    }

    void forEachDrawingTool(std::unique_ptr<ToolCommand> cmd);

    [[nodiscard]] Image getImage() const{
        return vision;
    }

    [[nodiscard]] int wight() const{
        return vision.getX();
    }

    [[nodiscard]] int height() const{
        return vision.getY();
    }
};

#endif //SHARED_WHITEBOARD_TOOLBAR_HPP
