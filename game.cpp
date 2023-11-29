/*********************************************************************
** Program Filename: game.cpp
** Author: Matthew McMahon
** Date: 11/28/23
** Description: game class functions
** Input: main.cpp
** Output: the game.
*********************************************************************/

#include "game.h"

/*********************************************************************
** Function: Game::Game()
** Description: Default constructor for the Game class.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: A Game object is created with default values.
*********************************************************************/
Game::Game() : length(0), width(0), num_arrows(0), debug_view(false), at_starting_location(false), beat_wumpus(false), awake(false), inverted_controls(false), inverted_strength(0), loss(false), picked_up(false) {

}

/*********************************************************************
** Function: Game::~Game()
** Description: Destructor for the Game class. Frees memory for each Room's event.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: The Game object is destroyed, and memory is freed.
*********************************************************************/
Game::~Game() {
    // Free the memory for each Room's event
	for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
			if (gameBoard.at(i).at(j).get_event() != nullptr) {
				delete gameBoard.at(i).at(j).get_event();
				gameBoard.at(i).at(j).set_event(nullptr);
			}
        }
    }
}

/*********************************************************************
** Function: Game::play_game(int w, int l, bool d)
** Description: Main function to play the game. It sets up the game board and runs the game loop.
** Parameters:
**    - w: Width of the game board.
**    - l: Length of the game board.
**    - d: Debug mode flag.
** Pre-Conditions: None
** Post-Conditions: The game is played until the player wins or loses.
*********************************************************************/
void Game::play_game(int w, int l, bool d) {
	// Set up the game board
	set_up(w, l);
	this->debug_view = d;

	char input;

	// Loops until the player has either won or lost
	while (!check_win() && !check_loss()){
		// Display the game board
		display_game();

		// Take and use user input
		input = get_input();
		move(input);

		// If the wumpus has awoken, the wumpus will move to an empty adjacent tile
		if (awake) {
			wumpus_move();
		}

		// Tests for any events in adjacent rooms
		adjacent_rooms();

		// Tests for any events in the entered room
		event_action();

		// Decreases confusion
		confusion_decrament();
	}

	return;
}

/*********************************************************************
** Function: Game::set_up(int l, int w)
** Description: Sets up the game board with specified dimensions and populates it with events.
** Parameters:
**    - l: Length of the game board.
**    - w: Width of the game board.
** Pre-Conditions: None
** Post-Conditions: The game board is set up with events and the player's starting location.
*********************************************************************/
void Game::set_up(int l, int w) {
	this->length = l;
	this->width = w;
	this->num_arrows = 3;
	gameBoard = vector<vector<Room>>(l, vector<Room>(w));

	// Set 2 Bats rooms
	seed_bat_rooms(l, w);

	// Set 2 Stalactites rooms
	seed_stalactite_rooms(l, w);

	// Sets 1 Wumpus room
	seed_wumpus_room(l, w);

	// Sets 1 Gold room
	seed_gold_room(l, w);

	// Seed player starting location
	seed_player_start(l, w);

	// Assign the created game board to the member variable
	this->gameBoard = gameBoard;
}

/*********************************************************************
** Function: Game::seed_bat_rooms(int l, int w)
** Description: Seeds the game board with 2 Bats events in empty rooms.
** Parameters:
**    - l: Length of the game board.
**    - w: Width of the game board.
** Pre-Conditions: None
** Post-Conditions: Two Bats events are placed in empty rooms.
*********************************************************************/
void Game::seed_bat_rooms(int l, int w) {
	int x, y;

	// Finds 2 empty rooms
	for (int i = 0; i < 2; ++i) {
		do {
			x = rand() % l;
			y = rand() % w;
		} while (!gameBoard.at(x).at(y).is_empty());

		// Populates the room with a new Bats event
		gameBoard.at(x).at(y).set_event(new Bats_Event);
	}
}

/*********************************************************************
** Function: Game::seed_stalactites_rooms(int l, int w)
** Description: Seeds the game board with 2 Stalactites events in empty rooms.
** Parameters:
**    - l: Length of the game board.
**    - w: Width of the game board.
** Pre-Conditions: None
** Post-Conditions: Two Stalactites events are placed in empty rooms.
*********************************************************************/
void Game::seed_stalactite_rooms(int l, int w) {
	int x, y;

	// Finds 2 empty rooms per floor
	for (int i = 0; i < 2; ++i) {
		do {
			x = rand() % l;
			y = rand() % w;
		} while (!gameBoard.at(x).at(y).is_empty());

		// Populates the room with a new Stalactites event
		gameBoard.at(x).at(y).set_event(new Stalactites_Event);
	}
}

