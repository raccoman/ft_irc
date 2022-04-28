#ifndef FT_IRC_CLIENT_HPP
# define FT_IRC_CLIENT_HPP

enum ClientState {
	HANDSHAKE,
	LOGIN,
	PLAY,
	DISCONNECTED
};

class Client;

#include <vector>
#include <string>
#include <sys/poll.h>
#include <sys/socket.h>
#include "utils.hpp"
#include "Channel.hpp"

class Client {

	typedef std::vector<pollfd>::iterator pollfds_iterator;

private:
	int _fd;
	std::string _hostname;
	int _port;

	std::string _nickname;
	std::string _username;
	std::string _realname;

	ClientState _state;

	Channel *_channel;

public:
	Client(int fd, const std::string &hostname, int port);

	~Client();

	int getFD() const { return _fd; };

	std::string getHostname() const { return _hostname; };

	int getPort() const { return _port; };

	bool isRegistered() const { return _state == ::PLAY; };

	std::string getNickname() const { return _nickname; };

	std::string getUsername() const { return _username; };

	std::string getRealName() const { return _realname; };

	std::string getPrefix() const;

	Channel *getChannel() const { return _channel; };

	void setNickname(const std::string &nickname) { _nickname = nickname; };

	void setUsername(const std::string &username) { _username = username; };

	void setRealName(const std::string &realname) { _realname = realname; };

	void setState(ClientState state) { _state = state; };

	void setChannel(Channel *channel) { _channel = channel; };

	void write(const std::string &message) const;

	void reply(const std::string &reply);

	void welcome();

	void join(Channel *channel);

	void leave();
};

#endif
