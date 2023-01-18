#include <opencv2/opencv.hpp>
#include <thread>

#include "user_editor.hpp"
#include "command_factory.hpp"
#include "service_command_factory.hpp"
#include "service_commands/service_command_name.hpp"
#include "network/nework_client.hpp"

//TODO improve data validation
//TODO fix undo/redo behavioral
// Проблема в том что при коннекте отправляем изображение - и это одна команда
// 1) передавать все команды, и пускай доска раз в 100 команд очищает стеки и меняет их на одну команду
// 2) механизм, что каждый юзер может отменять только сви команды - в каждой доске для каждого узера свои стеки

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
    if(argc != 3){
        std::cout << "Usage: " << argv[0] << " remote_host remote_port(0-65535)" << std::endl;
        return 0;
    }
    NetworkClient client(argv[1], std::stoi(argv[2]));

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

    editor.setSendCommand([&client](const CommandDTO& cmd){
        std::ostringstream data;
        data << cmd;
        client.send(data.str());
    });

    editor.setSendServiceCommand([&client](const ServiceCommandDTO& cmd){
        std::ostringstream data;
        data << cmd;
        client.send(data.str());
    });


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
        int int_key = cv::waitKeyEx(100);
        if(int_key > 0) {
            auto key = ASCIIKey(int_key);
            editor.processKey(key);
        }

        std::string data;
        if (!(data = client.receive()).empty()){
            std::istringstream data_iss(std::move(data));

            std::string name;
            data_iss >> name;
            data_iss.seekg(0);
            if(name == ServiceCommandName::ServiceRedoName || name == ServiceCommandName::ServiceUndoName){
                ServiceCommandDTO cmd;
                data_iss >> cmd;
                editor.processExternal(cmd);
            } else {
                CommandDTO cmd;
                data_iss >> cmd;
                editor.processExternal(cmd);
            }
        }
    }

    return 0;
}