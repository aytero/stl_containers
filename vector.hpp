#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

#include <memory>
#include <iostream>
#include <exception>

# include "reverse_iterator.hpp"
# include "type_traits.hpp"
# include "iterator_traits.hpp"
# include "utility.hpp"

namespace ft {

template < class T, class Alloc = std::allocator<T> >
class vector {
	public:
		typedef T								value_type;
		typedef Alloc							allocator_type;
		typedef typename Alloc::reference		reference;
		typedef typename Alloc::const_reference	const_reference;
		typedef typename Alloc::pointer			pointer;
		typedef typename Alloc::const_pointer	const_pointer;
		typedef typename std::ptrdiff_t	difference_type;
		typedef std::size_t							size_type;

	private:
		allocator_type	alloc_;
		size_type		capacity_;
		size_type		size_;
		pointer			arr_;

	public:
		class const_iterator {
			public:
				typedef typename Alloc::value_type		value_type;
				typedef typename Alloc::pointer			pointer;
				typedef typename Alloc::const_reference	reference;
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

				const_iterator& operator++() { ++ptr_; return *this; }
				const_iterator operator++( int ) { const_iterator tmp(*this); ++ptr_; return tmp; }
				const_iterator& operator--() { --ptr_; return *this; }
				const_iterator operator--( int ) { const_iterator tmp(*this); --ptr_; return tmp; }

				const const_iterator operator+( size_type n ) const { return const_iterator(ptr_ + n); }
				friend const_iterator operator+( size_type n, const const_iterator &c ) { return const_iterator(c.ptr_ + n); }
				const_iterator& operator+=( size_type n ) { ptr_ += n; return *this; }

				difference_type operator-( const const_iterator &other ) const { return ptr_ - other.ptr_; }
				const_iterator operator-( const size_type n ) const { return const_iterator(ptr_ - n); }
				const_iterator& operator-=( size_type n ) { ptr_ -= n; return *this; }

			protected:
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

				iterator( pointer ptr = NULL ) : const_iterator(ptr) {}
				iterator( const iterator &ref ) : const_iterator(ref) { const_iterator::ptr_ = ref.ptr_; }
				virtual ~iterator() {}

				iterator& operator=( const iterator &other ) {
					const_iterator::operator=(other);
					return *this;
				}

				reference operator*() { return *const_iterator::ptr_; }
				pointer operator->() { return const_iterator::ptr_; }
				reference operator[]( size_type n ) { return const_iterator::ptr_ + n; }

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
		};
	
		

		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		// constructors
		explicit vector( const allocator_type& alloc = allocator_type() )
						: alloc_(alloc), capacity_(0), size_(0), arr_(0) {}

		explicit vector( size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type() ) 
						: alloc_(alloc), capacity_(n), size_(n), arr_(alloc_.allocate(n)) {
			
			for (size_type i = 0; i < n; ++i)
				alloc_.construct(arr_ + i, val);
		}

		template < class InputIt >
		vector( typename enable_if<!is_integral<InputIt>::value, InputIt>::type first,
				InputIt last, const allocator_type& alloc = allocator_type() ) 
				: alloc_(alloc), capacity_(0), size_(0), arr_(0) {

			if (first > last)
				throw std::length_error("vector");
			size_ = last - first;
			capacity_ = size_;
			arr_ = alloc_.allocate(capacity_);
			for (difference_type i = 0; i < static_cast<difference_type>(size_); ++i)
				alloc_.construct(arr_ + i, *(first + i));
		}

		vector( const vector& ref ) : capacity_(0), size_(0) {
			*this = ref;
		}

		virtual ~vector() {
			clear();
			if (capacity_)
				alloc_.deallocate(arr_, capacity_);
		}

