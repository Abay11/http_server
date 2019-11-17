#pragma once

#include <string>
#include <sstream>
#include <list>

namespace ahttp
{
	//at the moment implement only 1 method

	enum class Status
	{
		OK = 200,
		NOT_FOUND = 404
	};

	class Method
	{
	public:
		Method() {};
		explicit Method(const std::string& method);

		void setMethod(const std::string& method);

		const char* to_string(Method m);

	private:
		enum METHODS{NO, GET}; //supports only GET method

		METHODS method = NO;
	};
	


	const char* to_string(Status s)
	{
		switch (s)
		{
		case Status::OK: return "OK"; break;
		case Status::NOT_FOUND: return "NOT FOUND"; break;
		}
	}

	class Header;

	class Request
	{
	public:
		Request(const std::string& request);

	private:
		Method method;
		std::string file_name;
		std::string http_version;
		std::list<Header> headers;
	};

	class Response
	{
	public:
		Response();

		void addHeader();

	private:
	};

	class Header
	{
	public:
		Header(const std::string& key, const std::string& value);

		const char* to_string();

	private:
		std::string key;
		std::string value;
	};
}
