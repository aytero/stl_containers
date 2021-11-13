#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{
	template <class T1, class T2>
		struct pair;

	template <class T1, class T2>
		pair<T1,T2> make_pair( T1 x, T2 y );

	template < class InputIt1, class InputIt2 >
		bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 );

	template < class InputIt1, class InputIt2, class BinaryPredicate >
		bool equal( InputIt1 first1, InputIt1 last1,
					InputIt2 firsr2, BinaryPredicate pred);

	template < class InputIt1, class InputIt2 >
		bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
									InputIt2 first2, InputIt2 last2 );

	template < class InputIt1, class InputIt2, class Compare >
		bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
									InputIt2 first2, InputIt2 last2, Compare comp );
}

template < class InputIt1, class InputIt2 >
	bool ft::equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 ) {
		while (first1 != last1) {
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

template < class InputIt1, class InputIt2, class BinaryPredicate >
	bool ft::equal( InputIt1 first1, InputIt1 last1,
				InputIt2 first2, BinaryPredicate pred) {
		while (first1 != last1) {
			if (!(pred(*first1, *first2)))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

template < class InputIt1, class InputIt2 >
	bool ft::lexicographical_compare( InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2 ) {
		while (first1 != last1) {
			if (first2 != last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

template < class InputIt1, class InputIt2, class Compare >
	bool ft::lexicographical_compare( InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2, Compare comp ) {
		while (first1 != last1) {
			if (first2 != last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}


template <class T1, class T2>
	ft::pair<T1,T2> ft::make_pair( T1 x, T2 y ) {
		return ft::pair<T1, T2>(x, y);
	}

template <class T1, class T2>
	struct ft::pair {
		T1	first;
		T2	second;
	
		typedef T1	first_type;
		typedef T2	second_type;
	
		pair() : first(T1()), second(T2()) {}
	
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

#endif
