#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <algorithm>

template<typename B, typename E>
void print(B _begin, E _end)
{
	std::unordered_set<std::string> set;
	for (; _begin != _end; _begin++)
	{
		if (set.find(*_begin) == set.end()) std::cout << *_begin << std::endl;
		set.insert(*_begin);
	}
	std::cout << " --------------------------- \n";
}




int main()
{
	std::vector<std::string> vec{ "one", "one", "two","three", "four", "four" };
	std::list<std::string> list{ "one", "one", "two","three", "four", "four" };

	print(vec.begin(), vec.end());
	print(list.rbegin(), list.rend());
	print(vec.rbegin(), vec.rend());


	// Task 2

	std::cout << "Type things here..... Type 'exit' to exit" << std::endl;

	std::vector<std::string> svec;

	std::string input = "";

	while (input != "exit")
	{
		std::cin >> input;
		if (input != "exit") svec.push_back(input);
	}

	std::sort(svec.begin(), svec.end());

	std::cout << "You type following things >>\n";

	for (auto value : svec)
	{
		std::cout << value << std::endl;
	}

	return 0;
}