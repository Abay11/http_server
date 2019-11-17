#pragma once

#include "includes_all.h"

namespace ahttp
{
	using namespace boost::asio;

	class Logger;
	class RequestHandler;

	class Session : public std::enable_shared_from_this<Session>
	{
	private:
		static unsigned short nSessions;

	public:
		Session(ip::tcp::socket& s, std::shared_ptr<Logger> logger, std::string root);

		~Session();

		void do_read();

		void do_write();

	private:
		ip::tcp::socket socket_;
		
		//don't now what exactly happen
		//in the cases when the requested file has larger size
		//the declared size
		enum { MAX_SIZE = 4096 };
		
		//buffer uses at first read request
		//after parsing and processing request 
		//buffer filled with reply content
		char buffer_[MAX_SIZE];

		std::shared_ptr<Logger> logger;
		std::unique_ptr<RequestHandler> request_handler;
	};
}
