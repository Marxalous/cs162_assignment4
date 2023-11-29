/*********************************************************************
** Program Filename: wumpus.cpp
** Author: Matthew McMahon
** Date: 11/28/23
** Description: wumpus class functions
** Input:
** Output:
*********************************************************************/

#include "wumpus.h"

//Wumpus Implementation
/*********************************************************************
** Function: Wumpus_Event::Wumpus_Event()
** Description: Default constructor for the Wumpus_Event class.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Initializes a Wumpus_Event object with the event type "W".
*********************************************************************/
Wumpus_Event::Wumpus_Event() : Event("W") {}

/*********************************************************************
** Function: Wumpus_Event::~Wumpus_Event()
** Description: Destructor for the Wumpus_Event class.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Frees any resources associated with the Wumpus_Event object.
*********************************************************************/
Wumpus_Event::~Wumpus_Event() {}

/*********************************************************************
** Function: Wumpus_Event::nearby_message() const
** Description: Outputs a nearby message related to Wumpus_Event.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Outputs a message indicating the presence of a terrible stench.
*********************************************************************/
void Wumpus_Event::nearby_message() const {
    cout << "You smell a terrible stench..." << endl;
}