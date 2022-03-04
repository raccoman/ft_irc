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

	/*
	 * As requested from subject we set the socket to NON-BLOCKING mode
	 * allowing it to return any data that the system has in it's read buffer
	 * for that socket, but, it won't wait for that data.
	 */
	fcntl(sockfd, F_SETFL, O_NONBLOCK);

	if (sockfd < 0)
		throw std::runtime_error("Error while opening socket.");
	struct sockaddr_in serv_address = {};

	// Clear address structure, should prevent some segmentation fault and artifacts
	bzero((char *) &serv_address, sizeof(serv_address));

	serv_address.sin_family = AF_INET; // Set TCP IPV4 protocol (AF_INET6 for IPV6)

	// Automatically be filled with current host's IP address
	serv_address.sin_addr.s_addr = INADDR_ANY;

	// This convert unsigned short int to big-endian network byte order as expected from TCP protocol standards
	serv_address.sin_port = htons(std::stoi(_port));

	// Bind the socket to the current IP address on selected port
	if (bind(sockfd, (struct sockaddr *) &serv_address, sizeof(serv_address)) < 0)
		throw std::runtime_error("Error while binding socket.");

	// Let socket be able to listen for requests
	if (listen(sockfd, MAX_CONNECTIONS) < 0)
		throw std::runtime_error("Error while listening on socket.");

	return sockfd;
}
