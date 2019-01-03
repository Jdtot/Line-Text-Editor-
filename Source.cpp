#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Editor.h" // Editor class header. 
using namespace std;
int main(int argc, char* argv[])
{
	if (argc > 1) // File given on command line.
	{
		Editor editor(argv[1]);
		editor.runLoop();
	}
	if (argc == 1) // No file given on command line.
	{
		Editor editor;
		editor.runLoop();
	}
	return 0;
}
