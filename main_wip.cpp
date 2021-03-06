#include <iostream>
#include <string>
#include <deque>
#include <ctime>
#ifdef ST//CREATE A REAL STL EXAMPLE
	#define NMSP "STD"
	#include <map>
	#include <stack>
	#include <vector>
	#include <set>
	namespace ft = std;
#else
#define NMSP "FT"
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
	#include "set.hpp"
	#include "utility.hpp"
#endif

template <typename T>
	void vector_print( const ft::vector<T> &vect ) {
		std::cout << "size: " << vect.size() << " capacity: " << vect.capacity() << std::endl;
		
		typename ft::vector<T>::const_iterator it = vect.begin();
		typename ft::vector<T>::const_iterator ite = vect.end();
		std::cout << "content: ";
		for (; it != ite; ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

int	main() {

	std::cout << "-------- " << NMSP << " --------" << std::endl;

	//ft::stack<int, std::vector<int> > st;
	//ft::stack<int, std::vector<int> > ste;
	ft::stack<int> st;
	ft::stack<int> ste;

	std::cout << (st == st) << "\n";

	//insert_test_1(v);
	ft::stack<int>	em;
	//ft::stack<int>	st;

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

	ft::vector<int> iters(vfill.begin(), vfill.end());

	iters.insert(iters.begin(), 1);

	v.reserve(100);
	v.begin();
	//std::cout << "elem [1]: " << vfillval[1] << "\n";
	//std::cout << "front:  " << vfillval.front() << "\n";
//	try {
//		vfill.at(9);
//	}
///	catch ( std::out_of_range& oor ) {
//		std::cerr << "Out of Range error: " << oor.what() << "\n";
//	}

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
*/
	/*
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
/*
	std::cout << "\n";

	std::list<int>		lst;

	lst.push_back(2);
	lst.push_back(4);
	lst.push_back(7);

	std::vector<int>		rr;

	rr.push_back(2);
	rr.push_back(4);
	rr.push_back(7);
	rr.push_back(8);
	rr.push_back(1);


	ft::vector<int>	r(rr.begin(), rr.end());
	//ft::vector<int>	r(lst.begin(), lst.end());
	std::cout << r[0] << "\n";

	ft::vector<int>	rrr(2, 3);
	
	std::cout << "\n";

	//rr.erase(rr.begin() + 2);
	rr.erase(rr.begin() + 2, rr.end());
	print_vector(rr);

	rr.insert(rr.begin(), 11);
	print_vector(rr);
	//rr.assign(3, 2);
	//rr.assign(rrr.begin(), rrr.end());
	//print_vector(rr);

	std::cout << "\n";

*/
	/*
	ft::RBTree<int>	tree;

	tree.insert(8);
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);
	//tree.insert(-1);
	tree.insert(4);
	tree.insert(9);

	tree.treePrint();
	std::cout << "\n";

	tree.insert(11);
	//tree.insert(-9);
	//tree.tree_insert(tree.getRoot(), 9);
	std::cout << "\n";

	tree.treePrint();
	std::cout << "\n\n";
	
	tree.deleteValue(4); // wrong balance
	// 2, 8 and 9 work ok
	tree.treePrint();

	//tree.rotateLeft(tree.getRoot());
	//tree.treePrint();
	
	ft::pair<int, std::string>	pr(1, "hi");
	ft::pair<int, std::string>	pr1(2, "hey");

	ft::pair<int, std::string>	pr2;
	pr2 = ft::make_pair(3, "hello");

	std::cout << (pr >= pr1) << "\n";
	std::cout << pr.first << ", " << pr.second << "\n";
	std::cout << pr2.first << ", " << pr2.second << "\n";
	*/

//	bool	ig = true;

//	if (ft::is_integral<ig>::value)
//		std::cout << "it's bool it's integral\n";




	ft::map<int, std::string> mp;
	mp.insert(ft::make_pair(1, "hello"));
	std::cout << mp.size() << "\n";
	//ft::map<int,std::string>::iterator it = mp.begin();
	std::cout << mp.begin()->first << ", " << mp.begin()->second << "\n";

	ft::map<int, std::string> mp1(mp);
	//ft::map<int, std::string> mp1(mp.begin(), mp.end());
	


	ft::set<int> setik;

	setik.size();

	setik.find(1);

	//std::vector<int> v;
	ft::map<int,int> mpt;

    for (int i = 0, j = 10; i < 30; ++i, ++j) {
        mpt.insert(ft::make_pair(i, j));
    }
	//ft::map<int, int> mp2(mp.begin(), mp.end());
	//ft::map<int, int>::iterator it = mp2.begin();
    //for (int i = 0; i < 5; ++i, it++) {
    //    v.push_back(it->first);
    //    v.push_back(it->second);
    //}

	std::cout << (mp < mp) << "\n";
	mp.equal_range(1);
	//mp.value_compare(1, 2);
	mp.insert(mp.begin(), ft::make_pair(2, "Hi"));

	ft::map<int,std::string>::iterator itik = --mp.end();
	//int bbb = --mp.end()->first;
	std::cout << itik->first << " --END\n";
	
	mp.erase(mp.begin(), --mp.end());

	mp.erase(mp.begin(), mp.end());
	mp.erase(1);

	ft::vector<int> vect;

	vect.reserve(2);
	std::cout << vect.capacity() << " capacity\n";
	vect.push_back(2);
	vect.push_back(5);
	vect.push_back(7);
	vect.push_back(1);
	vect.push_back(8);
	vector_print(vect);
	vect.erase(vect.begin());
	//vect.erase(vect.begin() + 1);
	//vect.erase(vect.end());
	//vect.erase(vect.begin(), vect.begin() + 2);
	//vect.erase(vect.begin() + 2, vect.end());

	ft::vector<int> vect_iter(vect.begin(), vect.end());
	vector_print(vect_iter);

	//vect_iter.reserve(10);
	vect_iter.insert(vect_iter.begin(), 3);
	vector_print(vect_iter);
	vect_iter.insert(vect_iter.begin() + 3, 27);
	vector_print(vect_iter);
	vect_iter.insert(vect_iter.begin(), 2, 2);
	vector_print(vect_iter);

	vect_iter.erase(vect_iter.begin());
	vector_print(vect_iter);
	vect_iter.erase(vect_iter.begin() + 1);
	vector_print(vect_iter);
	//std::cout << "END\n";
	//vect_iter.erase(vect_iter.end());
	//vector_print(vect_iter);
	//std::cout << "end\n";
	vect_iter.erase(vect_iter.begin(), vect_iter.begin() + 2);
	vector_print(vect_iter);
	vect_iter.erase(vect_iter.begin() + 2, vect_iter.end());
	vector_print(vect_iter);
return 0;
}
