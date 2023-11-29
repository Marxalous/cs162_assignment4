#ifndef GOLD_H
#define GOLD_H

#include "event.h"
#include <iostream>

using namespace std;

//Gold Interface
class Gold_Event : public Event {
	private:

	public:
		Gold_Event();							// Constructor for Gold_Event class
		virtual ~Gold_Event();					// Destructor for Gold_Event class

		void nearby_message() const override;	// Displays a nearby message for the Gold_Event
};

#endif