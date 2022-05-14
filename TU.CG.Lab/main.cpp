#include <iostream>

#include "Applications/Application_ModelLoading.hpp"

int main(int argc, char** argv)
{
	try
	{
		Applications::Application_ModelLoading app;

		app.Run();

		return 0;
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;

		return -1;
	}
}
