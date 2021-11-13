#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

#include <memory>
#include <iostream>
#include <exception>
//#include <iterator>
#include "reverse_iterator.hpp"
#include "iterator_traits.hpp"
#include "utility.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
		class vector;
}

template < class T, class Alloc >
class ft::vector {

	public:
		typedef T								value_type;
		typedef Alloc							allocator_type;
		typedef typename Alloc::reference		reference;
		typedef typename Alloc::const_reference	const_reference;
		typedef typename Alloc::pointer			pointer;
		typedef typename Alloc::const_pointer	const_pointer;
		typedef typename Alloc::difference_type	difference_type;
		typedef size_t							size_type;
		//typedef iterator;
		//typedef ft::vector::const_iterator	const_iterator;
		//typedef reverse_iterator;
		//typedef const_reverse_iterator;
		//typedef unsigned long		size_type;

	private:
		allocator_type	alloc_;
		size_type	capacity_;
		size_type	size_;
		pointer		arr_;

	public:
		class const_iterator {
			public:
				typedef typename Alloc::value_type		value_type;
				typedef typename Alloc::pointer			pointer;// const_pointer
				//typedef typename Alloc::const_pointer	pointer;// const_pointer
				typedef typename Alloc::const_reference	reference;
				//typedef typename Alloc::const_reference	const_reference;
				typedef typename Alloc::difference_type	difference_type;
				typedef std::random_access_iterator_tag	iterator_category;

				const_iterator( pointer ptr = NULL ) : ptr_(ptr) {}
				const_iterator( const const_iterator &ref ) : ptr_(ref.ptr_) {}
				virtual ~const_iterator() {}
				const_iterator& operator=( const const_iterator &other ) {
					if (this != &other)
						ptr_ = other.ptr_;
					return *this;
				}

				reference operator*() const { return *ptr_; }
				pointer operator->() const { return ptr_; }
				reference operator[]( size_type n ) const { return ptr_ + n; }

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

				const const_iterator operator+( size_type n ) const
					{ return const_iterator(ptr_ + n); }
				friend const_iterator operator+( size_type n, const const_iterator &c )
					{ return const_iterator(c.ptr_ + n); }
				const_iterator& operator+=( size_type n ){ ptr_ += n; return *this; }

				difference_type operator-( const const_iterator &other )
					{ return ptr_ - other.ptr_; }
					//{ return other.ptr_ - ptr_; }
				const const_iterator operator-( const size_type n ) const
					{ return const_iterator(ptr_ - n); }
				friend const_iterator operator-( size_type n, const const_iterator &c )
					{ return const_iterator(c.ptr_ - n); }
				const const_iterator& operator-=( size_type n ) const { ptr_ -= n; return *this; }

			//private:
			protected:
				//pointer	ptr_;
				T*	ptr_;
		};

		class iterator : public const_iterator {
			public:
				typedef typename Alloc::value_type		value_type;
				typedef typename Alloc::pointer			pointer;
				typedef typename Alloc::reference		reference;
				typedef typename Alloc::difference_type	difference_type;
				typedef std::random_access_iterator_tag	iterator_category;

				iterator( pointer ptr = NULL ) : const_iterator(ptr) {
					ptr_ = ptr;
					//ptr_ = const_iterator::ptr_;
					//std::cout << iterator::ptr_ << " lils ptr   " << const_iterator::ptr_ << "\n";
				}
				iterator( const iterator &ref ) : const_iterator(ref) { ptr_ = ref.ptr_; }
				virtual ~iterator() {}
				iterator& operator=( const iterator &other ) {
					//return const_iterator::operator=(other);
					if (this != &other)
						ptr_ = other.ptr_;
					//const_iterator::ptr_ = other.const_iterator::ptr_;
					return *this;
				}

				reference operator*() { return *ptr_; }
				pointer operator->() { return ptr_; }
				reference operator[]( size_type n ) { return ptr_ + n; }

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
				friend iterator operator+( size_type n, const iterator &c )
					{ return iterator(c.ptr_ + n); }
				iterator& operator+=( size_type n ){ ptr_ += n; return *this; }

				difference_type operator-( const iterator &other )
					{
						//return const_iterator::operator-(other); }
						return ptr_ - other.ptr_; }
				const iterator operator-( const size_type n ) const
					{ return iterator(const_iterator::ptr_ - n); }
				friend iterator operator-( size_type n, const iterator &c )
					{ return iterator(c.const_iterator::ptr_ - n); }
				const iterator& operator-=( size_type n ) const
					{ const_iterator::ptr_ -= n; return *this; }

