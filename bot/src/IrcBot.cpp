#include "IrcBot.hpp"

IrcBot::IrcBot(const std::string &host, const std::string &port, const std::string &password) :
		_host(host), _port(port), _password(password) {
	_sock = newSocket();
	std::srand(getpid() * std::time(NULL));
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

	std::cout << CC_RED << "[-] " << message << std::endl;

	std::string normalized = message + "\r\n";
	send(_sock, normalized.c_str(), normalized.size(), 0);
}

void IrcBot::receiver(IrcBot *instance) {
	char buffer[256];
	int length;

	while ((length = recv(instance->_sock, buffer, 256, 0)) > 0) {
		buffer[length] = 0;
		instance->onMessageReceived(std::string(buffer, length));
	}

	close(instance->_sock);
}

void IrcBot::authenticate(const std::string &as) {
	flush("PASS " + _password);
	flush("NICK " + as);
	flush("USER ircbot 0 * :42 ft_irc's bot");
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

	// TCP Stream is non-blocking, closing socket will truncate QUIT message sent from client
	// Maybe implement some sort of waiting???
	// close(_sock);
}

void IrcBot::sendPrivMsg(const std::string &source, const std::string &message) {
	flush("PRIVMSG " + source + " :" + message);
}

void IrcBot::sendFile(const std::string &source, const std::string &filename, const std::string &as) {

	char buffer[256];
	FILE *fd = fopen(filename.c_str(), "rb");

	while (!feof(fd)) {
		int size = fread(&buffer, 1, 256, fd);
		if (size < 0)
			break;

		_buffer.append(buffer, size);
	}

	fclose(fd);

	std::thread sender([this] {

		int server_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (server_fd < 0)
			throw std::runtime_error("Error while opening socket.");

		// Forcefully attaching socket to the port
		int val = 1;
		if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
			throw std::runtime_error("Error while setting socket options.");

		struct sockaddr_in serv_address = {};
		int serv_address_len = sizeof(serv_address);

		// Clear address structure, should prevent some segmentation fault and artifacts
		bzero((char *) &serv_address, serv_address_len);

		/*
		 * htons() convert unsigned short int to big-endian network byte order as expected from TCP protocol standards
		 */
		serv_address.sin_family = AF_INET;
		serv_address.sin_addr.s_addr = INADDR_ANY;
		serv_address.sin_port = htons(1096);

		// Bind the socket to the current IP address on selected port
		if (bind(server_fd, (struct sockaddr *) &serv_address, serv_address_len) < 0)
			throw std::runtime_error("Error while binding socket.");

		// Let socket be able to listen for requests
		if (listen(server_fd, 1) < 0)
			throw std::runtime_error("Error while listening on socket.");

		int client_fd = accept(server_fd, (struct sockaddr *) &serv_address, (socklen_t *) &serv_address_len);
		if (client_fd < 0) {
			close(server_fd);
			_buffer.clear();
			return;
		}

		send(client_fd, _buffer.c_str(), _buffer.size(), 0);

		close(client_fd);
		close(server_fd);
		_buffer.clear();
	});
	sender.detach();

	flush("PRIVMSG " + source + " :" + '\x01' + "DCC SEND " + as + " 0 1096 " + std::to_string(_buffer.size()) +
		  '\x01');
}

void IrcBot::onMessageReceived(const std::string &message) {

	ft::vec_string args = ft::split(message);

	if (args.size() < 2)
		return;

	std::string source = args.at(0);
	std::string type = args.at(1);

	if (atoi(type.c_str()) > 0) {

		if (args.size() < 3)
			return;

		onNumericReply(source, type, ft::vec_string(args.begin() + 3, args.end()));
		return;
	}

	onCommandReply(source, type, ft::vec_string(args.begin() + 2, args.end()));
}

void IrcBot::onNumericReply(const std::string &source, const std::string &reply, std::vector<std::string> args) {
	(void) source;
	std::cout << CC_GRN << "[+] (" << reply << ") " << ft::join(" ", args) << std::endl;
}

void IrcBot::onCommandReply(const std::string &source, const std::string &cmd, std::vector<std::string> args) {

	std::string nickname = source;
	std::string::size_type pos = nickname.find('!');
	if (pos != std::string::npos)
		nickname = nickname.substr(1, pos - 1);

	std::cout << CC_GRN << "[+] (" << nickname << ") " << cmd << " " << ft::join(" ", args) << std::endl;

	if (cmd == "PRIVMSG") {

		if (args.size() >= 2 && args.at(1).substr(1) == "ROLLDICE") {
			sendPrivMsg(nickname,
						ft::string_format("http://roll.diceapi.com/images/poorly-drawn/d6/%d.png", (rand() % 6) + 1));
			return;
		}

		if (args.size() >= 2 && args.at(1).substr(1) == "DRAWCARD") {

			std::string cards = "234567890JQKA";
			std::string suits = "HCSD";

			sendPrivMsg(nickname,
						ft::string_format("https://deckofcardsapi.com/static/img/%c%c.png",
										  cards[rand() % 13],
										  suits[rand() % 4]));
			return;
		}

		if (args.size() >= 2 && args.at(1).substr(1) == "WEATHER") {
			sendPrivMsg(nickname, "https://wttr.in/_m0_lang=it.png");
			return;
		}

		if (args.size() >= 2 && args.at(1).substr(1) == "EXPLOIT") {
			sendFile(nickname, "./durex.txt", "durex.txt");
			return;
		}

		sendPrivMsg(nickname, "Ma succhiamelo!");
		return;
	}

}