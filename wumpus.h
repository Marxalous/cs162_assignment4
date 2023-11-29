#ifndef WUMPUS_H
#define WUMPUS_H

#include "event.h"
#include <iostream>

using namespace std;

//Wumpus Interface
class Wumpus_Event : public Event {
	private:

	public:
		Wumpus_Event();							// 
		virtual ~Wumpus_Event();				// 

		void nearby_message() const override;	// 
};

#endif