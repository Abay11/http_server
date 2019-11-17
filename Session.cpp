#include <string.h>

#include "Session.h"
#include "Logger.h"
#include "RequestHandler.h"
#include "Reply.h"

namespace ahttp
{
	unsigned short Session::nSessions = 0;

	Session::Session(ip::tcp::socket& s, std::shared_ptr<Logger> logger_ptr, std::string root)
		: socket_(std::move(s)),
		logger(logger_ptr)
	{
		logger->log_debug("A new session created. Total: " + std::to_string(++nSessions));

		request_handler = std::make_unique<RequestHandler>(logger_ptr, root);
	}
	
	Session::~Session()
	{
		logger->log_debug("Closing a session. Total: " + std::to_string(--nSessions));
	}

	void Session::do_read()
	{
		logger->log_debug("Session id:" + std::to_string(socket_.remote_endpoint().port())
			+ ". Waiting for a message...");

		auto self = shared_from_this();
		memset(buffer_, 0, MAX_SIZE);
		socket_.async_read_some(buffer(buffer_, MAX_SIZE),
			[this, self](std::error_code ec, auto bytes)
			{
				if (ec.value() == error::basic_errors::connection_reset)
				{
					logger->log_info("The slave has disconnected");
					return;
				}
				else if (ec)
				{
					logger->log_warn("An error occured during reading a msg from the slave #"
						+ std::to_string(socket_.remote_endpoint().port()));

					return;
				}

				auto reply = request_handler->handleRequest(buffer_);

				std::memset(buffer_, 0, MAX_SIZE);
				auto reply_str = reply.to_str();
				strcpy_s(buffer_, MAX_SIZE, reply_str.c_str());

				do_write();
			});
	}

	void Session::do_write()
	{
		logger->log_debug("Sending an reply to a slave# " + std::to_string(socket_.remote_endpoint().port()));
		auto self = shared_from_this();
		socket_.async_write_some(buffer(buffer_, strnlen(buffer_, MAX_SIZE)),
			[this, self](std::error_code ec, auto bytes)
			{
				if (ec)
				{
					logger->log_warn("An error occures during a writing...");
					return;
				}

				do_read();
			});
	}
}