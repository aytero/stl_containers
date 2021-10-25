#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft
{
	template <class Iterator>
	class reverse_iterator;
}

template <class Iterator>
class ft::reverse_iterator {

	public:
		typedef Iterator													iterator_type;
		typedef typename std::iterator_traits<Iterator>::iterator_category	iterator_category;
		// std::iterator_traits<Iter>::
		typedef typename std::iterator_traits<Iterator>::value_type			value_type;
		typedef typename std::iterator_traits<Iterator>::difference_type	difference_type;
		typedef typename std::iterator_traits<Iterator>::pointer			pointer;
		typedef typename std::iterator_traits<Iterator>::reference			reference;

		reverse_iterator() : current_(0) {}

		explicit reverse_iterator( iterator_type it ) : current_(it) {}

		template <class Iter>
			// or base()
		reverse_iterator( const reverse_iterator<Iter>& rev_it ) : current_(rev_it.current_) {}
		
		reverse_iterator& operator=( const reverse_iterator &other ) {
			if (this != &other)
				current_ = other.base();
			return *this;
		}

		virtual ~reverse_iterator() {}

		// offset -1 ?
		iterator_type	base() const { return current_ - 1; }


		reference operator*() const {
			Iterator	it = current_;
			return *(--it);
		}
		pointer operator->() const { return &(operator*()); }
		reference operator[]( difference_type n ) { return base()[-n - 1]; }

		reverse_iterator& operator+=( difference_type n ) {
			current_ -= n;
			return reverse_iterator(*this);
		}
		reverse_iterator operator+( difference_type n ) const
			{ return reverse_iterator(iterator_type::operator-(n)); }
		
		reverse_iterator& operator++() {
			current_--;
			return reverse_iterator(*this);
		}
		//reverse_iterator& operator++() { return reverse_iterator(iterator_type::operator++()); }
		
		reverse_iterator operator++(int) {
			reverse_iterator	tmp(current_);

			--current_;
			return (tmp);
		}

		reverse_iterator& operator-=( difference_type n ) {
			current_ += n;
			return reverse_iterator(*this);
		}
		reverse_iterator operator-( difference_type n ) const
			{ return reverse_iterator(iterator_type::operator+(n)); }
		
		reverse_iterator& operator--() {
			current_++;
			return reverse_iterator(*this);
		}
		reverse_iterator operator--(int) {
			reverse_iterator	tmp(current_);

			++current_;
			return (tmp);
		}

	protected:
		iterator_type	current_;
		//iterator_type&	current_;

};

template <class Iterator>
	typename ft::reverse_iterator<Iterator> operator+(
				typename ft::reverse_iterator<Iterator>::difference_type n,
				const ft::reverse_iterator<Iterator>& rev_it ) {
		return rev_it - n;
		// reverse signs or not ?
		//return rev_it.base() + n;
	}

template <class Iterator>
	typename ft::reverse_iterator<Iterator>::differnece_type operator-(
				const ft::reverse_iterator<Iterator>& lhs,
				const ft::reverse_iterator<Iterator>& rhs ) {
		return rhs.base() + lhs.base();
	}

template <class Iterator>
	bool	operator==( const ft::reverse_iterator<Iterator>& lhs,
						const ft::reverse_iterator<Iterator>& rhs ) {
		return lhs.base() == rhs.base();
		//return lhs.current_ == rhs.current_;
	}

template <class Iterator>
	bool	operator!=( const ft::reverse_iterator<Iterator>& lhs,
						const ft::reverse_iterator<Iterator>& rhs ) {
		return lhs.base() != rhs.base();
	}

template <class Iterator>
	bool	operator<( const ft::reverse_iterator<Iterator>& lhs,
						const ft::reverse_iterator<Iterator>& rhs ) {
		return lhs.base() < rhs.base();
	}


template <class Iterator>
	bool	operator<=( const ft::reverse_iterator<Iterator>& lhs,
						const ft::reverse_iterator<Iterator>& rhs ) {
		return lhs.base() <= rhs.base();
	}

template <class Iterator>
	bool	operator>( const ft::reverse_iterator<Iterator>& lhs,
						const ft::reverse_iterator<Iterator>& rhs ) {
		return lhs.base() > rhs.base();
	}

template <class Iterator>
	bool	operator>=( const ft::reverse_iterator<Iterator>& lhs,
						const ft::reverse_iterator<Iterator>& rhs ) {
		return lhs.base() >= rhs.base();
	}

#endif
