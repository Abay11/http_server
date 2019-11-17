#include "RequestHandler.h"

#include <sstream>

#include "Reply.h"
#include "Request.h"
#include "Logger.h"

namespace ahttp
{
	RequestHandler::RequestHandler(std::shared_ptr<Logger> logger_ptr, std::string root)
		:logger(logger_ptr),
		root_directory(root)
	{
	}

	Reply RequestHandler::handleRequest(const char* request)
	{
		std::stringstream ss(request);

		std::string method;
		std::string request_file;
		std::string http_version;

		ss >> method >> request_file >> http_version;

		Reply reply;
		if (method != "GET")
		{
			reply.code() = 501;
			
			logger->log_err("Can't handle request:\n");
			logger->log_err(request);
			
			return reply;
		}

		std::string full_path(root_directory);
		full_path += *request_file.rbegin() == '/' ? request_file += "index.html" : request_file;
		logger->log_debug(std::string("Requested file full path: ") + full_path);
		std::ifstream local_file(full_path);
		if (!local_file.is_open())
		{
			reply.code() = 404;
			
			return reply;
		}

		std::string in;
		std::string file_read_buffer;
		while (std::getline(local_file, in))
			file_read_buffer.append(in);

		reply.code() = 200;
		reply.set_content(std::move(file_read_buffer));

		return reply;
	}
}
