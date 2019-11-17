#include "HTTPUtility.h"

#include <iostream>

ahttp::Request::Request(const std::string& request)
{
	std::stringstream s(request);

	std::string method;
	s >> method;
	if (method.empty()) throw std::exception("Request contains an empty method");

	std::string file;
	s >> file;
	if (file.empty()) throw std::exception("Request contains an empty file name");
	
	std::string http_v;
	s >> http_v;
	if (http_v.empty()) throw std::exception("Request contains an empty http protocol version");

	try
	{
		this->method.setMethod(method);
	}
	catch (const std::runtime_error & e)
	{
		std::cout << "Runtime error: " << e.what();
	}

	this->file_name = file;
	http_version = http_v;

	std::string line;
	while (s >> line)
	{
		std::stringstream in(line);
		std::string key;
		std::string value;
		std::getline(in, key, ':');
		std::getline(in, value);

		if (key.empty() || value.empty())
		{
			std::cerr << "WARNING: drop empty a header with empty key or value" << std::endl;
			continue;
		}

		headers.push_back(Header{ key, value });
	}
}

ahttp::Header::Header(const std::string& key, const std::string& value)
{
	this->key = key;
	this->value = value;
}

ahttp::Method::Method(const std::string& method)
{
	setMethod(method);
}

void ahttp::Method::setMethod(const std::string& method)
{
	if (method == "GET")
	{
		this->method = METHODS::GET;
	}
	else
	{
		throw std::runtime_error("Unsopported method"); // throw exception if the method not supported
	}
}

const char* ahttp::Method::to_string(Method m)
{
	switch (m.method)
	{
	case Method::METHODS::GET: return "GET"; break;
	default: return nullptr;
	}
}
