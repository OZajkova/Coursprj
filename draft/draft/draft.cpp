// draft.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include <iostream>
#include<vector>
#include"Trace.h"
#include<map>
#include"Depend.h"
#include"Petri.h"
#include <set>

int main()
{
//freopen("input.txt", "r", stdin);
	
	//we think that in one string we have 1 case\trace

	std::vector<Trace> Traces;
	bool flag = 0;
	std::string tmp;
	Trace cur;
	std::set<std::string> all_transitions;
	
	std::string c;
	std::map<std::string, int> A_full; //w;a
	std::map<std::string, int> A_tmp; //w
	std::vector<std::string> Begining;
	std::vector<std::string> Ending;
	while (getline(std::cin, c) && c !="") {
		for (size_t i = 0; i < c.size(); i++) {
			if (c[i] == ';') {
				if (i == tmp.size())
					Begining.push_back(tmp);
				if (i == c.size() - 1)
					Ending.push_back(tmp);
				cur.add_event(tmp);
				A_full[tmp]++;
				if (i != c.size() - 1)
					A_tmp[tmp]++;
				all_transitions.insert(tmp);
				tmp = "";
			}
			else {
				tmp += c[i];
			}
		}
			Traces.push_back(cur);
			flag = 1;
			cur = Trace();
	}


	//lets find dependencies
	Dependencies depend;
	depend.get_depend(Traces);
	depend.get_causal_dependencies();

	PetriNet net(depend, all_transitions, A_full, A_tmp, Begining, Ending);
	//net.Print_Net();
	net.Print_Net_to_DOT();

} 

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
