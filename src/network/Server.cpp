#include "network/Server.hpp"

Server::Server(const std::string &port, const std::string &password)
		: _running(1), _host("127.0.0.1"), _port(port), _password(password) {

	_sock = newSocket();
	_commandHandler = new CommandHandler(this);
}

Server::~Server() {
	delete _commandHandler;
}

void Server::start() {
	pollfd server_fd = {_sock, POLLIN, 0};
	_pollfds.push_back(server_fd);

	ft_log("Server listening...");

	while (_running) {

		// Loop waiting for incoming connects or for incoming data on any of the connected sockets.
		if (poll(_pollfds.begin().base(), _pollfds.size(), -1) < 0)
			throw std::runtime_error("Error while polling from fd.");

		// One or more descriptors are readable. Need to determine which ones they are.
		for (pollfds_iterator it = _pollfds.begin(); it != _pollfds.end(); it++) {

			if (it->revents == 0)
				continue;

			if ((it->revents & POLLHUP) == POLLHUP) {
				onClientDisconnect(it->fd);
				break;
			}

			if ((it->revents & POLLIN) == POLLIN) {

				if (it->fd == _sock) {
					onClientConnect();
					break;
				}

				onClientMessage(it->fd);
			}
		}
	}
}

int Server::newSocket() {

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw std::runtime_error("Error while opening socket.");

	// Forcefully attaching socket to the port
	int val = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
		throw std::runtime_error("Error while setting socket options.");

	/*
	 * As requested from subject we set the socket to NON-BLOCKING mode
	 * allowing it to return any data that the system has in it's read buffer
	 * for that socket, but, it won't wait for that data.
	 */
	if (fcntl(sockfd, F_SETFL, O_NONBLOCK) == -1) {
		throw std::runtime_error("Error while setting socket to NON-BLOCKING.");
	}

	struct sockaddr_in serv_address = {};

	// Clear address structure, should prevent some segmentation fault and artifacts
	bzero((char *) &serv_address, sizeof(serv_address));

	/*
	 * htons() convert unsigned short int to big-endian network byte order as expected from TCP protocol standards
	 */
	serv_address.sin_family = AF_INET;
	serv_address.sin_addr.s_addr = INADDR_ANY;
	serv_address.sin_port = htons(std::stoi(_port));

	// Bind the socket to the current IP address on selected port
	if (bind(sockfd, (struct sockaddr *) &serv_address, sizeof(serv_address)) < 0)
		throw std::runtime_error("Error while binding socket.");

	// Let socket be able to listen for requests
	if (listen(sockfd, MAX_CONNECTIONS) < 0)
		throw std::runtime_error("Error while listening on socket.");
	return sockfd;
}

std::string Server::readMessage(int fd) {

	std::string message;

	char buffer[100];
	bzero(buffer, 100);

	while (!std::strstr(buffer, "\r\n")) {
		bzero(buffer, 100);

		if (recv(fd, buffer, 100, 0) < 0) {
			if (errno != EWOULDBLOCK)
				throw std::runtime_error("Error while reading buffer from client.");
		}

		message.append(buffer);
	}

	return message;
}

void Server::onClientConnect() {
	int fd;
	sockaddr_in s_address = {};
	socklen_t s_size = sizeof(s_address);

	fd = accept(_sock, (sockaddr *) &s_address, &s_size);
	if (fd < 0)
		throw std::runtime_error("Error while accepting new client.");

	pollfd pollfd = {fd, POLLIN, 0};
	_pollfds.push_back(pollfd);

	Client *client = new Client(fd, _pollfds.end() - 1, inet_ntoa(s_address.sin_addr), ntohs(s_address.sin_port));
	_clients.insert(std::make_pair(fd, client));

	char message[1000];
	sprintf(message, "%s:%d has connected.", client->getHostname().c_str(), client->getPort());
	ft_log(message);
}

void Server::onClientDisconnect(int fd) {

	try {

		Client *client = _clients.at(fd);

		Channel *channel = client->getChannel();
		if (channel)
			channel->removeClient(client);

		char message[1000];
		sprintf(message, "%s:%d has disconnected.", client->getHostname().c_str(), client->getPort());
		ft_log(message);

		_pollfds.erase(client->getPollFD());
		_clients.erase(fd);
		delete client;
	}
	catch (const std::out_of_range &ex) {
	}

	if (_clients.empty())
		_running = 0;
}

void Server::onClientMessage(int fd) {
	clients_iterator it = _clients.find(fd);
	if (it == _clients.end()) return;

	_commandHandler->invoke(it->second, readMessage(fd));
}

Client *Server::getClient(const std::string &nickname) {
	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); it++) {
		if (!nickname.compare(it->second->getNickname()))
			return it->second;
	}
	return nullptr;
}

void Server::removeChannel(Channel *channel) {
	if (getChannel(channel->getName())) {
		_channels.erase(getChannelIterator(channel));
		delete channel;
	}
}

void Server::printChannels() {
	for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++) {
		ft_log((*it)->getName());
	}
} // DEBUG

std::vector<Channel *>::iterator Server::getChannelIterator(Channel *channel) {
	for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++) {
		if ((*it) == channel)
			return it;
	}
	return (_channels.end());
}

Channel *Server::getChannel(const std::string &name) {
	for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++) {
		if ((*it)->getName() == name) {
			return *it;
		}
	}
	return nullptr;
}

void Server::addChannel(const std::string &name, const std::string &password, Client *client) {
	Channel *channel = new Channel(name, password, client);
	_channels.push_back(channel);
}
