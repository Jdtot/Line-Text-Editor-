//Author Jason Toth 
// Header file for the text editor class "Editor"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "EditorException.h"
using namespace std;
#pragma once
static int curLine =1; // Keeps track of current line.
static int changes = 0;// keeeps track of any changes made to the file (insertions, deletions, replaced lines.)
static int saves = 0;  // Keeps track of when the file is saved and matches the changes variable at the end of each "write function"
class Editor
{
public:
	// Constructor if a file was indicated on the command line to read in/out to this constructor takes in the command line argument and sets the argv member to the command line argument
	// It will then call the readLines function to read out the Lines to the screen so the user can see the starting File lines.
	Editor(char arg[]) 
	{
		argv = arg;
		readLines(argv);
	};
	// Default constructor which is used if no command line argument is found. 
	Editor()
	{};
	// runLoop is the function keep the text editing program running. It is an infinite loop which only ends when the quit command is called. Before a command is entered it will display
	//The current line position, then wait for a command to be inputted.
	void runLoop();
	// This function takes the string argv as a parameter and reads the lines into the vector line by line, as well as displaying each Line by line. For an initial first look at the file as a whole.
	void readLines(string);
private:
	//The Insert function will ask the user to input a line of text, it will then insert the text at the current line that the text editor is "at" it uses the static int curLine to determine 
	// this line. Anytime insert is called, at the end of the function the changes static int is incremented by one. This is used to keep track of whether or not changes have been saved.
	//Inesrt takes the editor member passed by reference. Editor is a vector of strings 
	void insert(vector<string> &editor);
	//The Change position funcion is used to switch the current line position. to a new position. 
	//Parameters It takes a string. which contains an integer value the user wishes to jump to.
	void changePosition(string selection);
	//DelFunction is the method called when the user wishes to delete line(s) from the text editor. 
	// For parameters it takes the editor member passed by reference, and the selection member passed by reference.
	// Depending on the contents of selection the delete function will delete either the current line, a selected line, or a range of lines. 
	void delFunction(vector<string> & editor, string & selection);
	//The replace function when called replaces line the text editor is currently editing, with a new line of text that the user is prompted to input
	//It's parameters are the editor vector passed in by reference
	void replace(vector<string> & editor);
	/*CheckArg is used to check the validity of different arguments, and return values depending on which argument is detected.
	 Parameters 
	 @Selection member passed in by reference contains the command which was entered with any (or all) arguments.
	 @Choice & Choice2 Both are int variables set to 0 before being passed in. They hold the values for optional numerical commands when needed. 
	/@Return 1 No argument was given indicating the user wants to operate on the current line.
	 @Return 2 Indicates that the user has entered  -1, the shortcut  for last line of the editor as the first and only argument 
	 @Return 0 Indicates that either a single argument entered, 
	 @Throw exception thrown if an invalid argument was entered where the first argument is larger than the second.
	 @Return -1 Indicates that a range of lines was indicated. 
	 @Return 4 Indicates that the arguments are greater than the end of the vector, last element+1
	*/
	int checkArg(string &selection, int & choice, int & choice2);
	/* Lines, depending on the commands given, will either display the current line, last line, a selected line, or a range of lines
	Parameters
	@editor passed in by reference to access the lines
	@selection passed in by reference, contains the command and any optional arguments. 
	@choice & choice2 int values to hold the optional numerical commands.
	*/
	void lines(vector<string> & editor, string & selection, int choice, int choice2);
	/*Write when called will write out the current contents to either the .txt file given on the command line, or to a new selected file. 
	@throw If no filename was given on the command line and no filename is inputted by the user, it will throw an exception telling the user that no file 
		was inputted and there was no command line file to write to. 
	@Editor vector to be passed in by reference
	@Argv string to hold the file that was inputted on the command line if there is one.  
	*/
	void write(vector<string> & editor, string argv);
	//The Quit function is used to exit the runLoop, if changes have been made to the file since it was last "saved" (written out to a file) then it will ask if the user
	// would like to save (write to file) before exiting, if they want to cancel and go back, or if they would like to exit.
	//@editor member passed by reference as a single paramter
	int quit(vector<string> & editor);
	// Function called within the write function, when no argument is given for a .txt file to write to, if a .txt file was given on the command line this function will be called to write
	// to the command line File. @Editor is the single paramter passed in by reference to be used when writing out to the file.
	void cmdLineWrite(string, vector<string> & editor);
	// NewFileWrite is called when a file name is inputted by the user to write out to. It will either find the file, or create a new one and write out the current contents of the text editor 
	// to that file effectively "saving" it.
	void newFileWrite(string , vector<string> & editor);
	// checkCurLine checks each time through the loop that the editing position is no greater than the end of the vector. If it is greater than the end of the vector it sets the editing position
	//to the end of the vector.
	//It takes the editor member passed in by reference as it's only parameter. it returns the int value of the last line, to be used by other functions.
	int checkCurLine(vector<string> & editor);
	// Parses the character argument and returns a value to indicate which letter has been entered.
	int checkCharArg(string & selection);
	//The commands function parses the character command recieved and depending on the outcome will call one of the call----- functions to call the apropriate function with a try/catch block.
	// It takes the editor vector passed in by reference, the string selection  passed in by reference, and the int i from the runLoop passed in by reference.
	// The is is passed in by reference so that through the commands function the user is able to end the infinite runLoop
	void commands(vector<string> & editor, string & selection, int & i);
	//The callDelete function calls the delFunction with the try catch block in place.
	void callDelete();
	//The callWrite function calls the Write function with the try catch block in place.
	void callWrite();
	//The callQuit function calls the quit function with the try catch block in place.
	// It takes the int i from the runLoop so that if the user chooses to quit, it can change the value of i to end the infinite loop.
	void callQuit(int & i);
	//The callJump function calls the changePosition function with the try catch block in place.
	void callJump();
	//The callList function calls the Lines function with the try catch block in place. as well as checking if the current line or range of lines are even currently in the vector
	//If they are not it returns out.
	void callList();
	//getNumArguments is used by the checkArg function to get the optional numerical arguments from the selection string, 
	//it takes the int variables choice and choice2 passed in by reference as parameters.
	void getNumArguments(string selection, int &choice, int &choice2);
	string selection; // String variable used to "select" different commands such as jump, insert, replace, etc.
	vector<string> editor; // Vector of strings to hold the lines, which will be operated upon
	string argv; // Command line File if one is given. If not it will stay as an empty string. 
};
void Editor::insert(vector<string> &editor)
{
	string nLine; // variable for line to be inserted
	cout << endl << "Enter text for the insertion. ";
	getline(cin, nLine); // gets the line to insert
	editor.insert(editor.begin() + (curLine-1), nLine); // Inserts the line in the editor vector at the position of curLine-1 
	changes++; // Updates the changes int to show that a change has been made
	return;
}
void Editor::changePosition(string selection)
{
	int choice = 0; // Optional first numerical command
	int choice2 =0;// Optional second numerical command
	if (checkArg(selection, choice, choice2) == 0) // Single argument given.
	{
		for (curLine = 0; curLine < choice; curLine++) // adjusts the curLine to the element that is 1 less than the choice. because the "Line Number" will 
		{											//be 1 greater than the element holding it
		
		};
		return;
	}
	if (checkArg(selection, choice, choice2) == 2) // Shortcut for last line given. Loop will keep iterating and incrementing curLine till it is at the last element of the vector.
	{
		curLine = 0;
		for (vector<string>::iterator it = editor.begin(); it != editor.end(); it++ )
		{
			curLine++;
		}
	}
	if (checkArg(selection, choice, choice2) == 4) // Arguments given are greater than the length of the vector. It will set the curLine to the end of the vector.
	{
		curLine = (checkCurLine(editor) + 1);
	}													// If not any of the above cases it throws an exception stating that the Jump command only takes 1 argument, no more and no less.
	if (checkArg(selection, choice, choice2) != 0 && checkArg(selection, choice, choice2) != 2 && checkArg(selection, choice, choice2) != 4) 
	{																									
		throw incorrectArgumentsException();
	}
}
void Editor::delFunction(vector<string> & editor, string & selection) // Delete function to delete lines from the text editor using the vector.erase method.
{
	int choice =0;
	int choice2 = 0;
	switch (checkArg(selection, choice, choice2) )// switch statement which uses the parsing function checkArg to decide what happens.
	{
	case 2:							//Last line shortcut was given. 
	editor.erase(editor.end() - 1); // erases from element 1 less than the vector end which is the "last line".
	break;
	case 1:							// no argument given, so deletes from the current editing position. 
	editor.erase(editor.begin() + (curLine - 1)); // erases from the position of curLine -1 which is the element of the current editing position.
	break;
	case 0:							// Single Line argument given. 
	editor.erase(editor.begin() + (choice - 1)); // erases from the location of choice (the argument given) -1
	break;
	case -1:						// Range of lines given 
		choice2 = (choice2 - choice) + 1; // to get the number of times we need to iterate, choice 2 becomes the difference of choice2 and choice + 1
		for (int i = 0; i < choice2; i++) // for loop which erases the line from position of choice-1 this will push the next line into the line at choice-1 Repeats until all lines have been erased. 
		{
			editor.erase(editor.begin() + (choice - 1));
		}
		break;
	}
	changes++; // increments after the delete function has been called to show that a change has happened.
}
void Editor::runLoop()
	{
	int i = 0;
	int size = (i + 1);// the size variable is used in the runLoop function to keep the loop going infinitely.
		for (int i = 0; i < size; i++, size++)
		{
			checkCurLine(editor);// Ensures that the curLine will never be less than 0, or more than the end of the vector.
			cout << endl << "*" << (curLine) << ". "; // Displays current editing position.
			getline(cin, selection); // Gets command from user
			commands(editor, selection, i); // Calls the commands function to parse the command given.
		}
	}
