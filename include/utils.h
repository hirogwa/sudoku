#include <string>
#include <vector>
namespace strutils
{
	std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems);
	std::vector<std::string> split(const std::string &s, char delim);
	bool is_digit_only(std::string str);
}
