#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

#include <memory>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector;
}

template < class T, class Alloc >
class ft::vector {

	public:
		//typedef typename
		typedef T					value_type;
		typedef Alloc				allocator_type;
		//typedef reference		allocator_type::reference
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		//typedef iterator;
		//typedef const_iterator;
		//typedef reverse_iterator;
		//typedef const_reverse_iterator;
		//typedef difference_type;
		typedef size_t				size_type;
		//typedef unsigned long		size_type;
		
	private:
		pointer		arr_;
		size_type	size_;
		size_type	capacity_;

	public:
		// or make not nested/different files
		/*
		template <>
		class const_iterator {
			public:
				const_iterator();
				const_iterator( const const_iterator &ref );
				virtual ~const_iterator();
				const_iterator& operator=( const const_iterator &rhs );

				// dereference * and ->
				// += and -=
				// arithmetic operators it and int or it and it
				// increments
				// relational operators
				// operator[]
				// const operator[]
		}

		class iterator : public const_iterator() {
		}
		*/

		explicit vector( const allocator_type& alloc = allocator_type() ) : size_(0), capacity_(0) {
			arr_ = alloc.allocate(0);
			// or arr(0)
			//(void)alloc;
		}

		explicit vector( size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type() ) {
			(void)n;
			(void)val;
			(void)alloc;
		}
		virtual ~vector() {};
		//operator=();

		// iterators
		/*
		iterator		begin( void );
		iterator		end( void );
		const_iterator	begin( void ) const;
		const_iterator	end( void ) const;

		reverse_iterator		rbegin( void );
		reverse_iterator		rend( void );
		const_reverse_iterator	rbegin( void ) const;
		const_reverse_iterator	rend( void ) const;

		// capacity:
		size_type	size() const;
		size_type	max_size() const;
		void		resize( size_type n, value_type val = value_type() );
		size_type	capacity() const;
		bool		empty() const;
		void		reserve( size_type n );

		// element access
		reference		operator[] ( size_type n );
		const_reference	operator[] ( size_type n ) const;
		reference		at( size_type n );
		const_reference	at( size_type n ) const;// like [] but throws exception
		reference		front();
		const_reference	front() const;
		reference		back();
		const_reference	back() const;

		// modifiers
		assign();
		push_back();
		pop_back();
		insert();
		erase();
		swap();
		clear();

		// allocator
		get_allocator();

		// non-member funcs
		// friend operators
		// swap
		template< class T, class Alloc >
		bool operator==( const vector<T, Alloc>& lhs,
								const vector<T, Alloc>& rhs) {
			return ;
		}

		template< class T, class Alloc >
		bool operator!=( const vector<T, Alloc>& lhs,
								const vector<T, Alloc>& rhs) {
			return ;
		}

		template< class T, class Alloc >
		bool operator<( const vector<T, Alloc>& lhs,
								const vector<T, Alloc>& rhs) {
			return ;
		}

		template< class T, class Alloc >
		bool operator<=( const vector<T, Alloc>& lhs,
								const vector<T, Alloc>& rhs) {
			return ;
		}

		template< class T, class Alloc >
		bool operator>( const vector<T, Alloc>& lhs,
								const vector<T, Alloc>& rhs) {
			return ;
		}

		template< class T, class Alloc >
		bool operator>=( const vector<T, Alloc>& lhs,
								const vector<T, Alloc>& rhs) {
			return ;
		}

		template < class T, class Alloc >
		void	swap( vector<T, Alloc>& x, vector<T, Alloc>& y);
		*/
};

#endif
