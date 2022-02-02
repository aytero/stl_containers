#include "vector.hpp"
#include "stack.hpp"
#include <iostream>
#include <vector>

#include "utility.hpp"
#include "type_traits.hpp"

#include <list>//
#include "map.hpp"
#include "set.hpp"
#include "rbtree.hpp"

template <class V>
void	print_vector( V v ) {

	std::vector<int>::const_iterator	it = v.begin();
	std::vector<int>::const_iterator	ite = v.end();

	for (; it != ite; ++it) {
		std::cout << *it << " ";
	}
	std::cout << "\n";
}

class B {
public:
	char *l;
	int i;
	B():l(nullptr), i(1) {};
	B(const int &ex) {
		this->i = ex;
		this->l = new char('a');
	};
	virtual ~B() {
		delete this->l;
		this->l = nullptr;
	};
};

class A : public B {
public:
	A():B(){};
	A(const B* ex){
		this->l = new char(*(ex->l));
		this->i = ex->i;
		if (ex->i == -1) throw "n";
	}
	~A() {
		delete this->l;
		this->l = nullptr;
	};
};

template <typename T>
std::vector<int> insert_test_1(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(26000000, 1);
    v.push_back(*(vector.insert(vector.end() - 8000000, 44)));
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    std::vector<A> vv;
    std::vector<B*> v1;

	std::cout << &(*k4) << "\n";

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));

	try {
    	vv.insert(vv.begin(), v1.begin(), v1.end());
	}
	catch ( char const * e ) {
		std::cout << e << "\n";
		std::cout << "EXC\n";
	}
	return v;
}

int	main() {


	std::vector<int> v;

	insert_test_1(v);
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

	mp.erase(mp.begin(), mp.end());
	mp.erase(1);

	return 0;
}
