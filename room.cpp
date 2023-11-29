/*********************************************************************
** Program Filename: room.cpp
** Author: Matthew McMahon
** Date: 11/28/23
** Description: room class functions
** Input:
** Output:
*********************************************************************/

#include "room.h"

using namespace std;

//Room Implementation
/*********************************************************************
** Function: Room::Room()
** Description: Default constructor for the Room class.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Initializes a Room object with default values.
*********************************************************************/
Room::Room() : event_type(" "), event(nullptr), presence(false) {}

/*********************************************************************
** Function: Room::Room(string event_type)
** Description: Parameterized constructor for the Room class.
** Parameters: string event_type - The type of event in the room.
** Pre-Conditions: None
** Post-Conditions: Initializes a Room object with the specified event type.
*********************************************************************/
Room::Room(string event_type) {}

/*********************************************************************
** Function: Room::~Room()
** Description: Destructor for the Room class.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Frees the memory occupied by the event if it exists.
*********************************************************************/
Room::~Room() {
	if (this->event != nullptr) delete this->event;
}

/*********************************************************************
** Function: Room::is_empty()
** Description: Checks if the room is empty.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Returns true if the room is empty, false otherwise.
*********************************************************************/
bool Room::is_empty() const {
	return ((this->presence == false) && (this->event == nullptr));
}

/*********************************************************************
** Function: Room::get_event()
** Description: Gets the event object in the room.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Returns a pointer to the event object in the room.
*********************************************************************/
Event* Room::get_event() const {
	return this->event;
}

/*********************************************************************
** Function: Room::set_event(Event* new_event)
** Description: Sets the event in the room.
** Parameters: Event* new_event - Pointer to the new event.
** Pre-Conditions: None
** Post-Conditions: Sets the event in the room to the specified event.
*********************************************************************/
void Room::set_event(Event* new_event) {
	this->event = new_event;
}

/*********************************************************************
** Function: Room::set_event_type(string new_event_type)
** Description: Sets the type of event in the room.
** Parameters: string new_event_type - The new event type.
** Pre-Conditions: None
** Post-Conditions: Sets the event type in the room to the specified type.
*********************************************************************/
void Room::set_event_type(string new_event_type) {
	this->event_type = new_event_type;
}

/*********************************************************************
** Function: Room::has_player()
** Description: Checks if the room has a player.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Returns true if the room has a player, false otherwise.
*********************************************************************/
bool Room::has_player() const {
	return this->presence;
}

/*********************************************************************
** Function: Room::set_player(bool new_presence)
** Description: Sets the presence of a player in the room.
** Parameters: bool new_presence - The new presence value.
** Pre-Conditions: None
** Post-Conditions: Sets the presence of a player in the room to the specified value.
*********************************************************************/
void Room::set_player(bool new_presence) {
	this->presence = new_presence;
}