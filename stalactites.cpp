/*********************************************************************
** Program Filename: stalactites.cpp
** Author: Matthew McMahon
** Date: 11/28/23
** Description: stalactites class functions
** Input:
** Output:
*********************************************************************/

#include "stalactites.h"

//Stalactites Implementation
/*********************************************************************
** Function: Stalactites_Event::Stalactites_Event()
** Description: Default constructor for the Stalactites_Event class.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Initializes a Stalactites_Event object with the event type "S".
*********************************************************************/
Stalactites_Event::Stalactites_Event() : Event("S") {}

/*********************************************************************
** Function: Stalactites_Event::~Stalactites_Event()
** Description: Destructor for the Stalactites_Event class.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Frees any resources associated with the Stalactites_Event object.
*********************************************************************/
Stalactites_Event::~Stalactites_Event() {}

/*********************************************************************
** Function: Stalactites_Event::nearby_message() const
** Description: Outputs a nearby message related to Stalactites_Event.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Outputs a message indicating the presence of stalactites.
*********************************************************************/
void Stalactites_Event::nearby_message() const {
    cout << "You hear water dripping..." << endl;
}