/*********************************************************************
** Function: Game::seed_wumpus_room(int l, int w)
** Description: Seeds the Wumpus event in a random empty room on the game board.
** Parameters:
**    - l: Length of the game board.
**    - w: Width of the game board.
** Pre-Conditions: A Game object exists.
** Post-Conditions: Wumpus event is seeded in a random empty room on the game board.
*********************************************************************/
void Game::seed_wumpus_room(int l, int w) {
	int x, y;

	// Finds an empty room
	do {
		x = rand() % l;
		y = rand() % w;
	} while (!gameBoard.at(x).at(y).is_empty());

	// Populates the room with a new Wumpus event
	gameBoard.at(x).at(y).set_event(new Wumpus_Event);
}

/*********************************************************************
** Function: Game::seed_gold_room(int l, int w)
** Description: Seeds the game board with 1 Gold event in an empty room.
** Parameters:
**    - l: Length of the game board.
**    - w: Width of the game board.
** Pre-Conditions: None
** Post-Conditions: One Gold event is placed in an empty room.
*********************************************************************/
void Game::seed_gold_room(int l, int w) {
	int x, y;

	// Finds an empty room
	do {
		x = rand() % l;
		y = rand() % w;
	} while (!gameBoard.at(x).at(y).is_empty());

	// Populates the room with a new Gold event
	gameBoard.at(x).at(y).set_event(new Gold_Event);
}

/*********************************************************************
** Function: Game::seed_player_start(int l, int w)
** Description: Seeds the player's starting location on the game board.
** Parameters:
**    - l: Length of the game board.
**    - w: Width of the game board.
** Pre-Conditions: A Game object exists.
** Post-Conditions: Player's starting location is seeded on the game board.
*********************************************************************/
void Game::seed_player_start(int l, int w) {
	int x, y;

	// Finds an empty room
	do {
		x = rand() % l;
		y = rand() % w;
	} while (!gameBoard.at(x).at(y).is_empty());

	// Populates the room with player
	gameBoard.at(x).at(y).set_player(true);
	this->starting_x = x; // Sets the starting x
	this->starting_y = y; // Sets the starting y
	this->current_x = x; // Sets the initial current x
	this->current_y = y; // Sets the initial current y
}

/*********************************************************************
** Function: Game::display_game() const
** Description: Displays the current state of the game board.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: Current state of the game board is displayed.
*********************************************************************/
void Game::display_game() const {
	cout << endl << endl;
	cout << "Arrows remaining: " << this->num_arrows << endl << endl;

	// Grid pattern between rows
	string line = "";
	for (int i = 0; i < this->width; ++i) {
		if (debug_view) line += "+----";
		else if (!debug_view) line += "+-----";
	}

	// Prints out the grid
	for (int i = 0; i < this->length; ++i) {
		cout << line << "+-" << endl << "||";
		for (int j = 0; j < this->width; ++j) {
			const Room& current_room = this->gameBoard.at(i).at(j);

			// Place the player marker
			cout << (current_room.has_player() ? " *" : "  ");

			// If debug mode is on, place the event markers
			if (debug_view) {
				if (current_room.get_event() != nullptr) cout << current_room.get_event()->get_type() << "||";
				else cout << " ||";
			}
			else cout << "  ||";
		}
		cout << endl;
	}
	cout << line << "+-" << endl;
}

/*********************************************************************
** Function: Game::check_win() const
** Description: Checks if the player has won the game by picking up the gold or defeating the Wumpus.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: Prints a win message if the conditions are met.
*********************************************************************/
bool Game::check_win() const {
	// Check if the player has picked up the gold and returned to the starting position
	if (picked_up && starting_x == current_x && starting_y == current_y) {
		cout << "Congratulations! You collected the gold and returned to the starting position. You win!" << endl;
		return true;
	}

	// Check if the player has killed the wumpus
	if (beat_wumpus) {
		cout << "Congratulations! You killed the Wumpus. You win!" << endl;
		return true;
	}

	return false;
}

