#ifndef COMMAND_HPP
#define COMMAND_HPP

class Command;

#include <string>
#include "network/Client.hpp"
#include "network/Server.hpp"

class Command
{

protected:
    Server *_server;

public:
    Command(Server *server) : _server(server){};
    virtual ~Command(){};

    virtual void execute(Client *client, std::vector<std::string> arguments) = 0;
};

class JoinCommand : public Command
{
public:
	JoinCommand(Server *server);
	~JoinCommand();

	void execute(Client *client, std::vector<std::string> arguments);
};

class UserCommand : public Command
{
public:
    UserCommand(Server *server);
    ~UserCommand();

    void execute(Client *client, std::vector<std::string> arguments);
};

class NickCommand : public Command
{
public:
    NickCommand(Server *server);
    ~NickCommand();

    void execute(Client *client, std::vector<std::string> arguments);
};

class PassCommand : public Command
{
public:
    PassCommand(Server *server);
    ~PassCommand();

    void execute(Client *client, std::vector<std::string> arguments);
};

#endif // COMMAND_HPP