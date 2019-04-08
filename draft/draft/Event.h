#pragma once
#include<string>

class Event {
public:
	std::string Activity;
	Event(std::string s) {
		Activity = s;
	}
};