#include "ping.hpp"
#include "../handle/messegeHandler/additions.hpp"

<<<<<<< HEAD
#define PING_SECOND 10000

#define PING_SECOND_KICK 15000
=======
#define PING_SECOND 20

#define PING_SECOND_KICK 30
>>>>>>> ce1686cb7834138fe46a09d7ba7995d9554d3ec8

void	ping_client(std::map<int, User> &users, const int &id)
{
	std::vector< std::pair<int, std::string> >	messages;

	users.find(id)->second.setIsPing(true);
	messages.push_back(make_pair(id, "PING\n"));
	send_message(messages);
}

void	kick_client(std::map<int, User> &users, const int &id)
{
	std::vector< std::pair<int, std::string> >	messages;

	messages.push_back(make_pair(id, "QUIT"));
	send_message(messages);
}

bool	check_time(std::map<int, User> *clients_map, std::string pass,
				   std::map<int, string> &clients, fd_set &fds, map<int, string> &ip, std::vector<Channel> *channel)
{
	std::map<int, User>::iterator begin = clients_map->begin();
	std::map<int, User>::iterator end = clients_map->end();
	time_t	current_time = getCurrentTimeForUser();
	double	different;

	while (begin != end)
	{
		if (begin->second.getStatus() == -1)
			goto done;
		different = difftime(current_time, begin->second.getTimePing());
		if (different > PING_SECOND && !begin->second.getIsPing())
			ping_client(*clients_map, begin->first);
		else if (different > PING_SECOND_KICK)
		{
			send_message(handle_message("QUIT", begin->first, clients_map, pass, clients, fds,
										ip.find(begin->first)->second, channel));
			debug("[check_time] User was kick");
			return (true);
		}
	done:
		begin++;
	}
	return (false);
}
