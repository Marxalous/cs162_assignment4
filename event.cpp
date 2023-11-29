/*********************************************************************
** Program Filename: event.cpp
** Author: Matthew McMahon
** Date: 11/28/23
** Description: event class functions
** Input:
** Output:
*********************************************************************/

#include "event.h"

//Event Implementation
/*********************************************************************
** Function: Event::Event()
** Description: Default constructor for the Event class.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: An Event object is created.
*********************************************************************/
Event::Event() {}

/*********************************************************************
** Function: Event::Event(string type)
** Description: Parameterized constructor for the Event class. Initializes the Event with the given type.
** Parameters:
**    - type: A string representing the type of the event.
** Pre-Conditions: None
** Post-Conditions: An Event object is created with the specified type.
*********************************************************************/
Event::Event(string type) : type(type) {}

/*********************************************************************
** Function: Event::~Event()
** Description: Destructor for the Event class.
** Parameters: None
** Pre-Conditions: An Event object exists.
** Post-Conditions: The Event object is destroyed.
*********************************************************************/
Event::~Event() {}

/*********************************************************************
** Function: Event::get_type() const
** Description: Returns the type of the event.
** Parameters: None
** Pre-Conditions: An Event object exists.
** Post-Conditions: The type of the event is returned.
*********************************************************************/
string Event::get_type() const {
    return type;
}