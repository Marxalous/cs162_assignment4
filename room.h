#ifndef ROOM_H
#define ROOM_H

#include "event.h"
#include <iostream>

using namespace std;

//Room Interface
class Room {
	private:
		Event* event;		// Event object pointer
		string event_type;	// Event type
		bool presence;		// Player presence

	public:
		Room();										// Default constructor for the Room class
		Room(string event_type);					// Parameterized constructor for the Room class
		~Room();									// Destructor for the Room class

		bool is_empty() const;						// Checks if the room is empty
		Event* get_event() const;					// Gets the event object in the room
		void set_event(Event* event);				// Sets the event in the room
		void set_event_type(string new_event_type);	// Sets the type of event in the room
		bool has_player() const;					// Checks if the room has a player
		void set_player(bool new_presence);			// Sets the presence of a player in the room
};

#endif