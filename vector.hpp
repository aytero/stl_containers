#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

#include <memory>
#include <iostream>
#include <exception>
//#include <iterator>
#include "reverse_iterator.hpp"
#include "iterator_traits.hpp"
#include "utility.hpp"


// 12 operators in iters for ex const_iter - iter; iter + const_iter
// nil node left and right to min max
// std::distance not with all iterator types: make overloads
// allocator and memory; vector throws exceptions, catches, deletes not finished adding and throws again
// lower and  upper bound map and set into tree problem 
//
// tree copy and assign 
//
// vector operator -> with objects with overloaded & (addressof)
//
// map iterator -- when end() ? can use nil_->left/right or wierdly keep root in a node

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
		//typedef pointer							iterator_type;
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
				

				typedef pointer							iterator_type;

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

				/*
		const_iterator &operator+=(size_type n) { _ptr += n; return *this; }
		const_iterator operator+(size_type n) const { return const_iterator(_ptr + n); }
		friend const_iterator operator+(size_type n, const const_iterator &other) { return const_iterator(other._ptr + n); }

		const_iterator &operator-=(size_type n) { _ptr -= n; return *this; }
		const_iterator operator-(size_type n) const { return iterator(_ptr - n); }
		difference_type operator-(const_iterator const &other) const { return _ptr - other._ptr; }
				*/
				const_iterator& operator++() { ++ptr_; return *this; }
				const_iterator operator++( int ) { const_iterator tmp(*this); ++ptr_; return tmp; }
				const_iterator& operator--() { --ptr_; return *this; }
				const_iterator operator--( int ) { const_iterator tmp(*this); --ptr_; return tmp; }

				const const_iterator operator+( size_type n ) const { return const_iterator(ptr_ + n); }
				friend const_iterator operator+( size_type n, const const_iterator &c ) { return const_iterator(c.ptr_ + n); }
				const_iterator& operator+=( size_type n ) { ptr_ += n; return *this; }

				difference_type operator-( const const_iterator &other ) const { return ptr_ - other.ptr_; }
				const_iterator operator-( const size_type n ) const { return const_iterator(ptr_ - n); }
				//friend const_iterator operator-( size_type n, const const_iterator &c ) { return const_iterator(c.ptr_ - n); }
				const_iterator& operator-=( size_type n ) { ptr_ -= n; return *this; }

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

				typedef pointer							iterator_type;


		//iterator(T *ptr = NULL) : cit(ptr) {}
				iterator( pointer ptr = NULL ) : const_iterator(ptr) {
					//ptr_ = ptr;
					//ptr_ = const_iterator::ptr_;
					//std::cout << iterator::ptr_ << " lils ptr   " << const_iterator::ptr_ << "\n";
				}
				iterator( const iterator &ref ) : const_iterator(ref) { const_iterator::ptr_ = ref.ptr_; }
				virtual ~iterator() {}

				iterator& operator=( const iterator &other ) {
					const_iterator::operator=(other);
					return *this;
				}

				reference operator*() { return *const_iterator::ptr_; }
				pointer operator->() { return const_iterator::ptr_; }
				reference operator[]( size_type n ) { return const_iterator::ptr_ + n; }

				//bool	operator==( const iterator &rhs ) { return ptr_ == rhs.ptr_; }
				//bool	operator!=( const iterator &rhs ) { return ptr_ != rhs.ptr_; }
				//bool	operator<( const iterator &rhs ) { return ptr_ < rhs.ptr_; }
				//bool	operator<=( const iterator &rhs ) { return ptr_ <= rhs.ptr_; }
				//bool	operator>( const iterator &rhs ) { return ptr_ > rhs.ptr_; }
				//bool	operator>=( const iterator &rhs ) { return ptr_ >= rhs.ptr_; }

				//iterator &operator=(const iterator &other) { cit::operator=(other); return *this; }

				iterator &operator++() { const_iterator::operator++(); return *this; }
				iterator operator++( int ) { iterator tmp(*this); const_iterator::operator++(0); return tmp; }

				iterator &operator--() { const_iterator::operator--(); return *this; }
				iterator operator--( int ) { iterator tmp(*this); const_iterator::operator--(0); return tmp; }

				iterator &operator+=( difference_type n ) { const_iterator::operator+=(n); return *this; }
				iterator operator+( difference_type n ) const { return iterator(const_iterator::ptr_ + n); }
				friend iterator operator+( difference_type n, const iterator &other ) { return iterator(other.ptr_ + n); }

				iterator &operator-=( difference_type n ) { const_iterator::operator-=(n); return *this; }
				iterator operator-( difference_type n ) const { return iterator(const_iterator::ptr_ - n); }
				difference_type operator-( const_iterator const &other ) const { return const_iterator::operator-(other); }
				/*
				iterator& operator++() { ++ptr_; return *this; }
				iterator operator++( int ) { iterator tmp(*this); ++ptr_; return tmp; }
				iterator& operator--() { --ptr_; return *this; }
				iterator operator--( int ) { iterator tmp(*this); --ptr_; return tmp; }
				const iterator operator+( size_type n ) const { return iterator(ptr_ + n); }
				friend iterator operator+( size_type n, const iterator &c )
					{ return iterator(c.ptr_ + n); }
				iterator& operator+=( size_type n ){ ptr_ += n; return *this; }
				difference_type operator-( const iterator &other )
					{ return ptr_ - other.ptr_; }
				const iterator operator-( const size_type n ) const
					{ return iterator(const_iterator::ptr_ - n); }
				friend iterator operator-( size_type n, const iterator &c )
					{ return iterator(c.const_iterator::ptr_ - n); }
				const iterator& operator-=( size_type n ) const
					{ const_iterator::ptr_ -= n; return *this; }

*/
			//private:
			//protected:
				// isnt it inhereted ? custom type prob
				//pointer	ptr_;
		};
	
		
		/////// TODO
	 //vector (InputIterator first, InputIterator last,
	//	 const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value>::type* = 0) : _allocator(alloc){
