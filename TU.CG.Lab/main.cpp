#include <iostream>

#include "Application.hpp"

int main(int argc, char** argv)
{
	try
	{
		Application app;

		app.Run();

		return 0;
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;

		return -1;
	}
}
