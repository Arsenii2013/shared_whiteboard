#ifndef SHARED_WHITEBOARD_UTILITIES_HPP
#define SHARED_WHITEBOARD_UTILITIES_HPP
#include <opencv2/opencv.hpp>

class Color final{
    size_t r{0U}, g{0U}, b{0U};

public:
    Color() = default;

    Color(size_t r, size_t g, size_t b) : r(r), g(g), b(b) {
        if(r > 256 || g > 256 || b > 256){
            throw std::invalid_argument("each component of color(r, g ,b) must be <= 256");
        }
    }

    explicit operator cv::Scalar() const{
        return {double(r), double(g), double(b)};
    }

    [[nodiscard]] size_t getR() const {
        return r;
    }

    void setR(size_t _r) {
        Color::r = _r;
    }

    [[nodiscard]] size_t getG() const {
        return g;
    }

    void setG(size_t _g) {
        Color::g = _g;
    }

    [[nodiscard]] size_t getB() const {
        return b;
    }

    void setB(size_t _b) {
        Color::b = _b;
    }
};

class Point2D final{
    int x{0}, y{0};

public:
    Point2D() = default;
    Point2D(int x, int y) : x(x), y(y) {}

    explicit operator cv::Point() const{
        return {x, y};
    }

    [[nodiscard]] int getX() const {
        return x;
    }

    void setX(int _x) {
        Point2D::x = _x;
    }

    [[nodiscard]] int getY() const {
        return y;
    }

    void setY(int _y) {
        Point2D::y = _y;
    }
};

class Rectangle final{
    int x_l{0}, x_r{1};
    int y_u{0}, y_d{1};

public:
    Rectangle() = default;
    Rectangle(int xL, int xR, int yU, int yD) : x_l(xL), x_r(xR), y_u(yU), y_d(yD) {
        if(x_l > x_r || y_u > y_d){
            throw std::invalid_argument("upper left corner below or to the right of the lower right corner");
        }
    }

    [[nodiscard]] bool in(int x, int y) const{
        return x_l < x && x < x_r && y_u < y && y < y_d;
    };

    [[nodiscard]] int getXL() const {
        return x_l;
    }

    void setXL(int xL) {
        x_l = xL;
        if(x_l > x_r || y_u > y_d){
            throw std::invalid_argument("upper left corner below or to the right of the lower right corner");
        }
    }

    [[nodiscard]] int getXR() const {
        return x_r;
    }

    void setXR(int xR) {
        x_r = xR;
        if(x_l > x_r || y_u > y_d){
            throw std::invalid_argument("upper left corner below or to the right of the lower right corner");
        }
    }

    [[nodiscard]] int getYU() const {
        return y_u;
    }

    void setYU(int yU) {
        y_u = yU;
        if(x_l > x_r || y_u > y_d){
            throw std::invalid_argument("upper left corner below or to the right of the lower right corner");
        }
    }

    [[nodiscard]] int getYD() const {
        return y_d;
    }

    void setYD(int yD) {
        y_d = yD;
        if(x_l > x_r || y_u > y_d){
            throw std::invalid_argument("upper left corner below or to the right of the lower right corner");
        }
    }
};

enum class MouseEvent{
    ERROR,
    MOVE,
    LDOWN,
    LUP,
    RDOWN,
    RUP,
    //LCLICK,
    //RCLICK,
};

class ASCIIKey{
    int key{};
public:

    explicit ASCIIKey(int key): key(key){};

    explicit operator int() const{
        return key;
    }
};


#endif //SHARED_WHITEBOARD_UTILITIES_HPP
