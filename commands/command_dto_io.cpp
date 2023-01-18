#include "command_dto.hpp"

namespace {
    std::ostream& operator<<(std::ostream& stream,
                             const Point2D& p) {
        stream << p.getX() << ' ' << p.getY();
        return stream;
    }

    std::istream& operator>>(std::istream& stream,
                             Point2D& p) {
        int x, y;
        stream >> x >> y;
        p.setX(x);
        p.setY(y);
        return stream;
    }

    std::ostream& operator<<(std::ostream& stream,
                             const Color& c) {
        stream << c.getR() << ' ' << c.getG() << ' ' << c.getB();
        return stream;
    }

    std::istream& operator>>(std::istream& stream,
                             Color& c) {
        size_t r, g, b;
        stream >> r >> g >> b;
        c.setR(r);
        c.setG(g);
        c.setB(b);
        return stream;
    }

    std::ostream& operator<<(std::ostream& stream,
                             const std::list<Point2D>& list) {
        for (auto const &point: list) {
            stream << point << ' ';
        }
        return stream;
    }

    std::istream& operator>>(std::istream& stream,
                             std::list<Point2D>& list) {
        std::string line;
        std::getline(stream, line);
        std::istringstream iss(line);
        int x, y;
        list.clear();
        while (iss >> x >> y){
            list.emplace_back(x, y);
        }

        return stream;
    }
}

std::ostream &operator<<(std::ostream &stream, const CommandDTO &dto) {
    if(dto.getName() == CommandName::DrawCircleName){
        stream << dto.getName() << std::endl
               << dto.getRadius() << std::endl
               << dto.getCenter() << std::endl
               << dto.getThickness() << std::endl
               << dto.getColor() << std::endl;
    }else if(dto.getName() == CommandName::DrawRectangleName){
        stream << dto.getName() << std::endl
               << dto.getP1() << std::endl
               << dto.getP2() << std::endl
               << dto.getThickness() << std::endl
               << dto.getColor() << std::endl;
    }else if(dto.getName() == CommandName::DrawPolyLineName){
        stream << dto.getName() << std::endl
               << dto.getCoords() << std::endl
               << dto.getThickness() << std::endl
               << dto.getColor() << std::endl;
    }else if(dto.getName() == CommandName::DrawTextName){
        stream << dto.getName() << std::endl
               << dto.getLeftDown() << std::endl
               << dto.getText() << std::endl
               << dto.getThickness() << std::endl
               << dto.getColor() << std::endl;
    }else if(dto.getName() == CommandName::DrawImageName){
        stream << dto.getName() << std::endl
               << dto.getUpLeft() << std::endl
               << dto.getToDraw() << std::endl
               << dto.getMask() << std::endl;
    }else{

    }
    return stream;
}

std::istream &operator>>(std::istream &stream, CommandDTO &dto) {
    std::string name;
    std::getline(stream, name);
    if(name == CommandName::DrawCircleName){
        int radius;
        Point2D center;
        int thickness;
        Color color;
        stream >> radius >> center >> thickness >> color;
        dto = {center, radius, thickness, color};
    }else if(name == CommandName::DrawRectangleName){
        Point2D p1, p2;
        int thickness;
        Color color;
        stream >> p1 >> p2 >> thickness >> color;
        dto = {p1, p2, thickness, color};
    }else if(name == CommandName::DrawPolyLineName){
        std::list<Point2D> coords;
        int thickness;
        Color color;
        stream >> coords >> thickness >> color;
        dto = {coords, thickness, color};
    }else if(name == CommandName::DrawTextName){
        Point2D left_down;
        std::string text;
        int thickness;
        Color color;
        stream >> left_down >> text >> thickness >> color;
        dto = {left_down, text, thickness, color};
    }else if(name == CommandName::DrawImageName){
        Point2D up_left;
        Image to_draw;
        Image mask;
        char sep;
        stream >> up_left;
        stream.get();
        stream >> to_draw >> mask;//>> mask;
        //dto = {up_left, to_draw, mask};
        dto = {up_left, to_draw, mask};
    }else{

    }

    return stream;
}
