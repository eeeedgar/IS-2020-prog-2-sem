#include <iostream>
#include "RubicksCube.hpp"

using namespace std;

void Hello()
{
	cout
		<< "Hello User!\n"
		<< "Rules are simple. Here is an example.\nPrint single character 'R' to make 'R' rotation.\n"
		<< "Print 'Rr' to make reversed one.\n"
		<< "Got it?\n"
		<< "All commands:\n"
		<< "L  Lr   R  Rr   U  Ur   D  Dr   F  Fr   B  Br\n"
		<< "Print 'Z' to quit\n";
}

int main()
{
	RubicksCube cube = RubicksCube();
	string input;
	bool isGame = true;

	Hello();

	while (isGame)
	{

		cube.show();

		cin >> input;

		if (input == "R")
		{
			cube.R();
		}
		else if (input == "Rr")
		{
			cube.Rr();
		}
		else if (input == "L")
		{
			cube.L();
		}
		else if (input == "Lr")
		{
			cube.Lr();
		}
		else if (input == "U")
		{
			cube.U();
		}
		else if (input == "Ur")
		{
			cube.Ur();
		}
		else if (input == "D")
		{
			cube.D();
		}
		else if (input == "Dr")
		{
			cube.Dr();
		}
		else if (input == "F")
		{
			cube.F();
		}
		else if (input == "Fr")
		{
			cube.Fr();
		}
		else if (input == "B")
		{
			cube.B();
		}
		else if (input == "Br")
		{
			cube.Br();
		}
		else if (input == "Z")
		{
			cout << "Goodbye! :)\n";
			isGame = false;
		}
		else if (input == "help")
		{
			Hello();
		}
		else
		{
			cout << "Print 'help' to get command list or 'Z' to quit.\n";
		}

	}
	return 0;
}
