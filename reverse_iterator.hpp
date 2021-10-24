#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft
{
	template <>
	class reverse_iterator;
}

template <class Iterator>
class ft::reverse_iterator {
	;

	public:
		typedef typename Iterator									iterator_type;
		typedef iterator_traits<Iterator>::iterator_category		iterator_category;
		// std::iterator_traits<Iter>::
		typedef typename iterator_traits<Iterator>::value_type		value_type;
		typedef typename iterator_traits<Iterator>::difference_type	difference_type;
		typedef typename iterator_traits<Iterator>::pointer			pointer;
		typedef typename iterator_traits<Iterator>::reference		reference;

		reverse_iterator() : current_(0) {}

		explicit reverse_iterator( iterator_type it ) : current_(it) {}

		//template <class Iter>
		//reverse_iterator( const reverse_iterator<Iter>& rev_it ) {}
		
		/*
		reverse_iterator& operator=( const reverse_iterator &ref) {
			if (this != &other)
				;
			return *this;
		}
		*/
		virtual ~reverse_iterator() {}

		// offset -1 ?
		iterator_type	base() const { return current_ - 1; }


		reference operator*() const {
			Iterator	it = current_;
			return *(--it);
		}
		pointer operator->() const { return &(operator*()); }
		//reference operator[]( difference_type n ) const { return ptr_ + n; }

		/*
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

		*/
	protected:
		iterator_type	current_;
		//iterator_type&	current_;

};

#endif
