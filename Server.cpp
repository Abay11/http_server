#include "Server.h"

#include "includes_all.h"
#include "Session.h"
#include "Logger.h"

namespace ahttp
{
	Server::Server(const std::string& address, int port, std::string root)
		: context_(),
		acceptor_(context_),
		logger(std::make_shared<Logger>()),
		root_directory(root)
	{
		ip::tcp::endpoint ep(ip::address_v4::from_string(address), port);
		//ip::tcp::endpoint ep(ip::tcp::v4(), port);
		acceptor_.open(ep.protocol());
		acceptor_.bind(ep);
		acceptor_.listen();

		logger->log_info("Server run");
	}

	Server::~Server()
	{
		logger->log_info("Server stopped");
	}

	void Server::start()
	{
		logger->log_info("Start the Server");
		logger->log_debug("Binding address: " + acceptor_.local_endpoint().address().to_string());
		logger->log_debug("Listening port: " + std::to_string(acceptor_.local_endpoint().port()));
		
		do_accept();
	
		context_.run();
	}

	io_context& Server::get_executor()
	{
		return context_;
	}

	void ahttp::Server::do_accept()
	{
		logger->log_debug("Start waiting for a new slave");

		acceptor_.async_accept([this](std::error_code ec, ip::tcp::socket s)
			{
				if (ec)
				{
					logger->log_err("An error occures during accepting a slave");
				}
				else
				{
					logger->log_info("New connection");
					logger->log_debug("Accept a new slave #" + std::to_string(s.remote_endpoint().port()));
					std::make_shared<Session>(s, logger, root_directory)->do_read();
				}

				do_accept();
			}
		);
	}
}
