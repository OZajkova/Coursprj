#pragma once
#include <iostream>
#include <vector>

class Transition;

class Place {
public:
	std::vector<Transition*> kids;
	std::vector<Transition*> parents;
	std::string name;

	Place(std::string s) {
		name = s;
	}
};

class Transition {
public:
	std::vector<Place*> kids;
	std::vector<Place*> parent;
	std::string name;

	Transition(std::string s) {
		name = s;
	}
};
