#include "stack.hpp"
#include <iostream>

int	main() {

	stack<int>	em;
	stack<int>	st;

	em.push(8);

	std::cout << em.top() << "\n";
	std::cout << em.size() << "\n";

	st.push(8);

	std::cout << (st == em) << "\n";

	return 0;
}