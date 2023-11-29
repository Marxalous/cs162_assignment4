#ifndef STALACTITES_H
#define STALACTITES_H

#include "event.h"
#include <iostream>

using namespace std;

//Stalactites Interface
class Stalactites_Event : public Event {
	private:

	public:
		Stalactites_Event();					// Default constructor for the Stalactites_Event class
		virtual ~Stalactites_Event();			// Destructor for the Stalactites_Event class

		void nearby_message() const override;	// Outputs a nearby message related to Stalactites_Event
};

#endif