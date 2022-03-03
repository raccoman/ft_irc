#include "Server.hpp"

Server::Server(const std::string &port, const std::string &password)
	: _host("127.0.0.1"), _port(port), _password(password) {

	_sock = newSocket();
}

Server::~Server() {

}

void Server::start() {

}


int Server::newSocket() {

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw std::runtime_error("Error while opening socket.");

	struct sockaddr_in serv_address = {};
	bzero((char *) &serv_address, sizeof(serv_address));

	serv_address.sin_family = AF_INET;
	serv_address.sin_addr.s_addr = INADDR_ANY;
	serv_address.sin_port = htons(std::stoi(_port));

	if (bind(sockfd, (struct sockaddr *) &serv_address, sizeof(serv_address)) < 0)
		throw std::runtime_error("Error while binding socket.");

	if (listen(sockfd, MAX_CONNECTIONS) < 0)
		throw std::runtime_error("Error while listening on socket.");

	return sockfd;
}