//	size = last - first;
//	capacity = _size;
//	first = _allocator.allocate(_capacity);
//	for (difference_type i = 0; i < static_cast<difference_type>(_size); i++)
//		allocator.construct(_first + i, *(first + i));
		///

		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		// constructors
		explicit vector( const Alloc& alloc = Alloc() )
						: alloc_(alloc), capacity_(0), size_(0), arr_(0) {}

		explicit vector( size_type n, const value_type& val = value_type(), const Alloc& alloc = Alloc() ) 
						: alloc_(alloc), capacity_(n), size_(n), arr_(alloc_.allocate(n)) {
			//assign(n, val);
			//insert(begin(), n, val);
			for (size_type i = 0; i < n; ++i)
				alloc_.construct(arr_ + i, val);
		}

		template < class InputIt >
		vector( typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first,
				InputIt last, const Alloc& alloc = Alloc() ) 
				: alloc_(alloc), capacity_(0), size_(0), arr_(0) {

			if (first > last)
				throw std::length_error("vector");
			//assign(first, last);
			insert(begin(), first, last);
		}


		vector( const vector& x ) : capacity_(0), size_(0), arr_(NULL) { *this = x; }

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
		const_reverse_iterator	rend( void ) const { return const_reverse_iterator(begin()); }

		allocator_type get_allocator() const { return alloc_; }
		size_type	size() const { return size_; }
		size_type	max_size() const { return alloc_.max_size(); }
		size_type	capacity() const { return capacity_; }
		bool		empty() const { return size_ == 0;}
		pointer			data() { return arr_; }
		const_pointer	data() const { return arr_; }


		void	reserve( size_type n ) {
			if (n <= capacity_)
				return ;
			//std::cout << "aft return\n";
			//std::cout << capacity_ << " cap | " << n << " n\n";
			n = std::max(size_ * 2, n);
			//n = std::max(size_ * 2, size_type(n * 1.3));
			//std::cout << "testing reserve\n";
			//std::cout << size_ << " size | " << capacity_ 
			//	<< " cap | " << n << " n\n"; 

			pointer new_arr = alloc_.allocate(n);
			for (size_type i = 0; i < size_; ++i)
				new_arr[i] = arr_[i];
			if (arr_)
				alloc_.deallocate(arr_, capacity_);
			arr_ = new_arr;
			capacity_ = n;
		}

		void	resize( size_type n, value_type val = value_type() ) {
			reserve(n);
			//for (size_type i = size_ - 1; i < n; ++i)
			//	arr_[i] = val;
			while (size_ < n)
				arr_[size_++] = val;
			size_ = n;
		}

		//
		/*
			if(n < _size){
				for(size_type i = n; i < _size; i++)
					_allocator.destroy(_first + i);
				_size = n;
			}
			else if (n > _size){
				if (_capacity < n)
					this->reserve(_capacity * 2 > n ? _capacity * 2 : n);
				for (size_type i = _size; i < n; i++){
					_allocator.construct(_first + i, val);
					_size++;
				}
			}
			*/
		//////////
	

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
			void assign(InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last)
			{		
				clear();
				size_type new_size = std::distance(first, last);
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

		void pop_back() {
			--size_;
		}

		///////


		///////
		iterator insert( iterator position, const value_type& val ) {

			if (position < begin() || position >= end())
				throw std::logic_error("vector");

			size_type idx = std::distance(begin(), position);
			//difference_type	idx = position - begin();
			
			reserve(size_ + 1);
			for (size_type i = size_; i > idx; --i)
				arr_[i] = arr_[i - 1];

			++size_;
			arr_[idx] = val;

			//return begin() + idx;
			return iterator(arr_ + idx);
			//insert(position, 1, val);
		}

		void insert( iterator position, size_type n, const value_type& val ) {
			if (!n)
				return ;
			if (max_size() - size_ < n)
				throw std::length_error("vector");
			
			size_type	idx = position - begin();
			//size_type	idx = std::distance(position, begin());
			
			reserve(size_ + n);
			size_ += n;
			// size_ - 1 or size_ prob first bc of idx from 0
			for (size_type i = size_ - 1; i > idx + n - 1; --i)
				arr_[i] = arr_[i - n];
			for (size_type i = idx; i < idx + n; ++i)
				arr_[i] = val;
		}

		template < class InputIterator >
		void insert( iterator position, InputIterator first,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last) {
			if (position < begin() || position > end() || first > last)
				throw std::logic_error("vector");

			size_type	idx = std::distance(begin(), position);
			size_type	count = std::distance(first, last);
			//if (!count)
			//	return ;
			reserve(size_ + count);
			for (size_type i = size_; i > idx; --i) {
				arr_[i - 1 + count] = arr_[i - 1];
			}
			size_ += count;
			for (size_type i = 0; i < count; ++i) {
				arr_[idx + i] = *first;
				first++;
			}

			//std::cout << "insert val\n";
			/*
			size_type	i = size_ - 1;
			while (i > idx) {
				arr_[i + count] = arr_[i];
				--i;
			}
			size_ += count;
			//for (size_type i = size_; i < n; ++i)
			//	arr_[i] = arr_[i - n];
			i = 0;
			while (i < count) {
				arr_[i + idx] = *first;
				++first;
				++i;
			}
			*/
		}

		iterator erase( iterator position ) {
			size_type	index = position - begin();
			//if (position != end()) {
				for (size_type i = index; i < size_ - 1; i++)
					arr_[i] = arr_[i + 1];
				//reserve(size_ - 1);
			//}
			size_--;
			return iterator(arr_ + index);
		}

		iterator erase( iterator first, iterator last ) {
			size_type	count = last - first;
			size_type	idx = first - begin();

			for (size_type i = idx; i < size_ - count; i++)
				arr_[i] = arr_[i + count];
			size_ -= count;
			/*
			pointer		new_arr = alloc_.allocate(size_ - count);// * 2
			size_type	i = 0;

			while (i++ < idx)
				new_arr[i] = arr_[i];
			i += count;
			while (i++ < size_)
				//smth is wrong with indexes
				new_arr[i - count] = arr_[i];
			if (arr_)
				alloc_.deallocate(arr_, capacity_);
			arr_ = new_arr;
			size_ -= count;
			*/
			return iterator(arr_ + idx);
		}

		void	swap( vector &x ) {
			size_type	tmp_size = x.size();
			size_type	tmp_cap = x.capacity();
			pointer		tmp_arr = x.arr_;
			// alloc

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
			// or std::move()
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
	//return ft::lexicographical_compare(lhs.begin, lhs.end(), rhs.begin(), rhs.end());

	unsigned	i = 0;
	unsigned	lsz = lhs.size();
	unsigned	rsz = rhs.size();
	
	while (i < lsz && i < rsz && lhs[i] == rhs[i])
		i++;
	return (i == lsz && i < rsz) || (i < lsz && i < rsz && lhs[i] < rhs[i]);
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
