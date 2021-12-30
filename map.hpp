#ifndef MAP_HPP
# define MAP_HPP

namespace ft
{
	//template < class Key, class T, class Compare = less<Key>,
	//			 class Allocator = std::allocator<ft::pair<const Key,T> > >
	//	class map;
//}

template < class Key, class T, class Compare = less<Key>,
		 	class Allocator = std::allocator<pair<const Key, T> > >
class map {

	public:

		typedef Key									key_type;
		typedef T									mapped_type;
		typedef ft::pair<const Key, T>				value_type;
		typedef Compare								key_compare;
		typedef Allocator							allocator_type;
		typedef typename Allocator::reference		reference;
		typedef typename Allocator::const_reference	const_reference;
		typedef std::size_t							size_type;
		typedef std::ptrdiff_t						difference_type;
		//typedef ft::iterator_traits<iterator>::difference_type	diference_type;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;

		//typedef pair_compare value_compare;
		typedef rbree<value_type, pair_compare, allocator_type>	tree_type;
		typedef typename tree_type::iterator					iterator;
		typedef typename tree_type::const_iterator				const_iterator;
		typedef typename tree_type::reverse_iterator			reverse_iterator;
		typedef typename tree_type::const_reverse_iterator		const_reverse_iterator;

	private:
		ALloc		alloc_;
		Compare		cmp_;
		tree_type	tree_;
	
	public:

		/*
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			_alloc(alloc), _tree(tree_type(comp, alloc)), _compare(comp) {}

		template< class InputIt >
		map(InputIt first, InputIt last, const Compare& compare = Compare(), const Allocator& alloc = Allocator()):
			_alloc(alloc), _tree(first, last, compare, _alloc), _compare(compare) {}
	
		mapped_type& operator[](const key_type& key){
			//make_pair(key, mapped_type());
		//	return	_tree.insert(make_pair(key, mapped_type())).first->second;
			return (*((this->insert(ft::make_pair(key,mapped_type()))).first)).second;
		}

			*/
		explicit map( const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type() )
				: cmp_(comp), alloc_(alloc), tree_(tree_type(comp, alloc)) {}

		template <class InputIt>
			map ( InputIt first, InputIt last, const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type() )
					: cmp_(comp), alloc_(alloc), tree_(first, last, comp, alloc_) {
				//while (first != last) {
				//	insert(*first);
				//	++first;
				//}
			}

		map( const map<Key, T, Compare, Allocator> &ref ) : cmp_(other.cmp_), alloc_(other.alloc_), tree_(ref.tree_) {}

		~map() {}

		map<Key, T, Compare, Allocator> & operator=( const map<Key, T, Compare, Allocator> &other ) {
			if (this == &other)
				return *this;
			tree_ = other.tree_;
			return *this;
		}

		iterator begin() {
			return tree_.begin();
		}

		iterator end() {
			return tree_.end();
		}

		reverse_iterator rbegin() const {
			return tree_.rbegin();
		}

		reverse_iterator rend() const {
			return tree_.rend();
		}

		bool		empty() const { return tree_.empty(); }
		size_type	size() const { return tree_.size(); }
		size_type	max_size() const { return tree_.max_size(); }

		// prob a type may be const itself
		mapped_type& operator[]( const key_type& k ) {
			return ;
		}
		/*
		mapped_type& operator[](const key_type& key){
			//make_pair(key, mapped_type());
		//	return	_tree.insert(make_pair(key, mapped_type())).first->second;
			return (*((this->insert(ft::make_pair(key,mapped_type()))).first)).second;
		}
*/

		// single elem
		pair<iterator,bool> insert( const value_type& val ) {}
		// with hint
		iterator insert( iterator position, const value_type& val ) {}
		// range
		template <class InputIt>
			void insert( InputIt first, InputIt last ) {
				while (first != last) {
					tree_.insert(first);
				}
			}

		void		erase( iterator position) { tree_.deleteVal(position); }

		size_type	erase( const key_type& k ) {
			iterator	it = find(k);
			if (it == end())
				return 0;
			erase(it);
			return 1;
		}

		void		erase( iterator first, iterator last ) {
			iterator	it;
			while (first != last) {
				it = first;
				++first;
				erase(it);
			}
		}

		void swap( map &other ) {
			std::swap(this->cmp_, other.cmp_);
			tree_.swap(other.tree_);
		}

		void	clear() {
			tree_.clear();
		}

		key_compare		key_comp() const { return cmp_; }
		value_compare	value_comp() const { return tree_.value_comp(); }
		allocator_type	get_allocator() const { return tree_.get_allocator(); }
		//allocator_type	get_allocator() const { return alloc_; }

		iterator		find( const key_type& k ) {
			//return tree_.find(k);
			return tree_.find(make_pair(k, mapped_type()));
		}

		size_type	count( const key_type& k ) const {
			return tree_.count(make_pair(k, mapped_type()));
		}
	
		/*
		iterator lower_bound(const key_type& key){
			return (_tree.lower_bound(make_pair(key, mapped_type())));
		}	

		const_iterator lower_bound(const key_type& key) const{
			return (_tree.lower_bound(make_pair(key, mapped_type())));
		}	

		iterator upper_bound(const key_type& key){
			return (_tree.upper_bound(make_pair(key, mapped_type())));
		}	

		const_iterator upper_bound(const key_type& key) const{
			return (_tree.upper_bound(make_pair(key, mapped_type())));
		}

		pair<iterator, iterator> equal_range(const key_type & key){
			return (_tree.equal_range(make_pair(key, mapped_type())));
		}	

		pair<const_iterator, const_iterator> equal_range(const key_type & key) const{
			return (_tree.equal_range(make_pair(key, mapped_type())));
		}	
*/

		iterator lower_bound( const key_type& k ) {
			return tree_.lower_bound(make_pair(k, mapped_type()));
		}

		const_iterator lower_bound( const key_type& k ) const {
			return tree_.lower_bound(make_pair(k, mapped_type()));
		}
		
		iterator upper_bound( const key_type& k ) {
			return tree_.upper_bound(make_pair(k, mapped_type()));
		}
		
		const_iterator upper_bound( const key_type& k ) const {
			return tree_.upper_bound(make_pair(k, mapped_type()));
		}

		pair<iterator,iterator>	equal_range( const key_type& k) {}
		pair<const_iterator,const_iterator>	equal_range( const key_type& k) const {}

};

// all relational operators
// swap

}

#endif
