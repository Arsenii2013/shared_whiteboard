#ifndef SHARED_WHITEBOARD_IMAGE_HPP
#define SHARED_WHITEBOARD_IMAGE_HPP
#include <opencv2/opencv.hpp>
#include <utility>
#include <filesystem>
#include "utilities.hpp"

//о библиотеке для графики(opencv) должна занть только она
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

    void drawCircle(Point2D center, int radius, int thickness, Color color){
        cv::circle(storage, cv::Point(center), radius, cv::Scalar(color), thickness);
    }

    void drawRectangle(Point2D p1, Point2D p2, int thickness, Color color){
        cv::rectangle(storage, cv::Point(p1), cv::Point(p2), cv::Scalar(color), thickness);
    }

    void drawLine(Point2D p1, Point2D p2, int thickness, Color color){
        cv::line(storage, cv::Point(p1), cv::Point(p2), cv::Scalar(color), thickness);
    }

    void drawPolyLine(const std::list<Point2D>& coords, int thickness, Color color){
        std::vector<cv::Point> coords_converted;
        std::transform(coords.begin(), coords.end(), std::back_inserter(coords_converted), [](const Point2D& p){return cv::Point(p);});
        cv::polylines(storage, coords_converted, false, cv::Scalar(color), thickness);
    }

    void drawImage(Point2D up_left, const Image& to_draw){
        to_draw.storage.copyTo(storage({up_left.getY(), up_left.getY() + to_draw.getY()},
                                           {up_left.getX(), up_left.getX() + to_draw.getX()}));

    }

    void drawImage(Point2D up_left, const Image& to_draw, const Image& mask){
        to_draw.storage.copyTo(storage({up_left.getY(), up_left.getY() + to_draw.getY()},
                                           {up_left.getX(), up_left.getX() + to_draw.getX()}),
                               mask.storage);

    }

    Image subImage(Rectangle place){
        return Image{storage({place.getYU(), place.getYD()},
                                    {place.getXL(), place.getXR()}).clone()};
    }

    enum class ImageEdge{
        Up,
        Down,
        Right,
        Left,
    };

    void addImage(const Image& to_add, ImageEdge edge){
        if(storage.empty()){
            storage = to_add.storage;
            return;
        }
        if(edge == ImageEdge::Up){
            cv::Mat new_image{getY() + to_add.getY(), std::max(getX(), to_add.getX()),
                              CV_8UC3, {256, 256 ,256}};

            to_add.storage.copyTo(new_image({0, to_add.getY()},
                                                {0, to_add.getX()}));

            storage.copyTo(new_image({to_add.getY(), to_add.getY() + getY()},
                                        {0, getX()}));
            storage = std::move(new_image);
        }else if(edge == ImageEdge::Down){
            cv::Mat new_image{getY() + to_add.getY(), std::max(getX(), to_add.getX()),
                              CV_8UC3, {256, 256 ,256}};

            storage.copyTo(new_image({0, getY()},
                                        {0, getX()}));

            to_add.storage.copyTo(new_image({getY(), getY() + to_add.getY()},
                                                {0, to_add.getX()}));
            storage = std::move(new_image);
        }else if(edge == ImageEdge::Left){
            cv::Mat new_image{std::max(getY(), to_add.getY()), getX() + to_add.getX(),
                              CV_8UC3, {256, 256 ,256}};

            to_add.storage.copyTo(new_image({0, to_add.getY()},
                                                {0, to_add.getX()}));

            storage.copyTo(new_image({0, getY()},
                                        {to_add.getX(), to_add.getX() + getX()}));
            storage = std::move(new_image);
        }else if(edge == ImageEdge::Right){
            cv::Mat new_image{std::max(getY(), to_add.getY()), getX() + to_add.getX(),
                              CV_8UC3, {256, 256 ,256}};

            storage.copyTo(new_image({0, getY()},
                                         {0,  getX()}));

            to_add.storage.copyTo(new_image({0, to_add.getY()},
                                                {getX(),  getX() + to_add.getX()}));
            storage = std::move(new_image);
        }
    }

    [[nodiscard]] const cv::Mat &getStorage() const {
        return storage;
    }
};
#endif //SHARED_WHITEBOARD_IMAGE_HPP
