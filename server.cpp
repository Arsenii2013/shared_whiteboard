#include "whiteboard.hpp"
#include "commands/command_dto.hpp"
#include "command_factory.hpp"
#include "service_command_factory.hpp"
#include "service_commands/service_command_name.hpp"
#include "network/network_server.hpp"

#include <thread>

int main(int argc, char** argv)
{
    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " port(0-65535)" << std::endl;
        return 0;
    }

    Whiteboard whiteboard{1000, 1000, {256, 256, 256}};
    NetworkServer server{static_cast<unsigned short>((std::stoi(argv[1])))};

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
        if(server.wait(10U)){
            if(server.accepted()){
                CommandDTO cmd{Point2D(0, 0), whiteboard.getBoard()};
                std::ostringstream data;
                data << cmd;
                server.sendToActive(data.str());
            }else if(server.received()){
                std::istringstream data(server.receivedData());

                std::string name;
                data >> name;
                data.seekg(0);
                if(name == ServiceCommandName::ServiceRedoName || name == ServiceCommandName::ServiceUndoName){
                    ServiceCommandDTO cmd;
                    data >> cmd;
                    ServiceCommandFactory::create(cmd)->execute(whiteboard);
                } else {
                    CommandDTO cmd;
                    data >> cmd;
                    whiteboard.add_and_redo(DrawCommandFactory::create(cmd));
                }
                data.seekg(0);
                server.sendToEachExceptActive(data.str());
            }
        }
    }

    return 0;
}