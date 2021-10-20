#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

#include <memory>
#include <iostream>
#include <exception>
#include <iterator>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector;
}

template < class T, class Alloc >
class ft::vector {

	public:
		typedef T					value_type;
		typedef Alloc				allocator_type;
		//typedef reference		allocator_type::reference
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		//typedef iterator;
		//typedef ft::vector::const_iterator	const_iterator;
		//typedef reverse_iterator;
		//typedef const_reverse_iterator;
		typedef typename Alloc::difference_type	difference_type;
		typedef size_t				size_type;
		//typedef unsigned long		size_type;
		
	private:
		allocator_type	alloc_;
		size_type	capacity_;
		size_type	size_;
		pointer		arr_;

	public:
		// or make not nested/different files
		class const_iterator {
			//private:
			//	typedef const_iterator	cit;//????
			public:
				typedef typename Alloc::value_type			value_type;
				typedef typename Alloc::const_pointer		pointer;// const_pointer
				// const pointer ????
				typedef typename Alloc::const_reference		const_reference;
				typedef typename Alloc::difference_type		difference_type;
				typedef std::random_access_iterator_tag		iterator_category;

				const_iterator( pointer ptr = NULL ) : ptr_(ptr) {}
				//const_iterator( pointer elem ) : ptr_(elem) {}
				const_iterator( const const_iterator &ref ) : ptr_(ref.ptr_) {}
				virtual ~const_iterator() {}
				const_iterator& operator=( const const_iterator &other ) {
					if (this != &other)
						ptr_ = other.ptr_;
					return *this;
				}

				const_reference operator*() const { return *ptr_; }
				pointer operator->() const { return ptr_; }
				const_reference operator[]( size_type n ) const { return ptr_ + n; }

				bool	operator==( const const_iterator &rhs ) { return ptr_ == rhs.ptr_; }
				bool	operator!=( const const_iterator &rhs ) { return ptr_ != rhs.ptr_; }
				bool	operator<( const const_iterator &rhs ) { return ptr_ < rhs.ptr_; }
				bool	operator<=( const const_iterator &rhs ) { return ptr_ <= rhs.ptr_; }
				bool	operator>( const const_iterator &rhs ) { return ptr_ > rhs.ptr_; }
				bool	operator>=( const const_iterator &rhs ) { return ptr_ >= rhs.ptr_; }

				const_iterator& operator++() { ++ptr_; return *this; }
				const_iterator operator++( int ) { const_iterator tmp(*this); ++ptr_; return tmp; }
				const_iterator& operator--() { --ptr_; return *this; }
				const_iterator operator--( int ) { const_iterator tmp(*this); --ptr_; return tmp; }

				const const_iterator operator+( size_type n ) const { return const_iterator(ptr_ + n); }
				friend const_iterator operator+( size_type n, const const_iterator &c ) { return const_iterator(c.ptr_ + n); }
				const_iterator& operator+=( size_type n ){ ptr_ += n; return *this; }

				const const_iterator operator-( const size_type n ) const { return const_iterator(ptr_ - n); }
				friend const_iterator operator-( size_type n, const const_iterator &c ) { return const_iterator(c.ptr_ - n); }
				const const_iterator& operator-=( size_type n ) const { ptr_ -= n; return *this; }

			protected:
				pointer	ptr_;
		};

		class iterator : public const_iterator {
			//private:
			//	typedef const_iterator	cit;//????
			public:
				typedef typename Alloc::value_type		value_type;
				typedef typename Alloc::value_type*		pointer;
				typedef typename Alloc::reference		reference;
				typedef typename Alloc::difference_type	difference_type;
				typedef std::random_access_iterator_tag	iterator_category;

				iterator( pointer ptr = NULL ) : ptr_(ptr) {}
				iterator( const iterator &ref ) : ptr_(ref.ptr_) {}
				virtual ~iterator() {}
				iterator& operator=( const iterator &other ) {
					if (this != &other)
						ptr_ = other.ptr_;
					return *this;
				}

				reference operator*() const { return *ptr_; }
				pointer operator->() const { return ptr_; }
				reference operator[]( size_type n ) const { return ptr_ + n; }