			//private:
			protected:
				// isnt it inhereted ? custom type prob
				pointer	ptr_;
		};
	
		


		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;


		/*
		// from book
		vector() {}
		explicit vector( const Alloc& al ) {}
		explicit vector( size_type n ) {}
		vector( size_type n, const T& x ) {}
		vector( size_type n, const T& x, const Alloc& al ) {}
		vector( const vector& x ) {}
		template <class InIt>
			vector( InIt first, InIt last ) {}
		template <class InIt>
			vector( InIt first, InIt last, const Alloc& al ) {}
			*/

		// from cppreference
/*
		vector() : alloc_(Alloc()), capacity_(0), size_(0), arr_(NULL) {}
		explicit vector( const Alloc& al ) : alloc_(al), capacity_(0), size_(0), arr_(NULL) {}
		vector( const vector& x ) : capacity_(0), size_(0), arr_(NULL) { *this = x; }
		explicit vector( size_type n, const T& value = T(), const Alloc& al = Alloc() )
				: alloc_(al), capacity_(n), size_(n), arr_(alloc_.allocate(n)) {
			//for (size_type i = 0; i < size_; i++)
			//	arr_[i] = val;
			assign(n, value);
			std::cout << "fill\n";
		}
		explicit vector(size_type count) : capacity_(count),
									   size_(count),
									   arr_(alloc_.allocate(count)) {}

		template <class InputIt>
			vector( InputIt first, InputIt last, const Alloc& al = Alloc() )
				: alloc_(al), capacity_(0), size_(0), arr_(NULL) {
			assign(first, last);
			//insert(begin(), first, last);
			std::cout << "range\n";
		}

*/


		//from cplusplus
		// default
		explicit vector( const allocator_type& alloc = allocator_type() )
			: alloc_(alloc), capacity_(0), size_(0), arr_(NULL) {}

