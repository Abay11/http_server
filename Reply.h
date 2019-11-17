#pragma once

#include "includes_all.h"

namespace ahttp
{
	typedef std::pair<std::string, std::string> header_t;

	class Reply
	{
	public:
		Reply();

		int& code();
		int code() const;

		void addHeader(const std::string& key, const std::string& value);

		std::string to_str();

		void set_content(std::string&&);

	private:

		std::string code_to_string(int);

	private:
		int code_;
		std::string http_version = "HTTP/1.0";
		std::vector<header_t> headers;
		std::string content_;
	};
}