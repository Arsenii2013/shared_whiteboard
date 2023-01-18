#ifndef SHARED_WHITEBOARD_SETTINGS_HPP
#define SHARED_WHITEBOARD_SETTINGS_HPP
#include "utilities.hpp"
#include "toolbar.hpp"

class Settings final{
private:
    std::filesystem::path resource_path;
    std::vector<std::string> toolkit;

    Toolbar::Orientation toolbar_orientation{Toolbar::Orientation::Vertical};
    Point2D toolbar_up_left{0, 0};

    int whiteboard_wight{1000U}, whiteboard_height{1000U};
    Color whiteboard_background{256, 256, 256};

    int default_draw_thickness{1};
    Color default_draw_color{0, 0, 0};
    int max_thickness{20};
public:
    Settings(std::filesystem::path resourcePath, std::vector<std::string> toolkit) : resource_path(std::move(
            resourcePath)), toolkit(std::move(toolkit)) {};

    [[nodiscard]] const std::filesystem::path &getResourcePath() const {
        return resource_path;
    }

    [[nodiscard]] const std::vector<std::string> &getToolkit() const {
        return toolkit;
    }

    Toolbar::Orientation getToolbarOrientation() const {
        return toolbar_orientation;
    }

    const Point2D &getToolbarUpLeft() const {
        return toolbar_up_left;
    }

    [[nodiscard]] int getWhiteboardWight() const {
        return whiteboard_wight;
    }

    [[nodiscard]] int getWhiteboardHeight() const {
        return whiteboard_height;
    }

    [[nodiscard]] const Color &getWhiteboardBackground() const {
        return whiteboard_background;
    }

    [[nodiscard]] int getDefaultDrawThickness() const {
        return default_draw_thickness;
    }

    [[nodiscard]] const Color &getDefaultDrawColor() const {
        return default_draw_color;
    }

    [[nodiscard]] int getMaxThickness() const {
        return max_thickness;
    }
};
#endif //SHARED_WHITEBOARD_SETTINGS_HPP
