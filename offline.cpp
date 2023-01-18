#include <opencv2/opencv.hpp>
#include <thread>

#include "user_editor.hpp"

MouseEvent castToMouseEvent(int event){
    if(event == cv::MouseEventTypes::EVENT_MOUSEMOVE){
        return MouseEvent::MOVE;
    }else if(event == cv::MouseEventTypes::EVENT_LBUTTONUP){
        return MouseEvent::LUP;
    }else if(event == cv::MouseEventTypes::EVENT_RBUTTONUP){
        return MouseEvent::RUP;
    }else if(event == cv::MouseEventTypes::EVENT_LBUTTONDOWN){
        return MouseEvent::LDOWN;
    }else if(event == cv::MouseEventTypes::EVENT_RBUTTONDOWN){
        return MouseEvent::RDOWN;
    }else {
        return MouseEvent::ERROR;
    }
}

class OpenCVCallback final{
    UserEditor& editor;

    void processMouseEvent(int event, int x, int y){
        editor.processMouseEvent(castToMouseEvent(event), x, y);
    }

public:
    explicit OpenCVCallback(UserEditor &editor) : editor(editor) {}

    static void mouseCallback(int event, int x, int y, int flags, void* userdata){
        ((OpenCVCallback*)userdata)->processMouseEvent(event, x, y);
    }
};


int main(int argc, char** argv)
{
    cv::namedWindow("Whiteboard", cv::WINDOW_AUTOSIZE );

    Settings settings{"../resources", {"Empty",
                                     ToolName::DrawPrefix + ToolName::Circle,
                                     ToolName::DrawPrefix + ToolName::Rectangle,
                                     ToolName::DrawPrefix + ToolName::PolyLine,
                                     ToolName::DrawPrefix + ToolName::Text,
                                     ToolName::ToolPrefix + ToolName::Thickness,
                                     ToolName::ToolPrefix + ToolName::Color,
                                     ToolName::ServicePrefix + ToolName::Undo,
                                     ToolName::ServicePrefix + ToolName::Redo}};

    UserEditor editor{settings};
    editor.setDrawFunction([](const Image& image){cv::imshow("Whiteboard", image.getStorage());});
    editor.setSendCommand([](const CommandDTO&){});
    editor.setSendServiceCommand([](const ServiceCommandDTO&){});

    OpenCVCallback call{editor};
    cv::setMouseCallback("Whiteboard", OpenCVCallback::mouseCallback, &call);

    std::atomic<bool> running{true};
    std::jthread cin_thread{[&running](){
        std::string line;
        while (std::getline(std::cin, line)){
            if(line == "q" || line == "quit"){
                running = false;
            }
        }
        running = false;
    }};
    cin_thread.detach();
    while (running) {
        auto key = ASCIIKey(cv::waitKey(10));
        editor.processKey(key);
    }

    return 0;
}