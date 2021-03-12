#include "PCH.h"

#include "GameApp.h"

#include <iostream>

int main(int argc, char* argv[])
{
	try
	{
		auto game_app = make_unique<GameApp>();
		game_app->run();
	}
	catch (exception ex)
	{
		// show native dialog of exception
		std::cout << "An exception occured: " << ex.what() << std::endl;
	}

	return 0;
}