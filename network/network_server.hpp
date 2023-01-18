#ifndef SHARED_WHITEBOARD_NETWORK_SERVER_HPP
#define SHARED_WHITEBOARD_NETWORK_SERVER_HPP
#include <SFML/Network.hpp>
#include <list>
#include <functional>
#include <sstream>

class NetworkServer final{
    sf::TcpListener listener;
    std::list<sf::TcpSocket> _clients;
    sf::SocketSelector selector;

    bool _accepted{false};
    bool _recived{false};
    std::list<sf::TcpSocket>::iterator _last_active;
    sf::Packet _received_data;

    bool accept_and_add();
public:
    explicit NetworkServer(unsigned short port);

    bool wait(unsigned int timeout = 0U);

    [[nodiscard]] bool accepted() const{ return  _accepted; };
    [[nodiscard]] bool received() const{ return  _recived; };

    [[nodiscard]] std::string receivedData();

    void sendToActive(std::string data);

    void sendToEachExceptActive(std::string data);

    void sendToEach(std::string data);
};
#endif //SHARED_WHITEBOARD_NETWORK_SERVER_HPP