/*********************************************************************
** Function: Game::check_loss() const
** Description: Checks if the player has lost the game.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: Prints a loss message if the player has lost.
*********************************************************************/
bool Game::check_loss() const {
	// Checks if the player has lost
	if (loss) {
		cout << "Game over! You lost." << endl;
		return true;
	}

	return false;
}

/*********************************************************************
** Function: Game::get_input()
** Description: Gets user input for player movement or arrow firing.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: Returns the user input character.
*********************************************************************/
char Game::get_input() {
	char c;

	// Display options
	cout << endl << endl << "Player move..." << endl << endl;
	cout << "W - North" << endl;
	cout << "A - West" << endl;
	cout << "S - South" << endl;
	cout << "D - East" << endl;
	cout << "F - Fire an Arrow" << endl;

	cout << "Enter input: " << endl;
	cin >> c;
	cout << endl;
	cin.ignore(256, '\n');

	// Convert input to lowercase for usability
	if (isalpha(c)) {
		c = tolower(c);
	}

	return c;
}

/*********************************************************************
** Function: Game::move(char c)
** Description: Moves the player based on user input or fires an arrow.
** Parameters:
**    - c: User input character.
** Pre-Conditions: A Game object exists.
** Post-Conditions: Player is moved or arrow is fired based on user input.
*********************************************************************/
void Game::move(char c) {
	// If player enters f, proceed to the fire_arrow() function
	if (c == 'f') {
		fire_arrow();
		return;
	}

	// If the player is not confused and enters an input
	if (!inverted_controls) {
		switch (c) {
			case 'w':
				move_up();
				break;

			case 'a':
				move_left();
				break;

			case 's':
				move_down();
				break;

			case 'd':
				move_right();
				break;
		}
	}

	// If the player is confused and enters an input
	else if (inverted_controls) {
		switch (c) {
			case 'w':
				move_down();
				break;

			case 'a':
				move_right();
				break;

			case 's':
				move_up();
				break;

			case 'd':
				move_left();
				break;
		}
	}

	// Grabs the player's current location for any events
	current_player_location();

	// Checks if the player moves to the starting location or not
	if (starting_x == current_x && starting_y == current_y) this->at_starting_location = true;
	else this->at_starting_location = false;
}

/*********************************************************************
** Function: Game::move_up()
** Description: Moves the player north on the game board.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: Player is moved north if possible.
*********************************************************************/
void Game::move_up() {
	// Check if movement is within bounds
	if (current_x > 0) {
		// Move the player
		gameBoard.at(current_x).at(current_y).set_player(false);
		gameBoard.at(current_x - 1).at(current_y).set_player(true);
	}
	else cerr << "There is a wall preventing you from moving North." << endl;

	return;
}

/*********************************************************************
** Function: Game::move_left()
** Description: Moves the player west on the game board.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: Player is moved west if possible.
*********************************************************************/
void Game::move_left() {
	// Check if movement is within bounds
	if (current_y > 0) {
		// Move the player
		gameBoard.at(current_x).at(current_y).set_player(false);
		gameBoard.at(current_x).at(current_y - 1).set_player(true);
	} else cerr << "There is a wall preventing you from moving West." << endl;

	return;
}

/*********************************************************************
** Function: Game::move_down()
** Description: Moves the player south on the game board.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: Player is moved south if possible.
*********************************************************************/
void Game::move_down() {
	// Check if movement is within bounds
	if (current_x < length - 1) {
		// Move te player
		gameBoard.at(current_x).at(current_y).set_player(false);
		gameBoard.at(current_x + 1).at(current_y).set_player(true);
	} else cerr << "There is a wall preventing you from moving South." << endl;

	return;
}

/*********************************************************************
** Function: Game::move_right()
** Description: Moves the player east on the game board.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: Player is moved east if possible.
*********************************************************************/
void Game::move_right() {
	// Check if movement is within bounds
	if (current_y < width - 1) {
		// Move the player
		gameBoard.at(current_x).at(current_y).set_player(false);
		gameBoard.at(current_x).at(current_y + 1).set_player(true);
	} else cerr << "There is a wall preventing you from moving East." << endl;

	return;
}

