#pragma once

#include <string>
#include <fstream>

namespace ahttp
{

	class Logger
	{
		enum class LOG_LEVEL;

		const char* LOG_FILE_NAME = "server.log";

	public:
		Logger();
		
		Logger(Logger*);
		
		~Logger();
		
		void setLogLevel(LOG_LEVEL) noexcept;

		void log(LOG_LEVEL, const std::string&);
		
		void log_err(const std::string&);
		
		void log_warn(const std::string&);
		
		void log_info(const std::string&);
		
		void log_debug(const std::string&);
		
		Logger* getLogger();
		
		std::string lvl_to_string(LOG_LEVEL lvl);

	private:
		static LOG_LEVEL llevel;

		std::ofstream* log_file;
	};
}

