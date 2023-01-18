#ifndef SHARED_WHITEBOARD_NEWORK_CLIENT_HPP
#define SHARED_WHITEBOARD_NEWORK_CLIENT_HPP
#include <SFML/Network.hpp>

class NetworkClient final{
    sf::TcpSocket socket;

public:
    NetworkClient(const std::string& address, unsigned short port);


    std::string receive();

    void send(std::string data);
};
#endif //SHARED_WHITEBOARD_NEWORK_CLIENT_HPP
