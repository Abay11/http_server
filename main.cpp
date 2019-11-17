#include <cstdlib>
#include <iostream>
#include <memory>
#include <cstring>
#include <utility>

#include <boost/asio.hpp>

#include "Server.h"

int main(int argc, char* argv[])
{
	using namespace boost::asio;

	std::string address = "0.0.0.0";
	int port = 8080;
	std::string root = ".";

	if (argc == 8)
	{
		address = argv[3];
		port = atoi(argv[5]);
		root = argv[7];
	}
	else
	{
		//do log: can't parse args - I KNOW I KNOW NEED TO IMPL CORRECT ARGS PARSER
		//expected next format: final -h <ip> -p <port> -d <directory>
	}

	try
	{
		ahttp::Server server_(address, port, root);

		server_.start();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}