//#include "../system/system_methods.ipp"
//#include "__service.ipp"
#include "../vector.hpp"
#include <vector>

template <class T>
	void	printContainer( T v ) {
		std::vector<int>::const_iterator	it = v.begin();
		std::vector<int>::const_iterator	ite = v.end();

		for (; it != ite; ++it)
			std::cout << *it << " ";
		std::cout << "\n";
	}

template <class T>
int run_vector_unit_test(std::string test_name, std::vector<int> (func1)(std::vector<T>), std::vector<int> (func2)(ft::vector<T>)) {
    int    result;
    int    leaks;
    time_t t1;
    time_t t2;
    std::vector<int > res1;
    std::vector<int > res2;
    std::vector<int> vector;
	ft::vector<int> my_vector;

	//printElement(test_name);
	res1 = func1(vector);
	//std::cout << "HERE\n";
	res2 = func2(my_vector);
	//std::cout << "HERE2\n";
	if (res1 == res2) {
	    //printElement("OK");
		std::cout << "OK\n";
		result = 0;
	}
	else {
	    //printElement("FAILED");
		std::cout << "\n";
		printContainer(res1);
		std::cout << "\n";
		printContainer(res2);
		std::cout << "Failed\n";
	    result = 1;
	}
	/*
	t1 = g_end1 - g_start1, t2 = g_end2 - g_start2;
	(t1 >= t2) ? printElement(GREEN + std::to_string(t2) + "ms" + RESET) : printElement(REDD + std::to_string(t2) + "ms" + RESET);
	(t1 > t2) ? printElement(REDD + std::to_string(t1) + "ms" + RESET) : printElement(GREEN + std::to_string(t1) + "ms" + RESET);
	leaks = leaks_test(getpid());
	cout << endl;
	*/

	//return !(!result && !leaks);
	return result;
}

///////////// insert test ///////////////
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
    //g_start1 = timer();
    v.push_back(*(vector.insert(vector.end() - 8000000, 44)));
    //g_end1 = timer();
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    std::vector<A> vv;
    std::vector<B*> v1;

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    catch (...) {
		std::cout << "EMMM\n";
    	v.push_back(vv.size());
    	v.push_back(vv.capacity());
    }
    return v;
}

template <typename T>
std::vector<int> insert_test_1(ft::vector<T> vector) {
	std::cout << "HERE3\n";
    std::vector<int> v;
    vector.assign(26000000, 1);
    //g_start2 = timer();
    v.push_back(*(vector.insert(vector.end() - 8000000, 44)));
    //g_end2 = timer();
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
	ft::vector<A> vv;
	ft::vector<B*> v1;

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    catch (...) {
    	v.push_back(vv.size());
    	v.push_back(vv.capacity());
		//std::cout << "ermm\n";
    }
	std::cout << "HERE3\n";
	std::cout << v[1] << "\n";
    return v;
}

int main() {

    exit(run_vector_unit_test<int>("insert(value)", insert_test_1, insert_test_1));
}

////////

/*
template <typename T>
std::vector<int> erase_test_2(std::vector<T> vector) {
    std::vector<int> v;
    for (int i = 0; i < 99000000; ++i)
        vector.push_back(i);
    //g_start1 = timer();
    v.push_back(*(vector.erase(vector.begin() + 80000, vector.end() - 15000000)));
    //g_end1 = timer();
    v.push_back(*(vector.begin() + 82000));
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> erase_test_2(ft::vector<T> vector) {
    std::vector<int> v;
    for (int i = 0; i < 99000000; ++i)
        vector.push_back(i);
    //g_start2 = timer();
    v.push_back(*(vector.erase(vector.begin() + 80000, vector.end() - 15000000)));
    //g_end2 = timer();
    v.push_back(*(vector.begin() + 82000));
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

int main() {

    exit(run_vector_unit_test<int>("erase(range)", erase_test_2, erase_test_2));
}
*/
/*
template <typename T>
std::vector<int> resize_test(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(99000000, 1);
//    g_start1 = timer();
    vector.resize(50000000);
    vector.reserve(50000000);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.resize(70000000);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.resize(153000000, T());
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    v.push_back(vector[65]);
    //g_end1 = timer();
    return v;
}

template <typename T>
std::vector<int> resize_test(ft::vector<T> vector) {
    std::vector<int> v;
    vector.assign(99000000, 1);
   // g_start2 = timer();
    vector.resize(50000000);
    vector.reserve(50000000);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.resize(70000000);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << "testing reserve before\n";
	std::cout << vector.capacity() << " HERE IN\n";
    vector.resize(153000000, T());
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << vector.capacity() << " HERE IN\n";
    v.push_back(vector[65]);
   // g_end2 = timer();
    return v;
}

int main() {

    //exit(run_vector_unit_test<int>("resize()", resize_test, resize_test));
}
*/
