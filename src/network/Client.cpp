#include "Client.hpp"

Client::Client(int fd, pollfds_iterator pollfd, const std::string &hostname, int port)
	: _fd(fd), _pollfd(pollfd), _hostname(hostname), _port(port)
{
}

Client::~Client()
{
}