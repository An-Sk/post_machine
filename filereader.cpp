#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	std::string line;
	
	std::ifstream in("file123.txt");
	if (in.is_open())
	{
		while (getline(in, line))
		{
			std::cout << line << std::endl;
		}
	}
	in.close();

	std::cout << "Êîíåö ôàéëà" << std::endl;
	return 0;

}
