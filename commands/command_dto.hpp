#ifndef SHARED_WHITEBOARD_COMMAND_DTO_HPP
#define SHARED_WHITEBOARD_COMMAND_DTO_HPP
#include <string>
#include <utility>

#include "command_name.hpp"
#include "../utilities.hpp"
#include "../image.hpp"
class CommandDTO final{
    std::string name;
    Color color{0U, 0U,0U};
    int thickness{0};

    int radius{0};
    Point2D center{0,0};

    Point2D p1{0,0};
    Point2D p2{0,0};

    std::list<Point2D> coords{};

    Point2D up_left{0,0};
    Image to_draw{};
    Image mask{};
public:
    CommandDTO(int radius, const Point2D &center, const Color &color) : name(CommandName::DrawCircleName),
                                                                         color(color),
                                                                         radius(radius),
                                                                         center(center) {}

    CommandDTO(const Point2D &p1, const Point2D &p2, const Color &color) : name(CommandName::DrawRectangleName),
                                                                            color(color),
                                                                            p1(p1), p2(p2) {}

    CommandDTO(std::list<Point2D> coords, int thickness, const Color &color) : name(CommandName::DrawPolyLineName),
                                                                                color(color),
                                                                                thickness(thickness),
                                                                                coords(std::move(coords)) {}

    [[nodiscard]] const std::string &getName() const {
        return name;
    }

    [[nodiscard]] const Color &getColor() const {
        return color;
    }

    [[nodiscard]] int getThickness() const {
        return thickness;
    }

    [[nodiscard]] int getRadius() const {
        return radius;
    }

    [[nodiscard]] const Point2D &getCenter() const {
        return center;
    }

    [[nodiscard]] const Point2D &getP1() const {
        return p1;
    }

    [[nodiscard]] const Point2D &getP2() const {
        return p2;
    }

    [[nodiscard]] const std::list<Point2D> &getCoords() const {
        return coords;
    }

    [[nodiscard]] const Point2D &getUpLeft() const {
        return up_left;
    }

    [[nodiscard]] const Image &getToDraw() const {
        return to_draw;
    }

    [[nodiscard]] const Image &getMask() const {
        return mask;
    }
};

std::ostream& operator<<(std::ostream& stream,
                         const CommandDTO& dto);

std::istream& operator>>(std::istream& stream,
                         CommandDTO& dto);
#endif //SHARED_WHITEBOARD_COMMAND_DTO_HPP
