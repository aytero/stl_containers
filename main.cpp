#include "vector.hpp"
#include "stack.hpp"
#include <iostream>
#include <vector>

#include <list>//
#include "rbtree.hpp"

int	main() {

	/*
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
*/

	/*
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
	std::vector<int>::iterator			stiter;

	stvf.push_back(1);
	stvf.push_back(7);
	stvf.push_back(3);
	stvf.push_back(5);
	std::cout << stvf.front() << "\n";
	std::cout << stvf.back() << "\n";
	stit = stvf.begin();
	//stiter = stit;
	stit1 = stit;
	stit1 += 2;
	std::cout << "st it arithmetics " << *(1 + stit1)  << "\n";
	std::cout << "st it arithmetics " << *(stit1 + 1)  << "\n";
	std::cout << "st it arithmetics, distance " << stit1 - stit  << "\n";

	ft::vector<int>		toIter(3, 15);
	//ft::vector<int>		toIter;
	ft::vector<int>::const_iterator	cit;
	ft::vector<int>::iterator		it;


	toIter.push_back(2);
	toIter.push_back(7);
	toIter.push_back(5);
	toIter.push_back(1);
	toIter.push_back(8);

	cit = toIter.begin();

	std::cout << *cit << "\n";
	std::cout << *(cit + 2) << "\n";
	std::cout << *(cit + 4) << "\n";

	cit += 3;
	std::cout << "it arithmetics " << *(cit) << "\n";
	std::cout << "it arithmetics " << *(cit + 1) << "\n";
	std::cout << "it arithmetics " << *(1 + cit) << "\n";
	std::cout << "it arithmetics, distance " << cit - (cit - 2)  << "\n";

	unsigned int size = toIter.size();
	for (unsigned int i = 0; i < size; i++)
		std::cout << toIter[i] << " ";
	std::cout << "\n";

	it = toIter.begin() + 3;
	std::cout << *it << "\n";
	std::cout << it - toIter.begin() << "\n";
	//toIter.erase(it);

	//std::cout << *(toIter.begin() + 1)<< " begin\n";
	it = toIter.begin() + 2;
	toIter.insert(it, 2, 6);

	size = toIter.size();
	for (unsigned int i = 0; i < size; ++i)
		std::cout << toIter[i] << " ";
	std::cout << "\n";
	std::cout << "\n";

	ft::vector<int>::iterator	lil = toIter.begin();

	*/
	//std::cout << <<;
	/*
	std::vector<int>	svc(3, 5);
	std::vector<int>::const_iterator	sit = svc.begin();

	std::cout << *sit << "\n";

	ft::vector<int>		vc(3, 5);
	ft::vector<int>::const_iterator	it = vc.begin();

	std::cout << *it << "\n";
	*/

	std::cout << "\n";

	std::list<int>		lst;

	lst.push_back(2);
	lst.push_back(4);
	lst.push_back(7);

	std::vector<int>		rr;

	rr.push_back(2);
	rr.push_back(4);
	rr.push_back(7);


	ft::vector<int>	r(lst.begin(), lst.end());
	std::cout << r[0] << "\n";

	//ft::vector<int>	rrr(2, 3);
	
	ft::RBTree<int>	tree;

	tree.tree_insert(tree.getRoot(), 8);
	tree.tree_insert(tree.getRoot(), 3);
	tree.tree_insert(tree.getRoot(), 2);
	tree.tree_insert(tree.getRoot(), -1);
	tree.tree_insert(tree.getRoot(), 9);
	//tree.tree_insert(tree.getRoot(), 9);
	tree.tree_print(tree.getRoot());
	std::cout << "\n";
	return 0;
}
