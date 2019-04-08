#pragma once
#include<map>
#include<set>
#include<unordered_map>
#include "Trace.h"
#include "Event.h"


class Dependencies {
public:
	std::map <std::pair<std::string, std::string>, int> all_dependencies;
	std::vector<std::pair<std::pair<std::string, std::string>, bool> > cusal_dependencies;
	
	void get_causal_dependencies() {
		for (auto a : all_dependencies) {
			if (a.second != 0 || all_dependencies[{a.first.second, a.first.first}] != 0) {
				if (a.second > all_dependencies[{a.first.second, a.first.first}]){
					cusal_dependencies.push_back({ a.first, 0 });
				}
			}
		}
	} 

	void get_depend(std::vector<Trace> traces) {
		for (size_t i = 0; i < traces.size(); ++i) {
			for (size_t j = 1; j < traces[i].trace.size(); ++j) {
				all_dependencies[{traces[i].trace[j - 1], traces[i].trace[j]}]++;
				std::cout << "   " << traces[i].trace[j - 1] << "   " << traces[i].trace[j] << std::endl;
			}
		}
	}
};