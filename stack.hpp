#ifndef __STACK_HPP__
# define __STACK_HPP__

//# include "vector.hpp"
#include <vector>

//namespace ft;

// or ft::list<T>
//template < class T, typename Container = ft::vector<T> >// class stack;
template < class T, typename Container = std::vector<T> >// class stack;
class stack {
	public:
		// member types
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;// or unsigned int

		// probably from c++11
		//typedef T& referense;
		//typedef const T& const_referense;

		// member funcs
		// explicit Stack(); constructor
		stack( const container_type& cntr = container_type() ) : c(cntr) {}
		virtual ~stack() {}
		stack& operator=( const stack &other ) {
			if (this != &other)
				this->c = other.c;
			return (*this);
		}

		//referense		top( void ) { return this->c.back(); }
		//const_referense	top( void ) const {}
		value_type&			top( void ) { return this->c.back(); }
		const value_type&	top( void ) const { return this->c.back(); }

		bool		empty( void ) const { return this->c.empty(); }
		size_type	size() const{ return this->c.size(); }

		void	push( const value_type& val ) { this->c.push_back(val); }
		void	pop( void ) { this->c.pop_back(); }


		// non-member funcs, use friend
		template< class Y, class C >
		friend bool operator==( const stack<Y, C>& lhs, const stack<Y, C>& rhs) {
			return lhs.c == rhs.c; // like this?
		}

		template< class Y, class C >
		friend bool operator!=( const stack<Y, C>& lhs, const stack<Y, C>& rhs) {
			return lhs.c != rhs.c;
		}

		template< class Y, class C >
		friend bool operator<( const stack<Y, C>& lhs, const stack<Y, C>& rhs) {
			return lhs.c < rhs.c;
		}

		/*
		template< class T, class Container >
		friend bool operator<=( const std::stack<T, Container>& lhs, const std::stack<T, Container>& rhs) {
			return lhs.c <= rhs.c;
		}

		template< class T, class Container >
		friend bool operator>( const std::stack<T, Container>& lhs, const std::stack<T, Container>& rhs) {
			return lhs.c > rhs.c;
		}

		template< class T, class Container >
		friend bool operator>=( const std::stack<T, Container>& lhs, const std::stack<T, Container>& rhs) {
			return lhs.c >= rhs.c;
		}
		*/
	
	protected:
		container_type	c;
};

#endif