				//bool	operator==( const iterator &rhs ) { return ptr_ == rhs.ptr_; }
				//bool	operator!=( const iterator &rhs ) { return ptr_ != rhs.ptr_; }
				//bool	operator<( const iterator &rhs ) { return ptr_ < rhs.ptr_; }
				//bool	operator<=( const iterator &rhs ) { return ptr_ <= rhs.ptr_; }
				//bool	operator>( const iterator &rhs ) { return ptr_ > rhs.ptr_; }
				//bool	operator>=( const iterator &rhs ) { return ptr_ >= rhs.ptr_; }

				iterator& operator++() { ++ptr_; return *this; }
				iterator operator++( int ) { iterator tmp(*this); ++ptr_; return tmp; }
				iterator& operator--() { --ptr_; return *this; }
				iterator operator--( int ) { iterator tmp(*this); --ptr_; return tmp; }

				const iterator operator+( size_type n ) const { return iterator(ptr_ + n); }
				friend iterator operator+( size_type n, const iterator &c ) { return iterator(c.ptr_ + n); }
				iterator& operator+=( size_type n ){ ptr_ += n; return *this; }

				const iterator operator-( const size_type n ) const { return iterator(ptr_ - n); }
				friend iterator operator-( size_type n, const iterator &c ) { return iterator(c.ptr_ - n); }
				const iterator& operator-=( size_type n ) const { ptr_ -= n; return *this; }

			//protected:
			//	pointer	ptr_;
		};
	

		// default
		explicit vector( const allocator_type& alloc = allocator_type() )
			: alloc_(alloc), capacity_(0), size_(0), arr_(NULL) {}

		// fill
		explicit vector( size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type() ) 
				: alloc_(alloc), capacity_(n), size_(n), arr_(alloc_.allocate(n)) {
			for (size_type i = 0; i < size_; i++)
				arr_[i] = val;
				//arr_ + i = val;
			std::cout << "fill\n";
		}
		/*
		// range
		template < class InputIterator >
		vector( InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type() ) 
				: alloc_(alloc), capacity_(0), size_(0), arr_(NULL) {

			assign(first, last);
			std::cout << "range\n";
		}
		*/

		// copy constr
			//: alloc_(x.alloc_), capacity_(x.capacity_), size_(x.size_)//, arr_(x.arr_)
		vector( const vector& x ) : alloc_(0), capacity_(0), size_(0), arr_(NULL) { *this = x; }

		virtual ~vector() 
		{
			//clear(); // instead of for loop ?
			for (size_type i = 0; i < size_; i++)
				alloc_.destroy(arr_ + i);
			if (arr_)
				alloc_.deallocate(arr_, capacity_);
		}
		
		vector&	operator=( const vector &other ) {
			if (this == &other)
				return *this;

			// free before
			clear();
			//alloc;
			reserve(other.size_);
			alloc_ = other.alloc_;
			capacity_ = other.capacity_;
			size_ = other.size_;
			for (size_type i = 0; i < size_; i++)
				arr_[i] = other.arr_[i];
			return *this;
		}


		// iterators
		//iterator		begin( void ) { return iterator(arr_); }
		const_iterator	begin( void ) const { return const_iterator(arr_); }

		//iterator		end( void ) { return iterator(arr_ + size_); }
		const_iterator	end( void ) const { return const_iterator(arr_ + size_); }
		/*

		reverse_iterator		rbegin( void );
		const_reverse_iterator	rbegin( void ) const;

		reverse_iterator		rend( void );
		const_reverse_iterator	rend( void ) const;

		*/

		// allocator
		allocator_type get_allocator() const { return alloc_; }
		// capacity:
		size_type	size() const { return size_; }
		size_type	max_size() const { return alloc_.max_size(); }
		size_type	capacity() const { return capacity_; }
		bool		empty() const { return size_ == 0;}
		
		void	reserve( size_type n ) {
			if (n <= capacity_)
				return ;

			size_type	new_cap;
			pointer		new_arr;

			new_cap = n;// or size_ * 2
			//new_cap = std::max(size_ * 2, n);
			new_arr = alloc_.allocate(new_cap);
			for (size_type i = 0; i < size_; i++)
				new_arr[i] = arr_[i];
			if (arr_)
				alloc_.deallocate(arr_, capacity_);
			capacity_ = new_cap;
			arr_ = new_arr;
		}