		vector&	operator=( const vector &other ) {
			if (this == &other)
				return *this;
			clear();
			size_ = other.size_;
			if (capacity_ < other.size_) {
				if (capacity_ != 0)
					alloc_.deallocate(arr_, capacity_);
				capacity_ = other.size_;
				arr_ = alloc_.allocate(capacity_);
			}
			for (size_type i = 0; i < size_; ++i)
				alloc_.construct(arr_ + i, other[i]);
			alloc_ = other.alloc_;
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

		void reserve( size_type n ) {
			if (n < capacity_)
				return ;

			pointer new_arr = alloc_.allocate(n);
			try {
				for (size_type i = 0; i < size_; ++i)
					alloc_.construct(new_arr + i, *(arr_ + i));
			} catch ( std::exception &e ) {
				size_type i = 0;
				while (new_arr + i != 0 && i < size_) {
					alloc_.destroy(new_arr + i);
					++i;
				}
				alloc_.deallocate(new_arr, n);
				throw ;
			}
			for (size_type i = 0; i < size_; ++i)
				alloc_.destroy(arr_ + i);
			if (capacity_)
				alloc_.deallocate(arr_, capacity_);
			arr_ = new_arr;
			capacity_ = n;
		}

		void resize( size_type n, value_type val = value_type() ) {
			if (n < size_) {
				for (size_type i = n; i < size_; ++i)
					alloc_.destroy(arr_ + i);
				size_ = n;
			} else if (n > size_) {
				if (capacity_ < n)
					reserve(capacity_ * 2 > n ? capacity_ * 2 : n);
				for (size_type i = size_; i < n; ++i) {
					alloc_.construct(arr_ + i, val);
					++size_;
				}
			}
		}

		reference		operator[] ( size_type n ) { return *(arr_ + n); }// arr[n]
		const_reference	operator[] ( size_type n ) const { return arr_[n]; }
		
		reference at( size_type n ) {
			if (n >= size_ || n < 0)
				throw ( std::out_of_range("vector") );
			return (arr_[n]);
		}

		const_reference at( size_type n ) const {
			if (n >= size_ || n < 0)
				throw ( std::out_of_range("vector") );
			return (arr_[n]);
		}

		reference		front() { return arr_[0]; }
		const_reference	front() const { return arr_[0]; }
		reference		back() { return arr_[size_ - 1]; }
		const_reference	back() const { return arr_[size_ - 1]; }

		template < class InputIt >
			void assign(InputIt first,
					typename enable_if<!is_integral<InputIt>::value, InputIt>::type last) {
				if (first > last)
					throw std::logic_error("vector");
				clear();
				size_type new_size = static_cast<size_type>(last - first);
				if (new_size > capacity_) {
					if (capacity_)
						alloc_.deallocate(arr_, capacity_);
					arr_ = alloc_.allocate(new_size);
					capacity_ = new_size;
				}
				size_ = new_size;
				size_type i = 0;
				while (first != last) {
					alloc_.construct(arr_ + i, *first);
					++i;
					++first;
				}
			}

		void assign( size_type n, const value_type& val ) {
			clear();
			if (n > capacity_) {
				if (capacity_)
					alloc_.deallocate(arr_, capacity_);
				arr_ = alloc_.allocate(n);
				capacity_ = n;
			}
			for (size_type i = 0; i < n; ++i)
				alloc_.construct(arr_ + i, val);
			size_ = n;
		}

		void push_back( const value_type& val ) {
			if (size_ == capacity_) {
				reserve(capacity_ == 0 ? 1 : capacity_ * 2);
			}
			alloc_.construct(arr_ + size_, val);
			size_++;
		}

		void pop_back() {
			if (size_)
				alloc_.destroy(arr_ + size_ - 1);
			--size_;
		}

		iterator insert( iterator position, const value_type& val ) {
			if (position < begin() || position > end())
				throw std::logic_error("vector");
			difference_type	idx = position - begin();
			insert(position, 1, val);
			return iterator(arr_ + idx);

		}

		void insert( iterator position, size_type n, const value_type& val ) {
			if (!n)
				return ;
			if (max_size() - size_ < n)
				throw std::length_error("vector");
			
			size_type idx = static_cast<size_type>(position - begin());
			//difference_type idx = position - begin();
			if (size_ + n > capacity_) {
				size_type new_cap = capacity_ * 2 >= size_ + n ? capacity_ * 2 : size_ + n;

				pointer new_arr = alloc_.allocate(new_cap);

				for (size_type i = 0; i < idx; ++i)
					alloc_.construct(new_arr + i, *(arr_ + i));
				for (size_type i = 0; i < n; ++i)
					alloc_.construct(new_arr + idx + i, val);
				if (n == 1) {
					for (size_type i = idx; i < size_; ++i)
						alloc_.construct(new_arr + n + i, *(arr_ + i));
				} else {
					for (size_type i = idx; i < size_; ++i)
						alloc_.construct(new_arr + n + i, *(arr_ + i - 1));
				}

				size_type i = -1;
				while (++i < size_)
					alloc_.destroy(arr_ + i);
				if (size_)
					alloc_.deallocate(arr_, size_);

				capacity_ = new_cap;
				arr_ = new_arr;

			} else {
				for (size_type i = size_; i > idx; --i) {
					alloc_.destroy(arr_ + i + n - 1);
					alloc_.construct(arr_ + i + n - 1, *(arr_ + i - 1));
				}
				for (size_type i = 0; i < n; ++i) {
					alloc_.destroy(arr_ + idx + i);
					alloc_.construct(arr_ + idx + i, val);
				}
			}
			size_ += n;
		}

		template < class InputIterator >
		void insert( iterator position, InputIterator first,
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last) {
			if (position < begin() || position > end() || first > last)
				throw std::logic_error("vector");

			size_type idx = std::distance(begin(), position);
			size_type count = std::distance(first, last);
			//size_type idx = static_cast<size_type>(position - begin());
			//size_type count = static_cast<size_type>(last - first);

			if (size_ + count > capacity_) {
				size_type new_cap = capacity_ * 2 >= size_ + count ? capacity_ * 2 : size_ + count;
				pointer new_arr = alloc_.allocate(new_cap);

				for (size_type i = 0; i < idx; ++i)
					alloc_.construct(new_arr + i, *(arr_ + i));

				try {
					for (size_type i = 0; i < static_cast<size_type>(count); ++i, ++first)
						alloc_.construct(new_arr + idx + i, *first);
				}
				catch ( ... ) {
					for (size_type i = 0; i < count + idx; ++i)
						alloc_.destroy(new_arr + i);
					alloc_.deallocate(new_arr, new_cap);
					throw ;
				}
				for (size_type i = idx; i < size_ ; ++i)
					alloc_.construct(new_arr + i + count, *(arr_ + i));
				for (size_type i = 0; i < size_; i++)
					alloc_.destroy(arr_ + i);
				alloc_.deallocate(arr_, capacity_);
				capacity_ = new_cap;
				arr_ = new_arr;
			} else {
				for (size_type i = size_; i > idx; --i) {
					alloc_.destroy(arr_ + i + count - 1);
					alloc_.construct(arr_ + i + count - 1, *(arr_ + i - 1));
				}
				for (size_type i = 0; i < count; ++i, ++first) {
					alloc_.destroy(arr_ + i + count);
					alloc_.construct(arr_ + idx + i, *first);
				}
			}
			size_ += count;
		}

		iterator erase( iterator position ) {
			if (position == end())
				return position;

			size_type index = static_cast<size_type>(position - begin());
			--size_;
			for (size_type i = index; i < size_; ++i) {
				alloc_.destroy(arr_ + i);
				alloc_.construct(arr_ + i, *(arr_ + i + 1));
			}
			alloc_.destroy(arr_ + size_ - 1);
			return iterator(arr_ + index);
		}

		iterator erase( iterator first, iterator last ) {
			if (first == end() || first == last)
				return first;

			size_type count = static_cast<size_type>(last - first);
			difference_type idx = first - begin();

			if (last < end()){
				iterator ite = end();
				for (; first != ite; ++first, ++last) {
					alloc_.destroy(&(*first));
					if (last < ite)
						alloc_.construct(&(*(first)), *last);
				}
				//for (size_type i = idx; i < size_ - count; ++i) {
				//	if (arr_ + idx)
				//		alloc_.destroy(arr_ + i);
				//	alloc_.construct(arr_ + i, *(arr_ + i + count));
				//}
				size_ -= count;
			} else {
				count = size_ - count;
				while (size_ != count)
					pop_back();
			}

			return iterator(arr_ + idx);
		}

		void swap( vector &x ) {
			std::swap(arr_, x.arr_);
			std::swap(capacity_, x.capacity_);
			std::swap(size_, x.size_);
			std::swap(alloc_, x.alloc_);
		}

		void clear() {
			while (size_)
				pop_back();
		}
};

template < class T, class Alloc >
	bool operator==( const vector<T, Alloc>& lhs,
					const vector<T, Alloc>& rhs) {
		unsigned int size = lhs.size();
		if (size != rhs.size())
			return false;

		unsigned int i = 0;
		while (i < size && lhs[i] == rhs[i])
			i++;
		return i == size;
}

template < class T, class Alloc >
	bool operator!=( const vector<T, Alloc>& lhs,
					const vector<T, Alloc>& rhs) {
		return !(lhs == rhs);
	}

template < class T, class Alloc >
	bool operator<( const vector<T, Alloc>& lhs,
					const vector<T, Alloc>& rhs) {

		unsigned int i = 0;
		unsigned int lsz = lhs.size();
		unsigned int rsz = rhs.size();
	
		while (i < lsz && i < rsz && lhs[i] == rhs[i])
			i++;
		return (i == lsz && i < rsz) || (i < lsz && i < rsz && lhs[i] < rhs[i]);
	}

template < class T, class Alloc >
	bool operator<=( const vector<T, Alloc>& lhs,
					const vector<T, Alloc>& rhs) {
		return !(rhs < lhs);
	}

template < class T, class Alloc >
	bool operator>( const vector<T, Alloc>& lhs,
					const vector<T, Alloc>& rhs) {
		return rhs < lhs;
	}

template < class T, class Alloc >
	bool operator>=( const vector<T, Alloc>& lhs,
					const vector<T, Alloc>& rhs) {
		return !(lhs < rhs);
	}
}

namespace std {
template < class V, class Allocator >
	void swap( ft::vector<V, Allocator>& x, ft::vector<V, Allocator>& y) {
		x.swap(y);
	}
}


#endif
