// Basic exceptions to be thrown when Errors occur.
#pragma once
#include <string>
#include <iostream>
class firstIsGreaterException  // Exception if the first argument is greater than the second.
{
public:
	firstIsGreaterException()
	{
	}
};
class incorrectArgumentsException  // Exception if incorrect arguments are entered. (Too many, too few)
{
public:
	incorrectArgumentsException()
	{
	}
};
class noFileException  // No file was provided either on command line or from input when prompted. 
{
public:
	noFileException()
	{
	}
};