void Editor::replace(vector<string> & editor)
{
	if (curLine > checkCurLine(editor)) // If current editing position is at the end of the vector, returns out of the function as there will be no element in which to replace text.
		return;
	else
	{
		string nLine;// string to hold line of text.
		cout << endl << "Please enter the text to replace it with." << endl;
		cin.ignore();
		getline(cin, nLine);
		editor[(curLine - 1)] = nLine; // changes the data of element curLine-1 to the data that is held in nLine
		changes++; // increments changes to show a change has been made.
	}
}
int  Editor::checkArg(string & selection, int & choice, int & choice2)
{
	getNumArguments(selection, choice, choice2); // Takes the selection string and inputs the optional numeric commands into the correct variables of choice and choice2
	if (choice == 0 && choice2 == 0) // If no argument was given return 1
		return 1;
	if ((choice == -1 && choice2 == 0)) // If the shortcut for last line (-1) was given as first argument return 2
		return 2;
	// Checks for several conditions and has a short circuit in place if any are met the first two statements seperated by the OR, check if the last line shortcut is used 	
	//The third statement checks to make sure that neither value is for a line number that does not exist in the vector, and that the argument input was correct, (first not greater than second)
	if ( (choice == 0 && choice2 == -1) || (choice > 0 && choice2 == -1) ||( (choice > 0 && choice2 > 0)&& (choice && choice2 < checkCurLine(editor) ) ) && (choice < choice2)  ) 
	{
		if (choice2 == -1) // if the shortcut was used as the second argument
		{
			choice2 = (checkCurLine(editor)); // sets choice 2 to the  int value of the last element of the vector
		}
		if (choice == 0) // if choice was 0 in the first command (0 -1) sets choice to 1 so that the lines, and delete commands can still function, as they call choice-1.
		{
			choice = 1;
		}
		return -1;	//Returns -1 to indicate a range of lines was entered.
	}
	if (choice > choice2)			// Single argument or invalid argument.
	{
		if (choice > 0 && choice2 == 0)  // Indicates that choice had an argument entered but choice did not (single argument) Returns 0
			return 0;
		else                             // if both arguments had a command entered and the first argument was larger than the second then an exception is thrown.
			throw firstIsGreaterException();
	}
	if (choice > ( (checkCurLine(editor) + 1) ) || choice2 > (checkCurLine(editor) ) ) // arguments are larger than the current vector size. Returns 4
		return 4;
}
void Editor::lines(vector<string> & editor, string & selection, int choice, int choice2)
{
		if ((checkArg(selection, choice, choice2)) == -1) // Range of lines were given
		{
			choice2 = (choice2 - choice) + 1; // choice 2 becomes the difference of (choice2 - choice) +1 so that the for loop knows how many times to run
			vector<string>::iterator it = editor.begin() + (choice - 1); // initialize an iterator to 1 less than choice
			for (int i = 0; i < choice2; i++, it++) // while the for loop runs it displays the contents at the element that the iterator is currently at.
			{
				cout << " " << (choice + i) << ". " << *it << endl;
			}
		}
		else if ((checkArg(selection, choice, choice2)) == 1) // No argument given, Displays current line.
		{
			if (curLine > checkCurLine(editor)) // Checks if the user is trying to display a line that does not exist yet, if they are it cancels the operation and returns out.
				return;
			vector<string>::iterator it = (editor.begin() + (curLine - 1)); // iterator initialized to the element of curLine -1
			cout << " " << (curLine) << ". " << *it << endl; // displays the data at that element. 
		}
		else if ((checkArg(selection, choice, choice2)) == 2) // Shortcut for last Line given. 
		{
			vector<string>::iterator it = (editor.end() - (1)); // initializes iterator to the last element of the vector.
			cout << " " << checkCurLine(editor) << ". " << *it << endl; // displays the data at that element. 
		}
		else if ((checkArg(selection, choice, choice2)) == 0) // Single argument given
		{
			vector<string>::iterator it = (editor.begin() + (choice - 1)); // intializes iterator to the element 1 less than that argument.
			cout << " " << (choice) << ". " << *it << endl; // displays the data at that element. 
		}
}
void Editor::readLines(string)
{
	fstream iofile;
	string lines;
	iofile.open(argv); // opens file that was inputted on the command line. 
	if (iofile.is_open(), ios::in)
	{
		while (iofile.good()) // while end of file not reached it uses get lines to store the current line, then push_back to push it into the editor vector. Repeats for all lines until finished.
		{
			getline(iofile, lines);
			editor.push_back(lines);
		}
	}
	int i = 0;
	for (vector<string>::iterator it = editor.begin(); it != editor.end(); it++) // Displays all the lines by reading out each element of the vector that was just filled with the push_back calls.
	{
		if ((i + 1) == curLine)
		{
			cout << "*" << (i + 1) << ". " << *it << endl;
		}
		else
			cout << " " << (i + 1) << ". " << *it << endl;
			i++;
	}
}
void Editor::write(vector<string> & editor, string)
{
	string fileName; // variable to create a new file.
	cout << "Please enter the File name you would like to write to. (just the file name no .txt is needed)" << endl << "or press enter to use the file that was entered on the command line " << endl;
	getline(cin, fileName);

	if (fileName.empty() && argv.empty()) // checks if no new file was entered by the user, and if no command line argument was given. If both are empty then it throws an exception.
		throw noFileException();
	else if (fileName.empty()) // If no fileName is provided by the user then it calls the cmdLineWrite, and writes out to the file given on the command line. 
	{
		cmdLineWrite(argv, editor);
	}
	else // If a file name is given, then it will write out either to a current file, or create a new file with the name in the fileName string.
	{
		newFileWrite(fileName,editor);
	}
	saves = changes; // After either of the writing functions finishes, the static int saves is set equal to changes, to represent that all changes have been saved.
	return;
}
int  Editor::quit(vector<string> & editor)
{
	if (changes > saves) // Check if there are more changes than saves. If so indicate to the user that they have unsaved changes, and ask what they would like to do.
	{
		cout << "Unsaved changes were made would you like to save them? Type Y to save, C to cancel, E to exit without saving. ";
		getline(cin, selection);

		if (selection == "Y")// If Y is selected returns -1 to indicate that.
		{
			return -1;
		}
		else if (selection == "C") // if C is selected returns 2 to indicate that
			return 2;
		else if (selection == "E")// if E is selected returns 1 to indicate that
			return 1;
	}
	else if (changes == saves) // if changes and saves are equal all changes have been saved, and so the program returns 1
		return 1;
	
}
void Editor::newFileWrite(string  fileName, vector<string> & editor)
{
	ofstream ofile;
	ofile.open(fileName + ".txt"); // Takes the fileName and adds .txt to the end to either search for a file of that name or creates a new one. 
	if (ofile.is_open()) 
	{
		for (vector<string>::iterator it = editor.begin(); it != editor.end(); it++) // iterates through the vector writing out each line
		{
			if ((it + 1) == editor.end()) // If on the final line, does not write out an endl. (They add up over time)
			{
				ofile << *it;
			}
			else
				ofile << *it << endl;
		}
		ofile.close();
	}
}
void Editor::cmdLineWrite(string file, vector<string> & editor)
{
	ofstream ofile;
	ofile.open(file);
	if (ofile.is_open())
	{
		for (vector<string>::iterator it = editor.begin(); it != editor.end(); it++)// iterates through the vector writing out each line
		{
			if ((it + 1) == editor.end())// If on the final line, does not write out an endl. (They add up over time)
			{
				ofile << *it;
			}
			else
				ofile << *it << endl;
		}
		ofile.close();
	}
}
int  Editor::checkCurLine(vector<string> & editor)
{
	int i = 0;
	for (vector<string>::iterator it = editor.begin(); it != editor.end(); it++, i++) // iterates through the vector updating integer i as it goes, until i represents the last element of the vector.
	{
	}
	if (curLine > i) // if curLine is greater than the last element, sets it to i +1 (the end of the vector).
	{
		curLine = (i+1);
	}
	if (curLine == 0) // if curLine is 0, sets it to 1 as 0 is not a valid line number
	{
		curLine = 1;
	}
	return i; // returns i to be used by other functions which may need to compare their values to the int index value of the last element of the vector.
}
int  Editor::checkCharArg(string & selection)
{
	stringstream selStream;
	string charCommand;
	selStream << selection;
	selStream >> charCommand;
	if (charCommand == "I") // Checks charCommand to see which letter was passed in. Returns a different value for each letter to be used by the commands function to call the correct command.
		return 1;
	if (charCommand == "R")
		return 2;
	if (charCommand == "D")
		return 3;
	if (charCommand == "W")
		return 4;
	if (charCommand == "Q")
		return 5;
	if (charCommand == "J")
		return 6;
	if (charCommand == "L")
		return 7;
}
void Editor::commands(vector<string> & editor, string & selection, int & i)
{
	switch (checkCharArg(selection)) // Parses the character argument and returns a value depending on the letter.
	{
	case 1:				// I was entered, insert is called
		insert(editor);
		break;
	case 2:				// R was entered, replace is called
		replace(editor);
		break;
	case 3:				// D was entered, callDelete is called
		callDelete();
		break;
	case 4:				// W was entered, callWrite is called
		callWrite();
		break;
	case 5:				// Q was entered, callQuit is called
		callQuit(i);
		break;
	case 6:				// J was entered, callJump is called
		callJump();
		break;
	case 7:				// L was entered, callList is called
		callList();
		break;
	}
}
void Editor::callDelete()
{
	try // Try catch block that calls the delFunction
	{
		delFunction(editor, selection);
	}
	catch (firstIsGreaterException)
	{
		cout << "Error: First integer after the character command must be less than the second." << endl;
		cout << "Unless using the -1 shortcut in which case it must be entered as the second argument following a zero." << endl;
	}
}
void Editor::callWrite()
{
	try			// Try catch block that calls the write function
	{
		write(editor, argv);
	}
	catch (noFileException noF)
	{
		cout << "No file was entered on the command line, there is no default file to save to." << endl;
	}
}
void Editor::callQuit(int & i)
{
	switch (quit(editor)) // evaluates the quit function.
	{
	case -1: // User selected Y, indicating they want to save their changes. calls the write function with a try catch block
		try
		{
			write(editor, argv);
		}
		catch (noFileException())
		{
			cout << "No file was entered on the command line, there is no default file to save to, returning to command mode." << endl;
		}
		i = (i + 5); // updates i to break the infinite loop on the runLoop function.
		return;
	case 2: // User indicated they wanted to cancel. breaks out of the switch statement and returns to the runLoop.
		break;
	case 1: // Either the user wished to exit without saving, or they had already saved any changes they made. 
		i = (i + 5); // adjusts i to break the loop.
		return;
	}
}
void Editor::callJump()
{
		try				// Try catch block that calls the changePosition function
		{
			changePosition(selection);
		}
		catch (incorrectArgumentsException incorrect)
		{
			cout << "Error: The jump command only accepts 1 numerical argument. It cannot take more or fewer arguments." << endl;
		}
}
void Editor::callList()
{
	cout << endl; // just adds a blank line to make it more clear which line is the editing line, and which are the outputted ones.
	try			// Try catch block that calls the Lines function
	{
		int choice = 0;
		int choice2 = 0;
		if ((checkArg(selection, choice, choice2)) == 4) // If argument(s) are greater than the last element of the vector, returns out as there are no lines to list.
			return;
		lines(editor, selection, choice, choice2);
	}
	catch (firstIsGreaterException)
	{
		cout << "Error First integer after the character command must be less than the second." << endl;
		cout << "Unless using the -1 shortcut in which case it must be entered as the second argument following a zero." << endl;
	}
}
void Editor::getNumArguments(string selection, int &choice, int &choice2)
{
	stringstream letter;// strinstream to distribute arguments.
	string getRidOfLetter;
	letter << selection; // selection (arguments passed into the stream)
	letter >> getRidOfLetter; // gets rid of the letter command.
	letter >> choice; // puts numerical argument 1 into choice
	letter >> choice2;// puts numerical argument 2 into choice2
}