/*********************************************************************
** Function: Game::fire_arrow()
** Description: Fires an arrow in the specified direction and handles arrow movement.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: Arrow is fired, and game state is updated accordingly.
*********************************************************************/
void Game::fire_arrow() {
	// Check if the player has any more arrows
	if (this->num_arrows == 0) {
		cout << "You have no more arrows!" << endl;
		return;
	}

	// Get the direction the player wants the arrow to travel in
	char dir = get_dir();
	int arrow_travel_count = 0;

	// If player wants to go back, do not decrement the number of arrows, return to move
	if (dir == 'b') {
		++this->num_arrows;
		return;
	}

	// Get the starting position of the arrow
	int arrow_row = current_x, arrow_col = current_y;

	// Arrow movement interactions
	for (arrow_travel_count = 0; arrow_travel_count < 3; ++arrow_travel_count) {
		move_arrow(arrow_row, arrow_col, dir);

		// If the arrow goes OOB, it hits the wall
		if (!within_bounds(arrow_row, arrow_col)) {
			this->awake = true;
			cout << "The arrow hit a wall.\nThe Wumpus woke up..." << endl;
			break;
		}

		const Event* current_event = gameBoard.at(arrow_row).at(arrow_col).get_event();

		// Check if there's an event in the current room
		if (current_event) {
			// Check for arrow hitting wumpus
			if (current_event->get_type() == "W") {
				this->beat_wumpus = true;
				cout << "You have slain the Wumpus!" << endl;
			}
			// If it misses, the wumpus wakes
			else {
				if (!this->awake){
					this->awake = true;
					cout << "Your arrow missed.\nThe Wumpus woke up..." << endl;
				}
			}
			break;
		}
	}

	// If the arrow travels through 3 rooms, it wakes the wumpus
	if (arrow_travel_count == 3) {
		this->awake = true;
		cout << "Your arrow missed.\nThe Wumpus woke up..." << endl;
	}

	return;
}

/*********************************************************************
** Function: Game::get_dir()
** Description: Gets the direction from the player for firing an arrow.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: Returns the direction chosen by the player and decreases the number of arrows.
*********************************************************************/
char Game::get_dir() {
	char dir;

	// Display options
	cout << "Fire an arrow...." << endl;
	cout << "W - North" << endl;
	cout << "A - West" << endl;
	cout << "S - South" << endl;
	cout << "D - East" << endl;
	cout << "B - Back to Move" << endl;

	cout << "Enter direction: " << endl;
	cin >> dir;
	cin.ignore(256, '\n');

	// Reduce the number of arrows
	--this->num_arrows;

	return dir;
}

/*********************************************************************
** Function: Game::move_arrow(int &arrow_row, int &arrow_col, char dir)
** Description: Moves the arrow based on the specified direction.
** Parameters:
**    - arrow_row: Reference to the arrow's current row.
**    - arrow_col: Reference to the arrow's current column.
**    - dir: Direction in which the arrow should move.
** Pre-Conditions: A Game object exists.
** Post-Conditions: Arrow's position is updated based on the specified direction.
*********************************************************************/
void Game::move_arrow(int &arrow_row, int &arrow_col, char dir) {
	// Move the arrow based on the direction
	switch (dir) {
		case 'w':
			if (arrow_row > 0) --arrow_row;
			break;

		case 'a':
			if (arrow_col > 0) --arrow_col;
			break;

		case 's':
			if (arrow_row < length) ++arrow_row;
			break;

		case 'd':
			if (arrow_col < width) ++arrow_col;
			break;
	}
}

/*********************************************************************
** Function: Game::current_player_location()
** Description: Updates the current player location based on the game board.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: Current player location is updated.
*********************************************************************/
void Game::current_player_location() {
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < length; ++j) {
			// Get the current x and y coords of the player
			if (gameBoard.at(i).at(j).has_player()) {
				this->current_x = i;
				this->current_y = j;
				break;
			}
		}
	}
}

/*********************************************************************
** Function: Game::wumpus_move()
** Description: Moves the Wumpus to an empty adjacent room based on random chance.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: Wumpus may be moved to an empty adjacent room.
*********************************************************************/
void Game::wumpus_move() {
	int rng = rand() % 4;

	if (rng != 0) {
		int wumpus_row, wumpus_col;
		find_wumpus_location(wumpus_row, wumpus_col);

		move_wumpus(wumpus_row, wumpus_col);
	}

	return;
}

