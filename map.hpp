#ifndef MAP_HPP
# define MAP_HPP

namespace ft
{
	template < class Key, class T, class Compare = less<Key>,
				 class ALloc = std::allocator<ft::pair<const Key,T> >
		class map;
}

template < class Key, class T, class Compare, class Alloc >
class ft::map {
	;

	public:

		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<cinst key_type,mapped_type> value_type;
		typedef Compare key_compare;
		//typedef Compare			key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		// iterator;
		// const_iterator;
		//typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		//typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		//typedef ft::iterator_traits<iterator>::difference_type	diference_type;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

		explicit map( const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type() ) {}

		template <class InputIt>
			map ( InputIt first, InputIt last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type() ) {}

		map( const map &ref ) {}

		~map() {}

		map& operator=( const map &other ) {}

		iterator		begin() {}
		iterator		end() {}
		const_iterator	begin() const {}
		const_iterator	end() const {}

		reverse_iterator		rbegin() {}
		reverse_iterator		rend() {}
		const_reverse_iterator	rbegin() const {}
		const_reverse_iterator	rend() const {}

		bool	empty() const {}
		size_type	size() const { return rbtree.size(); }
		size_type	max_size() const {}

		// prob a type may be const itself
		mapped_type& operator[]( const key_type& k ) {}

		// single elem
		ft::pair<iterator,bool> insert( const value_type& val ) {}
		// with hint
		iterator insert( iterator position, const value_type& val ) {}
		// range
		template <class InputIt>
			void insert( InputIt first, InputIt last ) {}

		void		erase( iterator position) { rbtree.deleteVal(position); }
		size_type	erase( const key_type& k ) {}
		void		erase( iterator first, iterator last ) {}

		// swap() {}
		void	clear() {}

		key_compare		key_comp() const { return cmp_; }
		value_compare	value_comp() const {}
		allocator_type	get_allocator() const { return alloc_; }

		iterator		find( const key_type& k ) {}
		const_iterator	find( const key_type& k ) const {}

		size_type	count( const key_type& k ) const {}

		iterator		lower_boind( const key_type& k ) {}
		const_iterator	lower_boind( const key_type& k ) const {}
		iterator		upper_boind( const key_type& k ) {}
		const_iterator	upper_boind( const key_type& k ) const {}

		ft::pair<iterator,iterator>	equal_range( const key_type& k) {}
		ft::pair<const_iterator,const_iterator>	equal_range( const key_type& k) const {}
	
	private:
		// size ?? or through tree 
		ALloc	alloc_;
		Compare	cmp_;
		//ft::rbtree	rbtree_;
};

#endif