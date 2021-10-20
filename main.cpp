#include "vector.hpp"
#include "stack.hpp"
#include <iostream>
#include <vector>

int	main() {

	ft::stack<int>	em;
	ft::stack<int>	st;

	em.push(8);

	std::cout << em.top() << "\n";
	std::cout << em.size() << "\n";

	st.push(8);

	std::cout << (st == em) << "\n";
	std::cout << "\n";

	ft::vector<int>	v;
	ft::vector<int>	vfill(8);
	ft::vector<int>	vfillval(8, 15);// calls range constr but should call fill

	//std::cout << "empty front: " << v.front() << "\n";
	std::cout << "size: " << vfill.size() << "\n";
	std::cout << "elem [1]: " << vfill[1] << "\n";
	//std::cout << "elem [1]: " << vfillval[1] << "\n";
	//std::cout << "front:  " << vfillval.front() << "\n";
//	try {
//		vfill.at(9);
//	}
///	catch ( std::out_of_range& oor ) {
//		std::cerr << "Out of Range error: " << oor.what() << "\n";
//	}

	std::vector<int>	stv(3, 8);
	std::cout << "size: " << stv.size() << "\n";
	std::cout << "elem [1]: " << stv[1] << "\n";
	std::cout << stv.at(1) << "\n";
	try {
		stv.at(9);
	}
	catch ( std::out_of_range& oor ) {
		std::cerr << "Out of Range error: " << oor.what() << "\n";
	}

	std::vector<int>	stvf;
	std::vector<int>::const_iterator	stit;
	std::vector<int>::const_iterator	stit1;

	stvf.push_back(1);
	stvf.push_back(7);
	stvf.push_back(3);
	stvf.push_back(5);
	std::cout << stvf.front() << "\n";
	std::cout << stvf.back() << "\n";
	stit = stvf.begin();
	stit1 = stit;
	stit1 += 1;
	std::cout << "st it arithmetics " << *(1 + stit1)  << "\n";
	std::cout << "st it arithmetics " << *(stit1 + 1)  << "\n";

	ft::vector<int>		toIter(3, 15);
	ft::vector<int>::const_iterator	cit;

	cit = toIter.begin();

	std::cout << *cit << "\n";
	std::cout << *(cit + 2) << "\n";

	toIter.push_back(2);
	toIter.push_back(7);
	toIter.push_back(5);
	cit += 3;
	std::cout << "it arithmetics " << *(cit) << "\n";
	std::cout << "it arithmetics " << *(cit + 1) << "\n";
	std::cout << "it arithmetics " << *(1 + cit) << "\n";

	return 0;
}