/*********************************************************************
** Function: Game::hit_wumpus(int arrow_row, int arrow_col)
** Description: Checks if the arrow hits the Wumpus based on the arrow's position.
** Parameters:
**    - arrow_row: Row position of the arrow.
**    - arrow_col: Column position of the arrow.
** Pre-Conditions: A Game object exists.
** Post-Conditions: Returns true if the arrow hits the Wumpus, false otherwise.
*********************************************************************/
bool Game::hit_wumpus(int arrow_row, int arrow_col) {
	Event* event_type = gameBoard.at(arrow_row).at(arrow_col).get_event();
	if (event_type != nullptr && gameBoard.at(arrow_row).at(arrow_col).get_event()->get_type() == "W") {
		return true;
	}

	return false;
}

/*********************************************************************
** Function: Game::hit_wall(int arrow_row, int arrow_col) const
** Description: Checks if the arrow hits a wall based on the arrow's position.
** Parameters:
**    - arrow_row: Row position of the arrow.
**    - arrow_col: Column position of the arrow.
** Pre-Conditions: A Game object exists.
** Post-Conditions: Returns true if the arrow hits a wall, false otherwise.
*********************************************************************/
bool Game::hit_wall(int arrow_row, int arrow_col) const {
	if (arrow_row < 0 || arrow_row >= length || arrow_col < 0 || arrow_col >= width) return true;

	return false;
}

/*********************************************************************
** Function: Game::move_wumpus(int wumpus_row, int wumpus_col)
** Description: Moves the Wumpus to an empty adjacent room.
** Parameters:
**    - wumpus_row: Current row position of the Wumpus.
**    - wumpus_col: Current column position of the Wumpus.
** Pre-Conditions: A Game object exists.
** Post-Conditions: Wumpus is moved to an empty adjacent room if possible.
*********************************************************************/
void Game::move_wumpus(int wumpus_row, int wumpus_col) {
	bool moved = false;

	int rng = rand() % 4;

	switch (rng) {
		case 0:
			if (wumpus_row > 0 && gameBoard.at(wumpus_row - 1).at(wumpus_col).is_empty()) {
				move_event(wumpus_row - 1, wumpus_col, wumpus_row, wumpus_col);
				moved = true;
			}
			break;

		case 1:
			if (wumpus_row < length - 1 && gameBoard.at(wumpus_row + 1).at(wumpus_col).is_empty()) {
				move_event(wumpus_row + 1, wumpus_col, wumpus_row, wumpus_col);
				moved = true;
			}
			break;

		case 2:
			if (wumpus_col > 0 && gameBoard.at(wumpus_row).at(wumpus_col - 1).is_empty()) {
				move_event(wumpus_row, wumpus_col - 1, wumpus_row, wumpus_col);
				moved = true;
			}
			break;

		case 3:
			if (wumpus_col < width -1 && gameBoard.at(wumpus_row).at(wumpus_col + 1).is_empty()) {
				move_event(wumpus_row, wumpus_col + 1, wumpus_row, wumpus_col);
				moved = true;
			}
			break;
	}
}

/*********************************************************************
** Function: Game::find_wumpus_location(int &wumpus_row, int &wumpus_col) const
** Description: Finds the current location of the Wumpus on the game board.
** Parameters:
**    - wumpus_row: Reference to store the row position of the Wumpus.
**    - wumpus_col: Reference to store the column position of the Wumpus.
** Pre-Conditions: A Game object exists.
** Post-Conditions: wumpus_row and wumpus_col are updated with the Wumpus's location.
*********************************************************************/
void Game::find_wumpus_location(int &wumpus_row, int &wumpus_col) const {
	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < width; ++j) {
			if (gameBoard.at(i).at(j).get_event() && gameBoard.at(i).at(j).get_event()->get_type() == "W") {
				wumpus_row = i;
				wumpus_col = j;
				return;
			}
		}
	}
}

/*********************************************************************
** Function: Game::adjacent_rooms()
** Description: Checks for events in the adjacent rooms and outputs messages accordingly.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: Outputs messages for events in adjacent rooms.
*********************************************************************/
void Game::adjacent_rooms() {
	check_and_output_message(current_x + 1, current_y); // North
	check_and_output_message(current_x, current_y - 1); // West
	check_and_output_message(current_x - 1, current_y); // South
	check_and_output_message(current_x, current_y + 1); // East
}

