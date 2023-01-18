#include "image.hpp"

namespace{
    std::ostream& operator<<(std::ostream& stream,
                             const std::vector<uchar>& vect) {
        for (auto const &ch: vect) {
            stream << int(ch) << ' ';
        }
        return stream;
    }

    std::istream& operator>>(std::istream& stream,
                             std::vector<uchar>& vect) {
        std::string line;
        std::getline(stream, line);
        std::istringstream iss(line);
        vect.clear();

        int ch;
        while (iss >> ch){
            if(0 <= ch && ch <= 256) {
                vect.push_back(ch);
            }
        }

        return stream;
    }
}

std::ostream &operator<<(std::ostream &stream, const Image &i) {
    std::vector<uchar> buf;
    if(!i.getStorage().empty()) {
        cv::imencode(".jpg", i.getStorage(), buf);
    }
    stream << buf;
    return stream;
}

std::istream &operator>>(std::istream &stream, Image &i) {
    std::vector<uchar> buf;
    stream >> buf;
    if(!buf.empty()) {
        i = Image{cv::imdecode(buf, cv::ImreadModes::IMREAD_COLOR)};
    }
    return stream;
}

void Image::drawCircle(Point2D center, int radius, int thickness, Color color) {
    if(center.getX() - radius - thickness/2 < 0 || center.getX() + radius + thickness/2 > storage.cols ||
       center.getY() - radius - thickness/2 < 0 || center.getY() + radius + thickness/2 > storage.rows){
        return;
    }
    cv::circle(storage, cv::Point(center), radius, cv::Scalar(color), thickness);
}

void Image::drawRectangle(Point2D p1, Point2D p2, int thickness, Color color) {
    if(p1.getX() < 0 || p1.getX() > storage.cols || p1.getY() < 0 || p1.getY() > storage.rows){
        return;
    }
    if(p2.getX() < 0 || p2.getX() > storage.cols || p2.getY() < 0 || p2.getY() > storage.rows){
        return;
    }
    cv::rectangle(storage, cv::Point(p1), cv::Point(p2), cv::Scalar(color), thickness);
}

void Image::drawLine(Point2D p1, Point2D p2, int thickness, Color color) {
    if(p1.getX() < 0 || p1.getX() > storage.cols || p1.getY() < 0 || p1.getY() > storage.rows){
        return;
    }
    if(p2.getX() < 0 || p2.getX() > storage.cols || p2.getY() < 0 || p2.getY() > storage.rows){
        return;
    }
    cv::line(storage, cv::Point(p1), cv::Point(p2), cv::Scalar(color), thickness);
}

void Image::drawPolyLine(const std::list<Point2D> &coords, int thickness, Color color) {
    for(const auto& p: coords){
        if(p.getX() < 0 || p.getX() > storage.cols || p.getY() < 0 || p.getY() > storage.rows){
            return;
        }
    }
    std::vector<cv::Point> coords_converted;
    std::transform(coords.begin(), coords.end(), std::back_inserter(coords_converted), [](const Point2D& p){return cv::Point(p);});
    cv::polylines(storage, coords_converted, false, cv::Scalar(color), thickness);
}

namespace {
    double getTextScaleByHeight(const std::string& text, int search_height, double low, double high, double accuracy){
        int useless;
        while (std::abs(high - low) > accuracy) {
            double mid = low + (high - low) / 2;
            auto textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, mid, 1, &useless);

            if (std::abs(textSize.height - search_height) < accuracy) {
                return mid;
            }

            if (textSize.height < search_height) {
                low = mid;
            }else {
                high = mid;
            }
        }
    }
}

int Image::textWidthByHeight(const std::string &text, int search_height) {
    auto scale = getTextScaleByHeight(text, search_height, 0, 100, 0.05);
    int useless;
    return cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, scale, 1, &useless).width;
}

void Image::drawText(const std::string &text, Point2D left_down, int thickness, Color color) {
    if(left_down.getX() < 0 || left_down.getX() + Image::textWidthByHeight(text, thickness) + 1 > storage.cols ||
       left_down.getY() - thickness < 0 || left_down.getY() + thickness > storage.rows){
        return;
    }
    auto scale = getTextScaleByHeight(text, thickness, 0, 100, 0.05);
    cv::putText(storage, text, cv::Point(left_down), cv::FONT_HERSHEY_SIMPLEX,
                scale, cv::Scalar(color));
}

void Image::drawImage(Point2D up_left, const Image &to_draw) {
    if(up_left.getX() < 0 || up_left.getX() + to_draw.storage.cols > storage.cols ||
       up_left.getY() < 0 || up_left.getY() + to_draw.storage.rows > storage.rows){
        return;
    }
    if(to_draw.storage.empty()){
        return;
    }
    to_draw.storage.copyTo(storage({up_left.getY(), up_left.getY() + to_draw.getY()},
                                   {up_left.getX(), up_left.getX() + to_draw.getX()}));

}

void Image::drawImage(Point2D up_left, const Image &to_draw, const Image &mask) {
    if(up_left.getX() < 0 || up_left.getX() + to_draw.storage.cols > storage.cols ||
       up_left.getY() < 0 || up_left.getY() + to_draw.storage.rows > storage.rows){
        return;
    }
    if(to_draw.storage.empty()){
        return;
    }
    to_draw.storage.copyTo(storage({up_left.getY(), up_left.getY() + to_draw.getY()},
                                   {up_left.getX(), up_left.getX() + to_draw.getX()}),
                           mask.storage);

}

Image Image::subImage(Rectangle place) const {
    if(place.getXL() < 0 || place.getXR() > storage.cols ||
       place.getYU() < 0 || place.getYD() > storage.rows){
        return {};
    }
    return Image{storage({place.getYU(), place.getYD()},
                         {place.getXL(), place.getXR()}).clone()};
}

void Image::addImage(const Image &to_add, Image::ImageEdge edge) {
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
