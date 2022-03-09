#include "commands/Command.hpp"

JoinCommand::JoinCommand(Server *server) : Command(server) {}

JoinCommand::~JoinCommand() {}

void JoinCommand::execute(Client *client, std::vector<std::string> arguments) {

}