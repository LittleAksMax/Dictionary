#include <iostream>
#include <string>
#include "dictionary.h"
#include <stdlib.h>
#include <chrono>
#include <utility>

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

template<typename F, typename... Args>
double funcTime(F func, Args&&... args) {
	TimeVar t1 = timeNow();
	func();
	return duration(timeNow() - t1);
}

int main()
{
	dict<int, int> person;

	for (int i = 0; i < 30000; i++)
		if (!person.insert(rand() % 30000 + 1, rand() % 100))
			i--;

	
	
	std::cout << "norm: " << funcTime([&]() { person[30000]; }) << "\n";

	std::cout << "opt: " << funcTime([&]() { person.optimize(true, person.root()); }) << "\n";
	
	std::cout << "algo: " << funcTime([&]() { person[30000]; });
	

	std::cout << person << std::endl;

	return 0;
}