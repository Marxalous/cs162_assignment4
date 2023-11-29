/*********************************************************************
** Program Filename: main.cpp
** Author: Matthew McMahon
** Date: 11/28/23
** Description: int main() function
** Input:
** Output:
*********************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"

using namespace std;

/*********************************************************************
** Function: main()
** Description: The main function that runs the Wumpus game.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Runs the Wumpus game until the player decides to exit.
*********************************************************************/
int main() {
	cout << "Welcome to\n\n"
			"  ___ ___               __    ___________.__              __      __                                   \n"
			" /   |   \\ __ __  _____/  |_  \\__    ___/|  |__   ____   /  \\    /  \\__ __  _____ ______  __ __  ______\n"
			"/    ~    \\  |  \\/    \\   __\\   |    |   |  |  \\_/ __ \\  \\   \\/\\/   /  |  \\/     \\____ \\|  |  \\/  ___/\n"
			"\\    Y    /  |  /   |  \\  |     |    |   |   Y  \\  ___/   \\        /|  |  /  Y Y  \\  |_> >  |  /\\___ \\ \n"
			" \\___|_  /|____/|___|  /__|     |____|   |___|  /\\___  >   \\__/\\  / |____/|__|_|  /   __/|____//____  >\n"
			"       \\/            \\/                       \\/     \\/         \\/              \\/|__|              \\/ \n" << "\n\n";

	// Seed the RNG
	srand(time(NULL));

	// Run until the player would like to stop
	do {
		int wid = 5, len = 5;
		bool debug = false;

		// Get user input for width of the cave
		do {
			cout << "What is the width of the cave: ";
			cin >> wid;
			if (wid < 4) cout << "Width must be at least 4!" << endl;
		} while (wid < 4);

		// Get user input for length of the cave
		do {
			cout << "What is the length of the cave: ";
			cin >> len;
			if (len < 4) cout << "Length must be at least 4!" << endl;
		} while (len < 4);

		// Get user input for if they would like to play in debug mode
		do {
			cout << "Would you like to play in debug mode? (1 = true, 0 = false) ";
			cin >> debug;
		} while (debug != 0 && debug != 1);

		do {
			Game g;

			// Run the game
			g.play_game(wid, len/*, hei*/, debug);

			// Ask if the player would like to play again WITH the same settings
			char keep_playing;
			cout << "Would you like to play again WITH the same settings? (Y/N) ";
			cin >> keep_playing;

			// Reviews player input to determine whether or not to keep playing
			if (tolower(keep_playing) != 'y') {
				break;
			}

		} while (true);

		// Ask if the player would then like to play again, but changing the settings
		char keep_playing;
		cout << "Would you like to play again and CHANGE the settings? (Y/N) ";
		cin >> keep_playing;

		// Reviews player input to determine whether or not to keep playing
		if (tolower(keep_playing) != 'y') {
			break;
		}

	} while (true);

	return 0;
}