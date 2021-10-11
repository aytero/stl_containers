#ifndef __STACK_HPP__
# define __STACK_HPP__

//# pragma once
//# include "vector.hpp"
#include <vector>

namespace ft
{
	//template < class T, class Container = ft::vector<T> >
	template < class T, class Container = std::vector<T> >
	class stack;
}

// or ft::list<T>
//template < class T, typename Container = ft::vector<T> >
template < class T, class Container >
class ft::stack {
	public:
		// member types
		//typedef T			value_type;
		typedef typename Container::value_type	value_type;
		typedef Container	container_type;
		//typedef size_t		size_type;// or unsigned int
		typedef typename Container::size_type	size_type;


		// probably from c++11
		//typedef T& referense;
		//typedef const T& const_referense;

		// member funcs
		// explicit Stack(); constructor
		stack( const container_type& cntr = container_type() ) : c(cntr) {}
		stack( const stack& ref ) : c(ref.c) {}
		virtual ~stack() {}
		stack& operator=( const stack &other ) {
			if (this != &other)
				c = other.c;
			return (*this);
		}

		//referense		top( void ) { return this->c.back(); }
		//const_referense	top( void ) const {}
		value_type&			top( void ) { return c.back(); }
		const value_type&	top( void ) const { return c.back(); }

		bool		empty( void ) const { return c.empty(); }
		size_type	size() const{ return c.size(); }

		void	push( const value_type& val ) { c.push_back(val); }
		void	pop( void ) { c.pop_back(); }


		// == and < put in class, with friend spec, and make others logical variations of theese two
		// like templates after class
		// why?

		// non-member funcs, use friend
		friend bool operator==( const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return lhs.c == rhs.c;
		}

		friend bool operator<( const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return lhs.c < rhs.c;
		}

	protected:
		container_type	c;
};

template < class T, class Container >
bool operator!=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
	return !(lhs == rhs);
}

template < class T, class Container >
bool operator<=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
	return !(rhs <= lhs);
}

template < class T, class Container >
bool operator>( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
	return rhs < lhs;
}

template < class T, class Container >
bool operator>=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
	return !(lhs < rhs);
}


#endif
