#ifndef GAME_H
#define GAME_H

#include "room.h"
#include "gold.h"
#include "stalactites.h"
#include "bats.h"
#include "wumpus.h"
#include <vector>
#include <iostream>

using namespace std;

//Game interface
class Game {
	private:
		vector<vector<Room>> gameBoard;		// Vector of the game board

		int length; 				// Length of the board
		int width;  				// Width of the board
		// int height;				// Height of the board
		int num_arrows; 			// Number of arrows remaining
		bool debug_view;			// Debug mode bool

		bool at_starting_location;	// At starting location bool
		int starting_x;				// Starting x value
		int starting_y;				// Starting y value
		// int starting_z;			// Starting z value
		int current_x;				// Current x value
		int current_y;				// Current y value
		// int current_z;			// Current z value

		bool beat_wumpus;			// Has the wumpus been defeated?
		bool awake;					// Is the wumpus awake?

		bool inverted_controls;		// Does the player have inverted controls?
		int inverted_strength;		// Turns of inverted controls left

		bool loss;					// Has the player been killed?

		bool picked_up;				// Has the gold been picked up?

		void check_and_output_message(int x, int y) const;										// Checks for events in the specified room and outputs messages accordingly
		bool within_bounds(int x, int y) const;													// Checks if the specified coordinates are within the game board bounds

	public:
		Game();																					// Default constructor for the Game class
		~Game();																				// Destructor for the Game class

		void play_game(int l, int w, bool);														// Main function to play the game. It sets up the game board and runs the game loop

		void set_up(int l, int w);																// Sets up the game board with specified dimensions and populates it with events
		void seed_bat_rooms(int l, int w);														// Seeds the game board with 2 Bats events in empty rooms
		void seed_stalactite_rooms(int l, int w);												// Seeds the game board with 2 Stalactites events in empty rooms
		void seed_wumpus_room(int l, int w);													// Seeds the Wumpus event in a random empty room on the game board
		void seed_gold_room(int l, int w);														// Seeds the game board with 1 Gold event in an empty room
		void seed_player_start(int l, int w);													// Seeds the player's starting location on the game board
		void display_game() const;																// Displays the current state of the game board

		bool check_win() const;																	// Checks if the player has won the game by picking up the gold or defeating the Wumpus
		bool check_loss() const;																// Checks if the player has lost the game

		char get_input();																		// Gets user input for player movement or arrow firing
		void move(char);																		// Moves the player based on user input or fires an arrow
		void move_up();																			// Moves the player north on the game board
		void move_left();																		// Moves the player west on the game board
		void move_down();																		// Moves the player south on the game board
		void move_right();																		// Moves the player east on the game board
		void fire_arrow();																		// Fires an arrow in the specified direction and handles arrow movement
		char get_dir();																			// Gets the direction from the player for firing an arrow
		void move_arrow(int &arrow_row, int &arrow_col, char dir);								// Moves the arrow based on the specified direction

		void current_player_location();															// Updates the current player location based on the game board

		void wumpus_move();																		// Moves the Wumpus to an empty adjacent room based on random chance

		bool hit_wumpus(int arrow_row, int arrow_col);											// Checks if the arrow hits the Wumpus based on the arrow's position
		bool hit_wall(int arrow_row, int arrow_col) const;										// Checks if the arrow hits a wall based on the arrow's position

		void move_wumpus(int wumpus_row, int wumpus_col);										// Moves the Wumpus to an empty adjacent room
		void find_wumpus_location(int &wumpus_row, int &wumpus_col) const;						// Finds the current location of the Wumpus on the game board

		void event_action();																	// Performs actions based on the type of event in the current room
		void adjacent_rooms();																	// Checks for events in the adjacent rooms and outputs messages accordingly

		void confusion_decrament();																// Decreases the turns of confusion and resets controls when strength reaches 0

		void move_event(int to_row, int to_col, int from_row, int from_col/*, int from_h*/);	// Moves an event from one room to another on the game board
		void remove_event(int row, int col);													// Removes an event from the specified room on the game board
};

#endif