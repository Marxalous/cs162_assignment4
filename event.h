#ifndef EVENT_H
#define EVENT_H

#include <iostream>

using namespace std;

//Event Interface
class Event {
	protected:
		const string type;	// Event type

	public:
		Event();									// Default constructor for the Event class
		Event(string type);							// Parameterized constructor for the Event class
		virtual ~Event();							// Destructor for the Event class

		string get_type() const;					// Returns the type of the event
		virtual void nearby_message() const = 0;	// Pure virtual function for event's nearby messages
};

#endif