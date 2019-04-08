#pragma once
#include "Event.h"
#include<vector>

class Trace {
public:
	std::vector<std::string> trace;
	void add_event(std::string e) {
		trace.push_back(e);
	}
	Trace(){ }
};