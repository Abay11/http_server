#include "Logger.h"

#include <iostream>

#include <boost/date_time/local_time/local_date_time.hpp>

namespace ahttp
{
	enum class Logger::LOG_LEVEL{ ERROR, WARN, INFO, DEBUG };

	Logger::LOG_LEVEL Logger::llevel = Logger::LOG_LEVEL::DEBUG;
	
	Logger::Logger()
		:log_file(new std::ofstream())
	{
		log_file->open(LOG_FILE_NAME, std::ofstream::out | std::ofstream::app | std::ofstream::ate);
		if (!log_file->is_open())
			throw std::exception("Can't open a log file");

		//set formated date/time output
		using namespace boost::posix_time;
		time_facet* facet = new time_facet("[%Y-%b-%d %H:%M:%S]");
		log_file->imbue(std::locale(log_file->getloc(), facet));
	}

	Logger::Logger(Logger* other)
	{
		log_file = other->log_file;
	}

	Logger::~Logger()
	{
		log_file->close();
	}

	void Logger::setLogLevel(LOG_LEVEL new_value) noexcept
	{
		llevel = new_value;
	}
	void Logger::log(LOG_LEVEL lvl, const std::string& msg)
	{
		if (lvl > llevel) return;
		
		using namespace boost::posix_time;
		
		*log_file << second_clock::local_time()
			<< " " << lvl_to_string(lvl) << ": "
			<< msg << std::endl;
	}
	void Logger::log_err(const std::string& msg)
	{
		log(LOG_LEVEL::ERROR, msg);
	}
	void Logger::log_warn(const std::string& msg)
	{
		log(LOG_LEVEL::WARN, msg);
	}
	void Logger::log_info(const std::string& msg)
	{
		log(LOG_LEVEL::INFO, msg);
	}
	void Logger::log_debug(const std::string& msg)
	{
		log(LOG_LEVEL::DEBUG, msg);
	}

	Logger* Logger::getLogger()
	{
		return this;
	}
	std::string Logger::lvl_to_string(LOG_LEVEL lvl)
	{
		switch (lvl)
		{
		case LOG_LEVEL::DEBUG: return "DEBUG";
		case LOG_LEVEL::ERROR: return "ERROR";
		case LOG_LEVEL::INFO: return "INFO";
		case LOG_LEVEL::WARN: return "WARN";
		}
	}
}