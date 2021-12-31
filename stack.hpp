#ifndef __STACK_HPP__
# define __STACK_HPP__

# include "vector.hpp"

namespace ft
{
	template < class T, class Container = ft::vector<T> >
	class stack;
}

template < class T, class Container >
class ft::stack {
	public:
		typedef typename Container::value_type	value_type;
		typedef typename Container::size_type	size_type;
		typedef Container						container_type;

		explicit stack( const container_type& cont = container_type() ) : c(cont) {}

		stack( const stack& ref ) : c(ref.c) {}

		virtual ~stack() {}

		stack& operator=( const stack &other ) {
			if (this != &other)
				c = other.c;
			return (*this);
		}

		value_type&			top( void ) {
			return c.back();
		}

		const value_type&	top( void ) const {
			return c.back();
		}

		bool		empty( void ) const {
			return c.empty();
		}

		size_type	size() const {
			return c.size();
		}

		void	push( const value_type& val ) {
			c.push_back(val);
		}

		void	pop( void ) {
			c.pop_back();
		}

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
	return !(rhs < lhs);
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
