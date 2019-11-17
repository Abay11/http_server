#pragma once

#include "includes_all.h"

namespace ahttp
{
	using namespace boost::asio;

	class Logger;

	class Server
	{
	public:
		Server(const std::string& address, int port, std::string root_directory);

		~Server();

		void start();

		io_context& get_executor();

	private:
		void do_accept();

	private:
		io_context context_;
		ip::tcp::acceptor acceptor_;

		std::shared_ptr<Logger> logger;

		std::string root_directory;
	};
}
