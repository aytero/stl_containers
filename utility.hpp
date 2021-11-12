#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{
	template <class T1, class T2>
		struct pair;

	template <class T1, class T2>
		pair<T1,T2> make_pair( T1 x, T2 y );
}

/*
template < class InputIterator1, class InputIterator2 >
bool equal( InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2 ) {
	;
}
*/

/*
template < class InputIterator1, class InputIterator2, class BinaryPredicate >
bool equal( InputIterator1 first1, InputIterator1 last1,
			inputIterator2 firsr2, BinaryPredicate pred) {}
*/

/*
template < class InputIterator1, class InputIterator2 >
	bool lexicographical_compare( InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2 ) {
		;
	}
*/

template <class T1, class T2>
struct ft::pair {
	T1	first;// key
	T2	second;// val

	typedef T1	first_type;
	typedef T2	second_type;

	pair() : first(T1()), second(T2()) {}

	// copy
	template < class U, class V >
		pair( const pair<U,V>& b ) : first(b.first), second(b.second) {}

	pair( const first_type& a, const second_type& b ) : first(a), second(b) {}

	pair& operator=( const pair &pr ) {
		if (this == &pr)
			return *this;
		first = pr.first;
		second = pr.second;
		return *this;
	}
};

template <class T1, class T2>
	bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

template <class T1, class T2>
	bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
		return !(lhs == rhs);
	}

template <class T1, class T2>
	bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

template <class T1, class T2>
	bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
		return !(rhs < lhs);
	}

template <class T1, class T2>
	bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
		return rhs < lhs;
	}

template <class T1, class T2>
	bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
		return !(lhs < rhs);
	}


template <class T1, class T2>
	ft::pair<T1,T2> ft::make_pair( T1 x, T2 y ) {
		return ft::pair<T1, T2>(x, y);
	}

#endif
