#ifndef SHARED_WHITEBOARD_IMAGE_HPP
#define SHARED_WHITEBOARD_IMAGE_HPP
#include <opencv2/opencv.hpp>
#include <filesystem>
#include "utilities.hpp"

class Image final{
    cv::Mat storage{};
public:
    Image() = default;
    Image(int x, int y): storage(cv::Mat{y, x, CV_8UC3}){}
    Image(int x, int y, Color color): storage(cv::Mat{y, x, CV_8UC3, cv::Scalar(color)}){}
    explicit Image(const std::filesystem::path& file) : storage(cv::imread(file)) {}
    explicit Image(cv::Mat image) : storage(std::move(image)) {}

    [[nodiscard]] int getX() const{
        return storage.cols;
    }

    [[nodiscard]] int getY() const{
        return storage.rows;
    }

    [[nodiscard]] bool empty() const{
        return storage.empty();
    }

    void drawCircle(Point2D center, int radius, int thickness, Color color);

    void drawRectangle(Point2D p1, Point2D p2, int thickness, Color color);

    void drawLine(Point2D p1, Point2D p2, int thickness, Color color);

    void drawPolyLine(const std::list<Point2D>& coords, int thickness, Color color);

    static int textWidthByHeight(const std::string& text, int search_height);

    void drawText(const std::string& text, Point2D left_down, int thickness, Color color);

    void drawImage(Point2D up_left, const Image& to_draw);

    void drawImage(Point2D up_left, const Image& to_draw, const Image& mask);

    [[nodiscard]] Image subImage(Rectangle place) const;

    enum class ImageEdge{
        Up,
        Down,
        Right,
        Left,
    };

    void addImage(const Image& to_add, ImageEdge edge);

    [[nodiscard]] const cv::Mat &getStorage() const {
        return storage;
    }
};

std::ostream& operator<<(std::ostream& stream,
                         const Image& i);

std::istream& operator>>(std::istream& stream,
                         Image& i);
#endif //SHARED_WHITEBOARD_IMAGE_HPP
