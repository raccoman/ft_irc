#include "Client.hpp"

Client::Client(int fd, const std::string &hostname, int port)
	: _fd(fd),  _hostname(hostname), _port(port) {

}

Client::~Client() {
}