		// fill
		explicit vector( size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type() ) 
				: alloc_(alloc), capacity_(n), size_(n), arr_(alloc_.allocate(n)) {
			//for (size_type i = 0; i < size_; i++)
			//	arr_[i] = val;
			assign(n, val);
			std::cout << "fill\n";
		}
		// range
		// use is integral
		template < class InputIterator >
		vector( InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type() ) 
				: alloc_(alloc), capacity_(0), size_(0), arr_(NULL) {

			assign(first, last);
			//insert(begin(), first, last);
			std::cout << "range\n";
		}


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
			clear();
			reserve(other.size_);
			alloc_ = other.get_allocator();
			//alloc_ = other.alloc_;
			capacity_ = other.capacity_;
			size_ = other.size_;
			for (size_type i = 0; i < size_; i++)
				arr_[i] = other.arr_[i];
			return *this;
		}


		iterator		begin() { return iterator(arr_); }
		const_iterator	begin() const { return const_iterator(arr_); }
		iterator		end( void ) { return iterator(arr_ + size_); }
		const_iterator	end( void ) const { return const_iterator(arr_ + size_); }

		reverse_iterator		rbegin( void ) { return reverse_iterator(end()); }
		reverse_iterator		rend( void ) { return reverse_iterator(begin()); }
		const_reverse_iterator	rbegin( void ) const { return const_reverse_iterator(end()); }
		const_reverse_iterator	rend( void ) const { return conat_reverse_iterator(begin()); }

		allocator_type get_allocator() const { return alloc_; }
		size_type	size() const { return size_; }
		size_type	max_size() const { return alloc_.max_size(); }
		size_type	capacity() const { return capacity_; }
		bool		empty() const { return size_ == 0;}


		void	reserve( size_type n ) {
			if (n <= capacity_)
				return ;
			n = std::max(size_ * 2, n);

			pointer		new_arr = alloc_.allocate(n);

			for (size_type i = 0; i < size_; i++)
				new_arr[i] = arr_[i];
			if (arr_)
				alloc_.deallocate(arr_, capacity_);
			capacity_ = n;
			arr_ = new_arr;
		}

		void	resize( size_type n, value_type val = value_type() ) {
			reserve(n);
			while (size_ < n)
				arr_[size_++] = val;
			size_ = n;
		}


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


		template < class InputIt >
		void	assign( InputIt first, InputIt last )
		//void assign(InputIt first,
		//		typename std::enable_if<!std::is_integral<InputIt>::val, InputIt>::type last)
				//typename enable_if<!is_integral<InputIt>::val, InputIt>::type last)
		{		
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
/*

	template <class InputIt>
	void assign(InputIt first,
				typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)
	{
		clear();
		size_type t = std::distance(first, last);
		reserve(t);
		_size = t;
		int i = 0;
		while (first != last)
			_values[i++] = *first++;
	}
*/
		void	push_back( const value_type& val ) {
			if (size_ == capacity_) {
				if (size_)
					reserve(size_ * 2);
				else
					reserve(1);
			}
			arr_[size_] = val;
			size_++;
			//arr_[size_++] = val;
		}
		void	pop_back() { size_--; }


		// single elem
		iterator	insert( iterator position, const value_type& val ) {
			size_type	idx = position - begin();
			
			reserve(size_ + 1);
			++size_;
			for (size_type i = size_ - 1; i > idx; --i)
				arr_[i] = arr_[i - 1];
			arr_[idx] = val;
			return arr_ + idx;;
		}
		// fill
		void		insert( iterator position, size_type n, const value_type& val ) {
			size_type	idx = position - begin();
			
			reserve(size_ + n);
			size_ += n;
			// size_ - 1 or size_ prob first bc of idx from 0
			for (size_type i = size_ - 1; i > idx + n - 1; --i)
				arr_[i] = arr_[i - n];
			for (size_type i = idx; i < idx + n; ++i)
				arr_[i] = val;
		}

		// finish when able to distinguish int and iter
		// range
		template < class InputIterator >
		void		insert( iterator position, InputIterator first, InputIterator last ) {
			size_type	n = first - last;
			//size_type	idx = position.ptr_ - arr_;
			size_type	idx = position - first;
			reserve(size_ + n);
			size_ += n;
			size_type	i = size_ - 1;
			while (i > idx + n - 1) {
				arr_[i] = arr_[i - n];
				--i;
			}
			//for (size_type i = size_ - 1; i > idx + n - 1; --i)
			//	arr_[i] = arr_[i - n];
			while (first != last) {
				arr_[i] = *first;
				++first;
				++i;
			}
		}


		iterator erase( iterator position ) {
			size_type	index = position - begin();
			if (position != end()) {
				for (size_type i = index; i < size_ - 1; i++)
					arr_[i] = arr_[i + 1];
				reserve(size_ - 1);
			}
			size_--;
			return iterator(arr_ + index);
		}

		iterator erase( iterator first, iterator last ) {
			size_type	n = std::distance(first, last);
			size_type	idx = first - begin();
			
			pointer		new_arr = alloc_.allocate(size_ - n);
			size_type	i = 0;
			while (i++ < idx)
				new_arr[i] = arr_[i];
			idx += n;
			while (i++ > idx)
				new_arr[i] = arr_[i];

			if (arr_)
				alloc_.deallocate(arr_, capacity_);
			arr_ = new_arr;
			size_ -= n;
		}

		void	swap( vector &x ) {
			size_type	tmp_size = x.size();
			size_type	tmp_cap = x.capacity();
			pointer		tmp_arr = x.arr_;

			x.size_ = size_;
			x.capacity_ = capacity_;
			x.arr_ = arr_;
			size_ = tmp_size;
			capacity_ = tmp_cap;
			arr_ = tmp_arr;
			// read more about swaps and their optimization 

			// or
			//std::swap(arr_, x.arr_);
			//std::swap(capacity_, x.capacity_);
			//std::swap(size_, x.size_);
		}

		void	clear() {
			for (size_type i = 0; i < size_; i++)
				//alloc_.destroy(arr_[i]);
				alloc_.destroy(arr_ + i);
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

template< class T, class Alloc >
bool operator<( const ft::vector<T, Alloc>& lhs,
				const ft::vector<T, Alloc>& rhs) {
	return ft::lexicographical_compare(lhs.begin, lhs.end(), rhs.begin(), rhs.end());
}

template< class T, class Alloc >
bool operator<=( const ft::vector<T, Alloc>& lhs,
				const ft::vector<T, Alloc>& rhs) {
	return !(rhs < lhs);
}

template< class T, class Alloc >
bool operator>( const ft::vector<T, Alloc>& lhs,
				const ft::vector<T, Alloc>& rhs) {
	return rhs < lhs;
}

template< class T, class Alloc >
bool operator>=( const ft::vector<T, Alloc>& lhs,
				const ft::vector<T, Alloc>& rhs) {
	return !(lhs < rhs);
}

template < class T, class Alloc >
void	swap( ft::vector<T, Alloc>& x, ft::vector<T, Alloc>& y) {
	x.swap(y);
}

#endif
