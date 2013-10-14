#include <vector>
#include <string>
#include <sstream>
#include "utils.h"
namespace strutils
{
	std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems)
	{
		std::string original(s);
		std::stringstream s_stream (original);
		std::string str;
		while (std::getline(s_stream, str, delim))
		{
			elems.push_back(str);
		}
		if (original.find_last_of(delim) == original.size() - 1)
			elems.push_back("");
		return elems;
	}
	std::vector<std::string> split(const std::string &s, char delim)
	{
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}
	bool is_digit_only(std::string str)
	{
		return (str.find_first_not_of("0123456789") == std::string::npos);
	}
}
