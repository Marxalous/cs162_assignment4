#include "bats.h"

//Bats Implementation
/*********************************************************************
** Function: Bats_Event::Bats_Event()
** Description: Constructor for the Bats_Event class. Initializes the Bats_Event with the type "B".
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: A Bats_Event object is created with the type "B".
*********************************************************************/
Bats_Event::Bats_Event() : Event("B") {}

/*********************************************************************
** Function: Bats_Event::~Bats_Event()
** Description: Destructor for the Bats_Event class.
** Parameters: None
** Pre-Conditions: A Bats_Event object exists.
** Post-Conditions: The Bats_Event object is destroyed.
*********************************************************************/
Bats_Event::~Bats_Event() {}

/*********************************************************************
** Function: Bats_Event::nearby_message() const
** Description: Displays a message indicating that the player hears winds flapping nearby.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: The message is displayed.
*********************************************************************/
void Bats_Event::nearby_message() const {
    cout << "You hear winds flapping..." << endl;
}