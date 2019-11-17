#include "Reply.h"

namespace ahttp
{
	Reply::Reply()
	{
	}

	int& Reply::code()
	{
		return code_;
	}

	int Reply::code() const
	{
		return code_;
	}

	void Reply::addHeader(const std::string& key, const std::string& value)
	{
		headers.push_back(std::make_pair(key, value));
	}

	std::string Reply::to_str()
	{
		std::stringstream ss;
		ss << http_version << " " << code_ << " " << code_to_string(code_) << "\r\n";
		ss << "Content-Length: " << content_.size() << "\r\n";
		ss << "Content-Type: text/html\r\n";
		ss <<"\r\n";
		ss << content_;

		return ss.str();
	}
	void Reply::set_content(std::string&& content)
	{
		this->content_ = content;
	}

	std::string Reply::code_to_string(int code)
	{
		switch (code)
		{
		case 200: return "OK";
		case 400: return "Bad Request";
		case 404: return "Not Found";
		case 501: return "Not Implemented";
		default: return "Internal Server Error";
		}
	}
}
