#ifndef SET_HPP
# define SET_HPP

# include "utility.hpp"
# include "type_traits.hpp"
# include "iterator_traits.hpp"
# include "reverse_iterator.hpp"
# include "rbtree.hpp"

namespace ft {
	template <class Key, class Compare = std::less<Key>,
			 class Allocator = std::allocator<Key> >
	class set {

	public:
		typedef Key											key_type;
		typedef Key											value_type;
		typedef Compare										key_compare;
		typedef Compare										value_compare;
		typedef Allocator									allocator_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef RBTree<Key,Compare,Allocator>				tree_type;
		typedef std::size_t									size_type;
		typedef std::ptrdiff_t								difference_type;
		typedef typename Allocator::pointer					pointer;
		typedef typename Allocator::const_pointer			const_pointer;
		typedef typename tree_type::iterator				iterator;
		typedef typename tree_type::const_iterator			const_iterator;
		typedef typename tree_type::reverse_iterator		reverse_iterator;
		typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

	private:
		tree_type	tree_;

	public:

		explicit set( const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
						: tree_(tree_type(comp, alloc)) {}

		template <class InputIterator>
			set( InputIterator first, InputIterator last,
					const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) 
					: tree_(tree_type(first, last, comp, alloc)) {}

		set( const set<Key,Compare,Allocator>& ref ) : tree_(tree_type(ref.tree_)) {}

		~set() {}

		set<Key,Compare,Allocator>& operator=( const set<Key,Compare,Allocator>& other ) {
			tree_ = other.tree_;
			return *this;
		}

		allocator_type get_allocator() const {
			return tree_.get_allocator();
		}

		iterator begin() {
			return tree_.begin();
		}

		const_iterator begin() const {
			return tree_.begin();
		}

		iterator end() {
			return tree_.end();
		}

		const_iterator end() const {
			return tree_.end();
		}
			
		reverse_iterator rbegin() {
			return tree_.rbegin();
		}

		const_reverse_iterator rbegin() const {
			return tree_.rbegin();
		}

		reverse_iterator rend() {
			return tree_.rend();
		}

		const_reverse_iterator rend() const {
			return tree_.rend();
		}

		bool empty() const {
			return tree_.empty();
		}

		size_type size() const {
			return tree_.size();
		}

		size_type max_size() const {
			return tree_.max_size();
		}

		pair<iterator,bool> insert( const value_type& val ) {
			return tree_.insert(val);
		}

		iterator insert( iterator position, const value_type& val ) {
			return tree_.insert(position, val);
		}

		template <class InputIt>
			void insert( typename enable_if<!is_integral<InputIt>::value, InputIt>::type first,
						InputIt last ) {
				tree_.insert(first, last);
			}

		void erase( iterator position ) {
			tree_.erase(position);
		}

		size_type erase( const key_type& k ) {
			return tree_.erase(k);
		}

		void erase( iterator first, iterator last ) {
			tree_.erase(first, last);
		}

		void swap( set<Key,Compare,Allocator>& other ) {
			tree_.swap(other.tree_);
		}

		void clear() {
			tree_.clear();
		}

		key_compare key_comp() const {
			return tree_.value_comp();
		}

		value_compare value_comp() const {
			return tree_.value_comp();
		}

		iterator find( const key_type& x ) {
			return tree_.find(x);
		}

		const_iterator find( const key_type& x ) const {
			return tree_.find(x);
		}

		size_type count( const key_type& x ) const {
			return tree_.count(x);
		}

		iterator lower_bound( const key_type& x ) {
			return tree_.lower_bound(x);
		}

		const_iterator lower_bound( const key_type& x ) const {
			return tree_.lower_bound(x);
		}

		iterator upper_bound( const key_type& x ) {
			return tree_.upper_bound(x);
		}

		iterator upper_bound( const key_type& x ) const {
			return tree_.upper_bound(x);
		}

		pair<iterator, iterator> equal_range( const key_type& x ) {
			return tree_.equal_range(x);
		}

		pair<const_iterator, const_iterator> equal_range( const key_type& x ) const {
			return tree_.equal_range(x);
		}
		
		template <class key, class compare, class allocator>
			friend bool operator==( const set<key,compare,allocator>& lhs,
								const set<key,compare,allocator>& rhs);
		
		template <class key, class compare, class allocator>
			friend bool operator<( const set<key,compare,allocator>& lhs,
						const set<key,compare,allocator>& rhs); 
	};

	template <class Key, class Compare, class Allocator>
		bool operator==( const set<Key,Compare,Allocator>& lhs,
						const set<Key,Compare,Allocator>& rhs) {
			return lhs.tree_ == rhs.tree_;
		}

	template <class Key, class Compare, class Allocator>
		bool operator!=( const set<Key,Compare,Allocator>& lhs,
						const set<Key,Compare,Allocator>& rhs) {
			return !(lhs == rhs);
		}

	template <class Key, class Compare, class Allocator>
		bool operator<( const set<Key,Compare,Allocator>& lhs,
						const set<Key,Compare,Allocator>& rhs) {
			return lhs.tree_ < rhs.tree_;
		}
	
	template <class Key, class Compare, class Allocator>
		bool operator>( const set<Key,Compare,Allocator>& lhs,
						const set<Key,Compare,Allocator>& rhs) {
			return rhs < lhs;
		}
	
	template <class Key, class Compare, class Allocator>
		bool operator<=( const set<Key,Compare,Allocator>& lhs,
						const set<Key,Compare,Allocator>& rhs) {
			return !(rhs < lhs);
		}
	
	template <class Key, class Compare, class Allocator>
		bool operator>=( const set<Key,Compare,Allocator>& lhs,
						const set<Key,Compare,Allocator>& rhs) {
			return !(lhs < rhs);
		}
}

template <class Key, class Compare, class Allocator>
	void swap( ft::set<Key,Compare,Allocator>& lhs,
				ft::set<Key,Compare,Allocator>& rhs ) {
		lhs.swap(rhs);
	}

#endif