/*********************************************************************
** Function: Game::event_action()
** Description: Performs actions based on the type of event in the current room.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: Actions are taken based on the type of event in the current room.
*********************************************************************/
void Game::event_action() {
	int rng = rand() % 2;

	if (gameBoard.at(current_x).at(current_y).get_event() != nullptr) {

		if (gameBoard.at(current_x).at(current_y).get_event()->get_type() == "B") {
			this->inverted_controls = true;
			this->inverted_strength = 5;
			remove_event(current_x, current_y);
			cout << "You have been confused by a swarm of bats!" << endl;
			return;
		}

		else if (gameBoard.at(current_x).at(current_y).get_event()->get_type() == "S") {
			if (rng == 0) {
				this->loss = true;
				cout << "You were it in the head by falling stalactites!" << endl;
				return;
			}
			remove_event(current_x, current_y);
			cout << "You have evaded the falling stalactites!" << endl;
			return;
		}

		else if (gameBoard.at(current_x).at(current_y).get_event()->get_type() == "W") {
			this->loss = true;
			cout << "You were eaten by the Wumpus!" << endl;
			return;
		}

		else if (gameBoard.at(current_x).at(current_y).get_event()->get_type() == "G") {
			this->picked_up = true;
			remove_event(current_x, current_y);
			cout << "You have found the gold!" << endl;
			return;
		}
	}

	return;
}

/*********************************************************************
** Function: Game::confusion_decrement()
** Description: Decreases the turns of confusion and resets controls when strength reaches 0.
** Parameters: None
** Pre-Conditions: A Game object exists.
** Post-Conditions: Confusion strength is decremented, and controls are reset if strength reaches 0.
*********************************************************************/
void Game::confusion_decrament() {
	if (inverted_strength > 0) {
		--this->inverted_strength;
		cout << "Turns of confusion left: " << inverted_strength + 1 << endl;
		return;
	}
	else if (inverted_strength == 0) {
		this->inverted_controls = false;
		return;
	}

	return;
}

/*********************************************************************
** Function: Game::move_event(int to_row, int to_col, int from_row, int from_col)
** Description: Moves an event from one room to another on the game board.
** Parameters:
**    - to_row: Row position to move the event to.
**    - to_col: Column position to move the event to.
**    - from_row: Row position to move the event from.
**    - from_col: Column position to move the event from.
** Pre-Conditions: A Game object exists.
** Post-Conditions: Event is moved from one room to another on the game board.
*********************************************************************/
void Game::move_event(int to_row, int to_col, int from_row, int from_col) {
	if (within_bounds(to_row, to_col) && within_bounds(from_row, from_col)) {
		Event* temp_event = gameBoard.at(from_row).at(from_col).get_event();
		gameBoard.at(from_row).at(from_col).set_event(gameBoard.at(to_row).at(to_col).get_event());
		gameBoard.at(to_row).at(to_col).set_event(temp_event);
	}
}

/*********************************************************************
** Function: Game::remove_event(int row, int col)
** Description: Removes an event from the specified room on the game board.
** Parameters:
**    - row: Row position of the room.
**    - col: Column position of the room.
** Pre-Conditions: A Game object exists.
** Post-Conditions: Event is removed from the specified room on the game board.
*********************************************************************/
void Game::remove_event(int row, int col) {
	delete gameBoard.at(row).at(col).get_event();
	gameBoard.at(row).at(col).set_event(nullptr);
}

/*********************************************************************
** Function: Game::check_and_output_message(int x, int y) const
** Description: Checks for events in the specified room and outputs messages accordingly.
** Parameters:
**    - x: Row position of the room.
**    - y: Column position of the room.
** Pre-Conditions: A Game object exists.
** Post-Conditions: Outputs messages for events in the specified room.
*********************************************************************/
void Game::check_and_output_message(int x, int y) const {
	if (within_bounds(x, y)) {
		const Event* event = gameBoard.at(x).at(y).get_event();
		if (event) {
			event->nearby_message();
		}
	}
}

/*********************************************************************
** Function: Game::within_bounds(int x, int y) const
** Description: Checks if the specified coordinates are within the game board bounds.
** Parameters:
**    - x: Row position to check.
**    - y: Column position to check.
** Pre-Conditions: A Game object exists.
** Post-Conditions: Returns true if the coordinates are within bounds, false otherwise.
*********************************************************************/
bool Game::within_bounds(int x, int y) const {
	return x >= 0 && x < length && y >= 0 && y < width;
}