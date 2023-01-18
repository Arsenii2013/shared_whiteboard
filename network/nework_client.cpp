#include <sstream>
#include "nework_client.hpp"

NetworkClient::NetworkClient(const std::string &address, unsigned short port) {
    if (socket.connect(address, port) != sf::Socket::Done)
    {
        throw std::runtime_error("cant connect to remote host");
    }
    socket.setBlocking(false);
}

std::string NetworkClient::receive() {
    sf::Packet packet;
    sf::Socket::Status result;
    while((result = socket.receive(packet)) == sf::Socket::Partial);
    if(result == sf::Socket::Disconnected || result == sf::Socket::Error){
        throw std::runtime_error("disconnect from remote host");
    }
    std::string data;
    packet >> data;
    return data;
}

void NetworkClient::send(std::string data) {
    sf::Packet packet;
    packet << data;
    sf::Socket::Status result;
    while((result = socket.send(packet)) == sf::Socket::Partial);
    if(result == sf::Socket::Disconnected || result == sf::Socket::Error){
        throw std::runtime_error("disconnect from remote host");
    }
}
