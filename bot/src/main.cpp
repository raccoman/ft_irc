#include "IrcBot.hpp"

int main(int argc, char **argv) {

	try {

		if (argc < 3) {
			throw std::runtime_error("Usage: ./ircbot <host> <port> [password]");
		}

		IrcBot bot(argv[1], argv[2], argc == 4 ? argv[3] : "");
		bot.start();
		return 0;
	}
	catch (const std::exception &ex) {
		std::cerr << ex.what() << std::endl;
	}
}