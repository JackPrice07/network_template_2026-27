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

	running = true;
	std::thread input_thread([&] {input();});
	input_thread.detach();

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

void Server::listen(sf::TcpSocket& c_socket)
{
	//keep socket active until connection is no longer valid
	bool continue_receiving = true;

	char data[1028];
	std::size_t received;

	while (continue_receiving)
	{
		sf::Socket::Status status = c_socket.receive(data, 1028, received);

		if (status == sf::Socket::Status::Disconnected)
		{
			continue_receiving = false;
			std::cout << "Disconnected" << std::endl;
		}

		if (received < 1028) { data[received] = '\0'; }
		relay(data, c_socket);

		std::cout << reinterpret_cast<char*>(data) << std::endl;
	}

	c_socket.disconnect();
}
