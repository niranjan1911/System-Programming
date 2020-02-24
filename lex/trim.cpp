#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

int main()
{
	std::string s = "\tHello \n\n				World";
	s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

	std::cout << s;

	return 0;
}