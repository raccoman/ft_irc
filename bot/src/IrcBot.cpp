#include "IrcBot.hpp"

IrcBot::IrcBot(const std::string &host, const std::string &port, const std::string &password) :
		_running(1), _host(host), _port(port), _password(password) {
	_sock = newSocket();
}

IrcBot::~IrcBot() {
}

int IrcBot::newSocket() {

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		throw std::runtime_error("Error while opening socket.");

	struct sockaddr_in serv_address = {};

	// Clear address structure, should prevent some segmentation fault and artifacts
	bzero((char *) &serv_address, sizeof(serv_address));

	/*
	 * htons() convert unsigned short int to big-endian network byte order as expected from TCP protocol standards
	 */
	serv_address.sin_family = AF_INET;
	serv_address.sin_addr.s_addr = inet_addr(_host.c_str());
	serv_address.sin_port = htons(std::stoi(_port));

	// Bind the socket to the current IP address on selected port
	if (connect(sockfd, (struct sockaddr *) &serv_address, sizeof(serv_address)) < 0)
		throw std::runtime_error("Error while connecting to host.");

	return sockfd;
}

void IrcBot::flush(const std::string &message) {
	std::string normalized = message + "\r\n";
	write(_sock, normalized.c_str(), normalized.size());
}

void IrcBot::receiver(IrcBot *instance) {
	char buffer[256];
	int length;

	while ((length = recv(instance->_sock, buffer, 256, 0)) > 0) {
		buffer[length] = 0;
		instance->onMessageReceived(std::string(buffer, length));
	}

	close(instance->_sock);
	instance->_running = 0;
}

void IrcBot::authenticate(const std::string &as) {
	flush("PASS " + _password);
	flush("NICK " + as);
	flush("USER ircbot 0 * :42's ircbot");
}

void IrcBot::start() {
	authenticate("Siri");

	//Listen for incoming messages from server
	std::thread t(IrcBot::receiver, this);
	t.detach();

	std::string input;
	getline(std::cin, input);
	while (input != "exit") {
		getline(std::cin, input);
	}

	flush("QUIT :Bye, bye...");

	close(_sock);
	std::cout << "Bye, bye..." << std::endl;
}

void IrcBot::onMessageReceived(const std::string &message) {
	std::cout << message;
}