		void	resize( size_type n, value_type val = value_type() ) {
			//if (size_ > n) {
			//	size_ = n;
			//}
			//	;// reduce size to n
			//else if (n > size_ && n <= capacity_)
			//	;//fill with val
			//else
			//	;//reserve
			reserve(n);
			while (size_ < n)
				arr_[size_++] = val;
			size_ = n;
		}

		// element access
		reference		operator[] ( size_type n ) { return (arr_[n]); }
		const_reference	operator[] ( size_type n ) const { return arr_[n]; }
		reference		at( size_type n ) {
			if (n >= size_ || n < 0)
				throw ( std::out_of_range("vector") );
			return (arr_[n]);
		}
		const_reference	at( size_type n ) const {
			if (n >= size_ || n < 0)
				throw ( std::out_of_range("vector") );
			return (arr_[n]);
		}
		reference		front() { return arr_[0]; }
		const_reference	front() const { return arr_[0]; }
		reference		back() { return arr_[size_ - 1]; }
		const_reference	back() const { return arr_[size_ - 1]; }


		// modifiers
		template < class InputIterator >
		void	assign( InputIterator first, InputIterator last ) {
			
			clear();
			size_type	new_size = std::distance(first, last);
			reserve(new_size);
			size_ = new_size;

			size_type	i = 0;
			while (first != last) {
				arr_[i++] = *first;
				++first;
			}
		}

		void	assign( size_type n, const value_type& val ) {
			clear();
			resize(n, val);
		}

		void	push_back( const value_type& val ) {
			if (size_ == capacity_)
				;//resize reserve()
			arr_[size_] = val;
			size_++;
			//arr_[size_++] = val;
		}
		void	pop_back() { size_--; }

/*
		// single elem
		iterator	insert( iterator position, const value_type& val ) {}
		// fill
		void		insert( iterator position, size_type n, const value_type& val ) {}
		// range
		template < class InputIterator >
		void		insert( iterator position, InputIterator first, InputIterator last ) {}
		iterator erase( iterator position ) {
			if (position != ite)
				// reallocate
			size_--;
		}
		iterator erase( iterator first, iterator last );

		swap();
		*/
		void	clear() {
			for (size_type i = 0; i < size_; i++)
				alloc_.destroy(arr_[i]);
				//alloc_.destroy(arr_ + i);
			size_ = 0;
		}
};

template< class T, class Alloc >
bool operator==( const ft::vector<T, Alloc>& lhs,
				const ft::vector<T, Alloc>& rhs) {
	//size_type	size = lhs.size();
	unsigned int	size = lhs.size();
	if (size != rhs.size())
		return false;

	//for (size_type i = 0; i < size; i++) {
	//	if (lhs[i] != rhs[i])
	//		return false;
	//}
	//return true;
	
	//size_type	i = 0;
	// unsigned long
	unsigned int	i = 0;
	while (i < size && lhs[i] == rhs[i])
		i++;
	return i == size;
}

template< class T, class Alloc >
bool operator!=( const ft::vector<T, Alloc>& lhs,
				const ft::vector<T, Alloc>& rhs) {
	return !(lhs == rhs);
}

/*
template< class T, class Alloc >
bool operator<( const vector<T, Alloc>& lhs,
				const vector<T, Alloc>& rhs) {
	return ;
}

template< class T, class Alloc >
bool operator<=( const vector<T, Alloc>& lhs,
				const vector<T, Alloc>& rhs) {
	return !(rhs <= lhs);
}

template< class T, class Alloc >
bool operator>( const vector<T, Alloc>& lhs,
				const vector<T, Alloc>& rhs) {
	return rhs < lhs;
}

template< class T, class Alloc >
bool operator>=( const vector<T, Alloc>& lhs,
				const vector<T, Alloc>& rhs) {
	return !(lhs < rhs);
}
*/

template < class T, class Alloc >
void	swap( ft::vector<T, Alloc>& x, ft::vector<T, Alloc>& y) {
	x.swap(y);
	// may leave like this but prob better to reimplement 
	//or it calls iternal swap which i should write
}

#endif
