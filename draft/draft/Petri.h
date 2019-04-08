#pragma once
#include"Place_Trans.h"
#include<vector>
#include<set>
#include<map>
#include<algorithm>


class PetriNet {
public:
	std::vector<Place*> places;
	std::vector<Transition*> transitions;
	std::vector<std::string> transitions_name;

	PetriNet(Dependencies depend, std::set<std::string> all_transitions, std::map<std::string, int> A_full, std::map<std::string, int> A_tmp, std::vector<std::string> Begining, std::vector<std::string> Ending) {
		//заполняем массив переходов
		for (auto i : A_full) {
			transitions_name.push_back(i.first);
			Transition* cur = new Transition(i.first);
			transitions.push_back(cur);
		}

		//задаем начальные позиции
		Place *A = new Place("0");
		for (auto i : Begining) {
			for (auto j : transitions) {
				if (j->name == i) {
					j->parent.push_back(A);
					A->kids.push_back(j);
				}
			}
		}
		places.push_back(A);

		int chk = 1;
		//проверяем условие региона для кадой зависимости и минимизируем параметр count
		for (auto i : depend.cusal_dependencies) {
			if (i.second != 1) {
				std::cout << i.first.first << i.first.second << std::endl;
				int count = 0;
				count = A_tmp[i.first.first] - A_full[i.first.second];
				Place* A = new Place(std::to_string(chk));
				chk++;
				for (auto a : transitions) {
					if (a->name == i.first.first) {
						A->parents.push_back(a);
						a->kids.push_back(A);
					}
					if (a->name == i.first.second) {
						A->kids.push_back(a);
						a->parent.push_back(A);
					}
				}

				//добавляем дуги, входящие в позицию
				while (count < 0) {
					std::string add_transition;
					int cur_value = INT_MAX;
					std::pair<std::pair<std::string, std::string>, bool> copyy;
					bool is_visit = false;
					for (auto j : depend.cusal_dependencies) {
						if (j.first.first != i.first.first && j.first.second == i.first.second) {
							if (A_tmp[j.first.first] < cur_value) {
								cur_value = A_tmp[j.first.first];
								add_transition = j.first.first;
								copyy = { j.first,  j.second};
							}
						}
					}

					if (add_transition != "") {
						std::cout << "we add " << add_transition << std::endl;
						count += cur_value;
						std::cout << count << " ";
						for (auto a : transitions) {
							if (a->name == add_transition) {
								A->parents.push_back(a);
								a->kids.push_back(A);
								auto rem = find(depend.cusal_dependencies.begin(), depend.cusal_dependencies.end(), copyy);
								(*rem).second = 1;
							}
						}
					}
					else {
						break;
					}
				}

				//добавляем дуги, исходящие из позиции
				std::vector<std::string> visit_event;
				while (count >= 0) {
					std::string add_transition;
					int cur_value = INT_MAX;
					std::pair<std::pair<std::string, std::string>, bool> copyy;
					for (auto j : depend.cusal_dependencies) {
						if (j.first.first == i.first.first && j.first.second != i.first.second && find(visit_event.begin(), visit_event.end(), j.first.second) == visit_event.end()) {
							if (A_full[j.first.second] < cur_value) {
								cur_value = A_full[j.first.second];
								add_transition = j.first.second;
								copyy = { j.first, j.second};
								visit_event.push_back(j.first.second);
								std::cout << " " << j.first.second << " ";
							}
						}
					}

					if (add_transition != "") {
						if (count - cur_value >= 0) {
							std::cout << "we add " << add_transition << std::endl;
							count -= cur_value;
							std::cout << count << " ";
							for (auto a : transitions) {
								if (a->name == add_transition) {
									A->kids.push_back(a);
									a->parent.push_back(A);
									auto rem = find(depend.cusal_dependencies.begin(), depend.cusal_dependencies.end(), copyy);
									(*rem).second = 1;
								}
							}
						}
					}
					else {
						break;
					}
					std::cout << count << std::endl;
				}
				//i.second = 1;
				places.push_back(A);
			}
		}

		//добавляем конечную позицию
		A = new Place(std::to_string(chk));
		for (auto i : Ending) {
			for (auto j : transitions) {
				if (i == j->name) {
					A->parents.push_back(j);
					j->kids.push_back(A);
				}
			}
		}
		for (auto a : Ending) {
			std::cout << a << std::endl;
		}
	}

	void Print_Net() {
		for (auto a : transitions) {
			std::cout << "!   " << a->name << "   !" << std::endl;
			for (auto b : a->kids) {
				for (auto c : b->kids) {
					std::cout << c->name << " ";
				}
				std::cout << std::endl;
			}
		}
	}

	void Print_Net_to_DOT() {
		freopen("out.txt" ,"w", stdout);
		std::set<std::string> s;
		std::cout << "Digraph {" << std::endl;
		std::cout << "node [shape = box];";
		for (auto k : transitions) {
			std::cout << k->name << ";";
		}
		std::cout << std::endl;
		std::cout << "node [shape = circle];" << std::endl;
		for (auto a : places) {
			for (auto b : a->kids) {
				s.insert(a->name + "->" + b->name);
				for (auto c : b->kids) {
					s.insert(b->name + "->" + c->name);
				}
			}
		}
		for (auto a : s) {
			std::cout << a << std::endl;
		}
		std::cout << "}";
	}
};