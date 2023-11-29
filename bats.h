#ifndef BATS_H
#define BATS_H

#include "event.h"
#include <iostream>

using namespace std;

//Bats Interface
class Bats_Event : public Event {
	private:

	public:
		Bats_Event();							// Constructor for the Bats_Event class
		virtual ~Bats_Event();					// Destructor for the Bats_Event class

		void nearby_message() const override;	// Displays a message indicating that the player hears winds flapping nearby
};

#endif