#include <iostream>

class Number {

	int		n;

	public:
		Number( int num ) : n(num) {}
		int	get_num() const { return n; }
};

class Point {
	
	Number	*x;
	Number	*y;

	public:

		Point( int t_x, int t_y ) : x(new Number(t_x)), y(new Number(t_y)) {}
		~Point() { delete x; delete y; }

		Point	operator=( const Point & obj ) {
			this->~Point();
			new (this) Point(obj.get_x(), obj.get_y());
			return *this;
		}

		int	get_x() const { return x->get_num(); }
		int	get_y() const { return y->get_num(); }
};


int	main() {

	Point	pt(5, 8);
	Point	pt1(3, 4);


	std::cout << pt.get_x() << " " << pt.get_y() << "\n";
	pt = pt;
	std::cout << pt.get_x() << " " << pt.get_y() << "\n";
	std::cout << pt1.get_x() << " " << pt1.get_y() << "\n";
}
