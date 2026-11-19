#include "Server.h"

void Server::init()
{
	if (listener == nullptr)
	{
		listener = std::make_unique<sf::TcpListener>();
	}
	//bind the listener to a port
	if (listener->listen(53000) != sf::Socket::Status::Done)
	{
		std::cout << "Couldn't bind listener to port 53000." << std::endl;
	}
}

void Server::run()
{
	while (running)
	{
		//Add new connection to the connections vector
		sf::TcpSocket& c_sock = *connections.emplace_back(std::make_unique<sf::TcpSocket>());

		// checks that the new connection finishes properly
		if (listener->accept(c_sock) != sf::Socket::Status::Done)
		{
			//Connection didn't finish properly remove it
			connections.pop_back();
			std::cout << "Connecion failed on server side" << std::endl;
			continue;
		}
		std::cout << "Client connected @ " << c_sock.getRemotePort() << std::endl;
	}
}

void Server::input()
{
	while (running)
	{
		std::string str;
		std::getline(std::cin, str);
		std::cin.clear();

		std::lock_guard<std::mutex> lck(mutex);
		for (std::unique_ptr<sf::TcpSocket>& connection : connections)
		{
			connection->send(reinterpret_cast<char*>(str.data()), str.length());
		}
	}
}