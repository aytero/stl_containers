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

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

template <typename T>
	void stack_print( const ft::stack<T> &st ) {
		std::cout << "size: " << st.size() << std::endl;
		std::cout << "content: " << st.top() << std::endl;
	}

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

template <typename T>
std::string print_pair( const T &iterator, std::ostream &o = std::cout) {
	o << "key: " << iterator->first << " | value: " << iterator->second;
	o << std::endl;
	return "";
}

template <typename M>
	void map_print( const M &mp ) {
		std::cout << "size: " << mp.size() << std::endl;
		
		typename M::const_iterator it = mp.begin();
		typename M::const_iterator ite = mp.end();
		std::cout << "content: ";
		for (; it != ite; ++it)
			std::cout << "- " << print_pair(it) << std::endl;
		std::cout << std::endl;
	}

template <typename S>
	void set_print( const S &st ) {
		std::cout << "size: " << st.size() << std::endl;
		
		typename S::const_iterator it = st.begin();
		typename S::const_iterator ite = st.end();
		std::cout << "content: ";
		for (; it != ite; ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

void subject_test() {

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
}

void stack_test() {
	std::cout << "\nSTACK test\n";

	ft::stack<int> st;
	st.push(rand());
	st.push(rand());
	stack_print(st);

	const ft::stack<int> st_copy(st);
	stack_print(st_copy);

	st.push(rand());
	stack_print(st_copy);

	st = st_copy;
	stack_print(st);

	std::cout << st.top() << std::endl;
	std::cout << st.empty() << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << "Relational operators: " << (st == st_copy) << (st != st_copy)
				<< (st < st_copy) << (st >= st_copy) << std::endl;
	st.pop();
	std::cout << st.top() << std::endl;
	stack_print(st);
}

void vector_test() {
	std::cout << "\nVECTOR test\n";

	ft::vector<int> v_empty;
	ft::vector<int> v_fill(5, 80);
	ft::vector<int> v_count(20);
	for (int i = 0; i < 20; ++i)
		v_count[i] = rand();
	ft::vector<int> v_range(v_fill.begin(), v_fill.end());
	const ft::vector<int> v_copy(v_count);
	vector_print(v_fill);
	vector_print(v_count);
	vector_print(v_copy);

	ft::vector<int> v_iter(++(++v_copy.begin()), --(--v_copy.end()));
	vector_print(v_iter);

	ft::vector<int> v(1);
	v = v_iter;
	vector_print(v);

	std::allocator<int> alloc = v.get_allocator();
	std::allocator<int> alloc1 = v_iter.get_allocator();
	std::cout << (alloc == alloc1) << std::endl;

	int *data_ptr = v_count.data();
	std::cout << data_ptr[0] << std::endl;
	const int *data_ptr_const = v_copy.data();
	std::cout << data_ptr_const[0] << std::endl;

	std::cout << v_copy.size() << std::endl;
	std::cout << v_copy.capacity() << std::endl;
	std::cout << v_iter.max_size() << std::endl;
	std::cout << v.empty() << std::endl;

	std::cout << v.front() << std::endl;
	std::cout << v_copy.front() << std::endl;
	std::cout << v.back() << std::endl;
	std::cout << v_copy.back() << std::endl;

	std::cout << v[4] << std::endl;
	std::cout << v_copy[4] << std::endl;
	std::cout << v.at(5) << std::endl;
	std::cout << v_copy.at(5) << std::endl;

	v_iter.reserve(500);
	vector_print(v_iter);
	v_iter.clear();
	vector_print(v_iter);
	v_iter.push_back(rand());
	vector_print(v_iter);
	v_iter.pop_back();
	vector_print(v_iter);
	v_iter.resize(20);
	vector_print(v_iter);
	v_iter.resize(40, rand());
	vector_print(v_iter);
	
	v.swap(v_iter);
	vector_print(v_iter);
	vector_print(v);

	v.assign(42, rand());
	vector_print(v);
	v.assign(v_copy.begin(), v_copy.end());
	vector_print(v);
	v.insert(v.begin() + 5, rand());
	vector_print(v);
	v.insert(v.begin() + 4, 4, rand());
	vector_print(v);
	v.insert(v.begin() + 8, v_copy.begin() + 1, v_copy.begin() + 3);
	vector_print(v);

	ft::vector<int>::iterator it = v.erase(v.begin());
	vector_print(v);
	it = v.erase(v.end() - 2, v.end());
	vector_print(v);
}

void map_test() {
	std::cout << "\nMAP test\n";

	ft::map<int, int> mp;
	mp[21] = rand();
	mp[42] = rand();
	map_print(mp);

	ft::map<int, int> map_iter(++mp.begin(), mp.end());
	map_print(map_iter);

	const ft::map<int, int> map_copy(mp);
	map_print(map_copy);
	mp = map_iter;
	map_print(mp);

	std::cout << map_copy.at(21) << std::endl;
	std::cout << map_copy.empty() << std::endl;
	mp.clear();
	map_print(mp);

	mp.insert(ft::make_pair(21, rand()));
	map_print(mp);
	mp.insert(mp.begin(), ft::make_pair(88, rand()));
	map_print(mp);
	map_iter.insert(mp.begin(), mp.end());
	map_print(map_iter);

	map_iter.erase(map_iter.begin());
	map_print(map_iter);
	map_iter.erase(++map_iter.begin(), map_iter.end());
	map_print(map_iter);
	map_iter.erase(map_iter.begin()->first);
	map_print(map_iter);

	map_iter.swap(mp);
	map_print(map_iter);
	map_print(mp);
}

void set_test() {
	std::cout << "\nSET test\n";

	ft::set<int> set_;

	set_.insert(rand());
	set_.insert(rand());
	set_print(set_);

	ft::set<int> set_iter(++set_.begin(), set_.end());
	set_print(set_iter);

	const ft::set<int> set_copy(set_);
	set_print(set_copy);
	set_ = set_iter;
	set_print(set_);

	std::cout << set_copy.empty() << std::endl;
	set_.clear();
	set_print(set_);

	set_.insert(rand());
	set_print(set_);
	set_.insert(set_.begin(), rand());
	set_print(set_);
	set_iter.insert(set_.begin(), set_.end());
	set_print(set_iter);

	set_iter.erase(set_iter.begin());
	set_print(set_iter);
	set_iter.erase(++set_iter.begin(), set_iter.end());
	set_print(set_iter);
	set_iter.erase(*set_iter.begin());
	set_print(set_iter);

	set_iter.swap(set_);
	set_print(set_iter);
	set_print(set_);
}

int main(int argc, char** argv) {

	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}

	std::cout << std::endl;
	std::cout << "-------- " << NMSP << " --------" << std::endl;
	const int seed = atoi(argv[1]);
	srand(seed);
	const clock_t begin_time = clock();

	subject_test();
	stack_test();
	vector_test();
	map_test();
	set_test();


	std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << " s" << std::endl;
	return (0);
}
