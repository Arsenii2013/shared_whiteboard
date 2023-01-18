#include "network_server.hpp"

bool NetworkServer::accept_and_add() {
    _clients.emplace_back();
    if (listener.accept(*_clients.rbegin()) == sf::Socket::Done)
    {
        selector.add(*_clients.rbegin());
        return true;
    }else{
        _clients.pop_back();
        return false;
    }
}

NetworkServer::NetworkServer(unsigned short port) {
    listener.listen(port);
    selector.add(listener);
}

bool NetworkServer::wait(unsigned int timeout_ms) {
    if (selector.wait(sf::milliseconds(timeout_ms))){
        if (selector.isReady(listener)){
            if(accept_and_add()){
                _recived = false;
                _accepted = true;
                _last_active = std::prev(_clients.end());
                return true;
            }else{
                return false;
            }
        }else{
            _last_active = std::find_if(_clients.begin(), _clients.end(),
                                        [this](sf::TcpSocket& client){return selector.isReady(client);});
            auto state = _last_active->receive(_received_data);
            if (state == sf::Socket::Done){
                _accepted = false;
                _recived = true;
                return true;
            }else if(state == sf::Socket::NotReady){
                return false;
            }else if(state == sf::Socket::Partial){
                return false;
            }else if(state == sf::Socket::Disconnected){
                selector.remove(*_last_active);
                _clients.erase(_last_active);
                return false;
            }else if(state == sf::Socket::Error){
                selector.remove(*_last_active);
                _last_active->disconnect();
                _clients.erase(_last_active);
                return false;
            }
        }
    }else{
        return false;
    }
}

void NetworkServer::sendToEachExceptActive(std::string data) {
    sf::Packet packet;
    packet << data;
    for(auto iter = _clients.begin(); iter != _clients.end(); iter++){
        if(iter != _last_active){
            iter->send(packet);
        }
    }
}

void NetworkServer::sendToEach(std::string data) {
    sf::Packet packet;
    packet << data;
    std::for_each(_clients.begin(), _clients.end(), [&packet](sf::TcpSocket& client){client.send(packet);});
}

void NetworkServer::sendToActive(std::string data) {
    sf::Packet packet;
    packet << data;
    _last_active->send(packet);
}

std::string NetworkServer::receivedData() {
    std::string tmp;
    _received_data >> tmp;
    return tmp;
}
