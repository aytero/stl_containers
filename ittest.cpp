#include <iostream>

class vect {
	
public:
	class	const_it {
	
		public:
			const_it() : n(1) {}
	
			int		getN() { return n; }
	
		protected:
			int	n;
	};
	
	class	it : public const_it {
		//protected:
		//	int	n;
	
		public:
			it() { n = 8; }
	
			int		getN() { return n; }
			int		some() {
				return n + n;
			}
	};

private:
	int la;

};

int	main() {

	vect::const_it	cit;
	vect::it	it;

	std::cout << it.getN() << "\n";
	std::cout << it.some() << "\n";
}
