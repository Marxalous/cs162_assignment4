/*********************************************************************
** Program Filename: gold.cpp
** Author: Matthew McMahon
** Date: 11/28/23
** Description: gold class functions
** Input:
** Output:
*********************************************************************/

#include "gold.h"

//Gold Implementation
/*********************************************************************
** Function: Gold_Event::Gold_Event()
** Description: Constructor for Gold_Event class.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Creates a Gold_Event object with type "G".
*********************************************************************/
Gold_Event::Gold_Event() : Event("G"){}

/*********************************************************************
** Function: Gold_Event::~Gold_Event()
** Description: Destructor for Gold_Event class.
** Parameters: None
** Pre-Conditions: A Gold_Event object exists.
** Post-Conditions: Destroys the Gold_Event object.
*********************************************************************/
Gold_Event::~Gold_Event() {}

/*********************************************************************
** Function: Gold_Event::nearby_message() const
** Description: Displays a nearby message for the Gold_Event.
** Parameters: None
** Pre-Conditions: A Gold_Event object exists.
** Post-Conditions: Prints a message indicating a glimmer nearby.
*********************************************************************/
void Gold_Event::nearby_message() const {
	cout << "You see a glimmer nearby..." << endl;
}