#pragma once

#include "includes_all.h" 

namespace ahttp
{
	class Reply;
	class Logger;

	class RequestHandler
	{
	public:
		RequestHandler(std::shared_ptr<Logger> logger_ptr, std::string root);

		Reply handleRequest(const char* request);

	private:
		std::shared_ptr<Logger> logger;

		std::string root_directory = ".";
	};
}

