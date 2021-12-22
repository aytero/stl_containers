#ifndef RBTREE_ITERATOR_HPP
# define RBTREE_ITERATOR_HPP

template <typename T>
class TreeIterator {
	Node*	ptr_;

	/*
		node_pointer tree_min(node_pointer n) const {
			while(n->left != NULL && !n->left->is_nil)
				n = n->left;
			return n;
		}

		node_pointer tree_max(node_pointer n) const {
			while (!n->right->is_nil)
				n = n->right;
			return n;
		}
		*/

	public:
		//typedefs
		typedef std::bidirectional_iterator_tag						iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type		value_type;
		typedef typename ft::iterator_traits<T*>::reference			reference;
		typedef typename ft::iterator_traits<T*>::pointer			pointer;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
		typedef Node<typename ft::remove_const<value_type>::type >* node_ptr;

		//methods

		TreeIterator() {}
		TreeIterator( const TreeIterator &ref ) {}
		~TreeIterator() {}
		TreeIterator& operator=( const TreeIterator &other ) {}

		reference operator*() { return *ptr_; }
		pointer operator->() { return ptr_; }

		TreeIterator& operator++() {
			//++ptr_;
			//return *this;
		}

		TreeIterator operator++( int ) {
			//TreeIterator tmp(*this);
			//++ptr_;
			//return tmp;
		}

		TreeIterator& operator--() {
			//--ptr_;
			//return *this;
		}

		TreeIterator operator--( int ) {
			//TreeIterator tmp(*this);
			//--ptr_;
			//return tmp;
		}
};

template <class A, class B>
	bool operator==( const TreeIterator<A> &lhs, const TreeIterator<B> &rhs ) {
		return lhs.ptr_() == rhs.ptr_();
	}

template <class A, class B>
	bool operator!=( const TreeIterator<A> &lhs, const TreeIterator<B> &rhs ) {
		return lhs.ptr_() != rhs.ptr_();

#endif
