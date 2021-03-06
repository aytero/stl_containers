#ifndef RBTREE_HPP
# define RBTREE_HPP

# include "reverse_iterator.hpp"
# include "rbtree_iterator.hpp"
# include "utility.hpp"
# include "type_traits.hpp"

# include <iostream>

template < class Data, class Compare = std::less<Data>, class Allocator = std::allocator<Data> >
class RBTree {
	public:
		typedef Data									value_type;
		typedef Compare									value_compare;
		typedef Allocator								allocator_type;

		typedef typename Allocator::template
							rebind< Node<Data> >::other	node_allocator;
		typedef typename node_allocator::pointer		nodePtr;

		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef std::size_t								size_type;
		typedef std::ptrdiff_t							difference_type;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;

		typedef TreeIterator<Data>						iterator;
		typedef TreeIterator<const Data>				const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	private:
		allocator_type	val_alloc_;
		node_allocator	node_alloc_;
		value_compare	compare_;
		nodePtr			root_;
		nodePtr			null_node_;
		nodePtr			nil_;
		nodePtr			head_;
		size_type		size_;

	public:

		// Constructors
		RBTree() : root_(0), val_alloc_(Allocator()),
					node_alloc_(node_allocator()), compare_(Compare()), size_(0) {
			init();
			root_ = head_;
		}

		RBTree( const Compare& comp, const Allocator& alloc = Allocator()) 
						: val_alloc_(alloc), node_alloc_(node_allocator()), compare_(comp),
						root_(0), size_(0) {
			init();
			root_ = head_;
		}

		template <class InputIt>
			RBTree( typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt >::type first,
					InputIt last, const Compare& comp, const Allocator& alloc = Allocator() )
					: val_alloc_(alloc), node_alloc_(node_allocator()), compare_(comp) {
				size_ = 0;
				init();
				root_ = head_;
				for (; first != last; ++first)
					insert(*first);
			}

		RBTree( const RBTree &ref ) : compare_(ref.compare_), root_(0) {
			*this = ref;
		}

		RBTree& operator=( const RBTree &other ) {
			if (this == &other)
				return *this;
			val_alloc_ = other.val_alloc_;
			node_alloc_ = other.node_alloc_;
			compare_ = other.compare_;
			
			root_ == 0 ? init() : free_node(root_);
			if (other.size_ == 0)
				root_ = head_;
			else {
				root_ = copy_node(other.root_);
				copy_tree(root_, other.root_);
			}
			size_ = other.size_;
			return *this;
		}

		~RBTree() {
			free_node(root_);
			val_alloc_.destroy(head_->data);
			val_alloc_.deallocate(head_->data, 1);
			node_alloc_.deallocate(nil_, 1);
			node_alloc_.deallocate(head_, 1);
		}

		iterator begin() {
			return iterator(size_ == 0 ? head_ : iterator(tree_min(root_)));
		}

		const_iterator begin() const {
			return const_iterator(size_ == 0 ? head_ : const_iterator(tree_min(root_)));
		}

		iterator end() {
			return iterator(head_);
		}

		const_iterator end() const {
			return const_iterator(head_);
		}
		
		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}

		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}

		ft::pair<iterator,bool> insert( const value_type &val ){
			nodePtr new_node = findVal(root_, val);
			if (new_node)
				return ft::pair<iterator,bool>(iterator(new_node), false);

			new_node = create_node(val);
			insert_into_tree(new_node, root_);
			//rb_insert(new_node);
			rb_insert_fixup(new_node);
			++size_;
			set_tree_max();
			return ft::pair<iterator,bool>(iterator(new_node), true);
		}
	
		// with hint
		iterator insert( iterator position, const value_type& val ) {
			nodePtr new_node = findVal(root_, val);
			if (new_node)
				return iterator(new_node);

			new_node = create_node(val);
			if (position == begin()) {
				if (position != end() && compare_(val, *position))
					insert_into_tree(new_node, tree_min(root_));
				else
					insert_into_tree(new_node, root_);
			} else if (position == end()) {
				if (position != begin()&& compare_(*(--position), val))
					insert_into_tree(new_node, head_->parent);
				else
					insert_into_tree(new_node, root_);
			} else
				insert_into_tree(new_node, root_);

			rb_insert_fixup(new_node);
			++size_;
			set_tree_max();
			return iterator(new_node);
		}

		template <class InputIterator>
			void insert( typename ft::enable_if<!ft::is_integral<InputIterator>::value,
							InputIterator>::type first, InputIterator last ) {
				for (; first != last; ++first)
					insert(*first);
			}

		bool empty() const {
			return size_ == 0;
		}

		size_type size() const {
			return size_;
		}

		size_type max_size() const {
			return node_alloc_.max_size();
		}

		value_compare value_comp() const {
			return compare_;
		}

		allocator_type	get_allocator() const {
			return val_alloc_;
		}

		void erase( iterator position ) {
			nodePtr n = position.getNode();
			nodePtr to_free = n;
			nodePtr x;
			bool n_orig_color = n->color;

			if (is_nil(n->left)) {
				x = n->right;
				rb_transplant(n, n->right);
			} else if (is_nil(n->right)) {
				x = n->left;
				rb_transplant(n, n->left);
			} else {
				nodePtr z = n;
				n = tree_min(z->right);
				n_orig_color = n->color;
				x = n->right;
				if (n->parent != z) {
					rb_transplant(n, n->right);
					n->right = z->right;
					z->right->parent = n;
				}
				rb_transplant(z, n);
				n->left = z->left;
				n->left->parent = n;
				n->color = z->color;
			}

			val_alloc_.destroy(to_free->data);
			val_alloc_.deallocate(to_free->data, 1);
			node_alloc_.deallocate(to_free, 1);

			if (n_orig_color == _tree_black)
				rb_erase_fixup(x);

			--size_;
			nil_->parent = 0;
			if (size_ == 0)
				root_ = head_;
			else {
				if (size_ != 1)
					x = tree_max(root_);
				else
					x = root_;
				x->right = head_;
				head_->parent = x;
			}
		}

		size_type erase( const value_type& value ) {
			nodePtr	node = findVal(root_, value);

			if (node)
				erase(iterator(node));
			return (node != 0);// number of elems erased
		}

		//template <class InputIterator>
			//void erase( typename ft::enable_if<!ft::is_integral<InputIterator>::value,
			//				InputIterator>::type first, InputIterator last ) {
			void erase( iterator first, iterator last ) {
				if (first == begin() && last == end())
					clear();
				else {
					while (first != last)
						erase(first++);
				}
			}

		void clear() {
			free_node(root_);
			root_ = head_;
			head_->parent = 0;
			size_ = 0;
		}

		const nodePtr getRoot() const { return root_; }

		iterator find( const value_type& val ) {
			nodePtr res = findVal(root_, val);
			return res == 0 ? end() : iterator(res);
		}
		
		const_iterator find( const value_type& val ) const {
			nodePtr res = findVal(root_, val);
			return res == 0 ? end() : const_iterator(res);
		}

		size_type count( const value_type& val ) const {
			return find(val) != end();
		}

		iterator lower_bound( const value_type& val ) {
			iterator ite = end();
			for (iterator it = begin(); it != ite; ++it) {
				if (!compare_(*it, val))
					return it;
			}
			return ite;
		}

		const_iterator lower_bound( const value_type& val ) const {
			const_iterator ite = end();
			for (const_iterator it = begin(); it != ite; ++it) {
				if (!compare_(*it, val))
					return it;
			}
			return ite;
		}

		iterator upper_bound( const value_type& val ) {
			iterator ite = end();
			for (iterator it = begin(); it != ite; ++it) {
				if (compare_(val, *it))
					return it;
			}
			return ite;
		}
		
		const_iterator upper_bound( const value_type& val ) const {
			const_iterator ite = end();
			for (const_iterator it = begin(); it != ite; ++it) {
				if (compare_(val, *it))
					return it;
			}
			return ite;
		}

		ft::pair<iterator,iterator> equal_range( const value_type& val ) {
			return ft::make_pair(lower_bound(val), upper_bound(val));
		}

		ft::pair<const_iterator,const_iterator> equal_range( const value_type& val ) const {
			return ft::make_pair(lower_bound(val), upper_bound(val));
		}

		void swap( RBTree& other ) {
			std::swap(val_alloc_, other.val_alloc_);
			std::swap(node_alloc_, other.node_alloc_);
			std::swap(compare_, other.compare_);
			std::swap(root_, other.root_);
			std::swap(nil_, other.nil_);
			std::swap(head_, other.head_);
			std::swap(size_, other.size_);
		}

	private:
		void init() {
			nil_ = node_alloc_.allocate(1);
			node_alloc_.construct(nil_, Node<Data>());
			nil_->color = _tree_black;
			nil_->is_nil = true;
			head_ = node_alloc_.allocate(1);
			node_alloc_.construct(head_, Node<Data>());
			head_->data = val_alloc_.allocate(1);
			val_alloc_.construct(head_->data, Data());
			head_->color = _tree_black;
		}

		/*
		nodePtr findVal( nodePtr node, const value_type& val ) const {
			while (node && !is_nil(node)) {
				if (compare_(val, *node->data))
					node = node->left;
				else if (compare_(*node->data, val))
					node = node->right;
				else
					break ;
			}
			return node;
		}
		*/

		nodePtr findVal( nodePtr node, const value_type& data ) const {
			if (!node || is_nil(node))
				return 0;
			if (compare_(data, *node->data))
				return findVal(node->left, data);
			if (compare_(*node->data, data))
				return findVal(node->right, data);
			return node;
		}


		void free_node( nodePtr n ) {
			if (!n || is_nil(n))
				return ;
			free_node(n->left);
			free_node(n->right);
			val_alloc_.destroy(n->data);
			val_alloc_.deallocate(n->data, 1);
			node_alloc_.deallocate(n, 1);
		}

		void treePrint() {
			if (root_)
				printHelper(root_, 0);
		}

		void printHelper(const nodePtr root, int lvl) {
			if (!root)
				return ;
			printHelper(root->right, lvl + 1);
			for (int i = 0; i < lvl * 4; i++)
				std::cout << " ";
			std::cout << root->data << (root->color == false ? "r" : "b") << std::endl;
			printHelper(root->left, lvl + 1);
		}

		void rotateLeft( nodePtr n ) {
			nodePtr	pivot = n->right;

			n->right = pivot->left;
			if (!is_nil(pivot->left))
				pivot->left->parent = n;
			pivot->parent = n->parent;
			if (n->parent == 0)
				root_ = pivot;
			else if (n == n->parent->left)
				n->parent->left = pivot;
			else
				n->parent->right = pivot;
			pivot->left = n;
			n->parent = pivot;
			/*
			pivot->parent = n->parent;
			if (n->parent != NULL) {
				if (n->parent->left == n)
					n->parent->left = pivot;
				else
					n->parent->right = pivot;
			} else
				root_ = pivot;
			n->right = pivot->left;
			if (pivot->left != NULL)
				pivot->left->parent = n;
			n->parent = pivot;
			pivot->left = n;
			*/
		}

		void	rotateRight( nodePtr n ) {
			nodePtr	pivot = n->left;

			n->left = pivot->right;
			if (!is_nil(pivot->right))
				pivot->right->parent = n;
			pivot->parent = n->parent;
			if (n->parent == 0)
				root_ = pivot;
			else if (n == n->parent->left)
				n->parent->left = pivot;
			else
				n->parent->right = pivot;
			pivot->right = n;
			n->parent = pivot;
			/*
			pivot->parent = n->parent;
			if (n->parent != NULL) {
				if (n->parent->left == n)
					n->parent->left = pivot;
				else
					n->parent->right = pivot;
			} else
				root_ = pivot;
			n->left = pivot->right;
			if (pivot->right != NULL)
				pivot->right->parent = n;
			n->parent = pivot;
			pivot->right = n;
			*/
		}

		bool is_nil( nodePtr node ) const {
			return node == nil_ || node == head_;
		}

		nodePtr create_node( const value_type& val ) {
			nodePtr new_node = node_alloc_.allocate(1);
			pointer new_val = val_alloc_.allocate(1);
			val_alloc_.construct(new_val, val);
			//new (new_node) Node<value_type>(new_val);
			node_alloc_.construct(new_node, Node<value_type>(new_val));
			new_node->left = nil_;
			new_node->right = nil_;
			return new_node;
		}

		nodePtr copy_node( nodePtr other ) {
			nodePtr new_node = node_alloc_.allocate(1);
			node_alloc_.construct(new_node, Node<Data>());
			new_node->color = other->color;
			new_node->is_nil = other->is_nil;
			if (other->data) {
				new_node->data = val_alloc_.allocate(1);
				val_alloc_.construct(new_node->data, *other->data);
			}
			return new_node;
		}

		void copy_tree( nodePtr node, nodePtr other ) {
			if (other->left->is_nil)
				node->left = nil_;
			else {
				node->left = copy_node(other->left);
				node->left->parent = node;
				copy_tree(node->left, other->left);
			}

			if (other->right->is_nil)
				node->right = nil_;
			else if (other->right->right == 0) {
				node->right = head_;
				head_->parent = node;
			} else {
				node->right = copy_node(other->right);
				node->right->parent = node;
				copy_tree(node->right, other->right);
			}
		}

		void set_tree_max() {
			nodePtr new_tree_max = tree_max(root_);
			new_tree_max->right = head_;
			head_->parent = new_tree_max;
		}

		nodePtr insert_to_node( nodePtr root, nodePtr new_node ) {
			if (compare_(*new_node->data, *root->data)) {
				if (!is_nil(root->left))
					return insert_to_node(root->left, new_node);
				root->left = new_node;
			} else {
				if (!is_nil(root->right)) {
					return insert_to_node(root->right, new_node);
				}
				root->right = new_node;
			}
			new_node->parent = root;
			return (new_node);
		}
		
		nodePtr insert_into_tree(nodePtr new_node, nodePtr where){
			if (root_ == head_)
				root_ = new_node;
			else
				insert_to_node(where, new_node);
			return (new_node);
		}

		void rb_insert( nodePtr new_node ) {
			nodePtr y = nil_;
			nodePtr x = root_;
			//while (!is_nil(x)) {
			while (x != nil_) {
				y = x;
				if (compare_(*new_node->data, *x->data)) {// new_node.key < x.key
					x = x->left;
				} else {
					x = x->right;
				}
			}
			new_node->parent = y;
			if (is_nil(y)) {
				root_ = new_node;
			} else if (compare_(*new_node->data, *y->data)) {// new_node.key < y.key
				y->left = new_node;
			} else {
				y->right = new_node;
			}
			new_node->left = nil_;
			new_node->right = nil_;
			new_node->color = _tree_red;
		}

		void rb_insert_fixup( nodePtr node ) {
			if (node != root_ && node->parent != root_) {
				while (node != root_ && node->parent->color == _tree_red) {
					if (node->parent == node->parent->parent->left) {
						nodePtr	y = node->parent->parent->right;// uncle node
						if (y->color == _tree_red) {
							node->parent->color = _tree_black;
							y->color = _tree_black;
							node->parent->parent->color = _tree_red;
							node = node->parent->parent;
						} else {
							if (node == node->parent->right) {
								node = node->parent;
								rotateLeft(node);
							}
							node->parent->color = _tree_black;
							node->parent->parent->color = _tree_red;
							rotateRight(node->parent->parent);
						}
					} else {
						nodePtr y = node->parent->parent->left;
						if (y->color == _tree_red) {
							node->parent->color = _tree_black;
							y->color = _tree_black;
							node->parent->parent->color = _tree_red;
							node = node->parent->parent;
						} else {
							if (node == node->parent->left) {
								node = node->parent;
								rotateRight(node);
							}
							node->parent->color = _tree_black;
							node->parent->parent->color = _tree_red;
							rotateLeft(node->parent->parent);
						}
					}
				}
			}
			root_->color = _tree_black;
		}

		void rb_transplant( nodePtr u, nodePtr v ) {
			if (u == root_)
				root_ = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		void rb_erase_fixup( nodePtr x ) {
			nodePtr w = nil_;// brother

			while (x != root_ && x->color == _tree_black) {
				if (x == x->parent->left) {
					w = x->parent->right;
					if (w->color == _tree_red) {
						w->color = _tree_black;
						x->parent->color = _tree_red;
						rotateLeft(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == _tree_black && w->right->color == _tree_black) {
						w->color = _tree_red;
						x = x->parent;
					} else {
						if (w->right->color == _tree_black) {
							w->left->color = _tree_black;
							w->color = _tree_red;
							rotateRight(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = _tree_black;
						w->right->color = _tree_black;
						rotateLeft(x->parent);
						x = root_;
					}
				} else {
					w = x->parent->left;
					if (w->color == _tree_red) {
						w->color = _tree_black;
						x->parent->color = _tree_red;
						rotateRight(x->parent);
						w = x->parent->left;
					}
					if (w->right->color == _tree_black && w->left->color == _tree_black) {
						w->color = _tree_red;
						x = x->parent;
					} else {
						if (w->left->color == _tree_black) {
							w->right->color = _tree_black;
							w->color = _tree_red;
							rotateLeft(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = _tree_black;
						w->left->color = _tree_black;
						rotateRight(x->parent);
						x = root_;
					}
				}
			}
		}

		nodePtr	tree_min( nodePtr n ) const {
			nodePtr	ptr = n;
			
			while (ptr != 0 && !is_nil(ptr->left))
				ptr = ptr->left;
			return ptr;
		}

		nodePtr	tree_max( nodePtr n ) const {
			nodePtr	ptr = n;
			
			while (ptr->right != 0 && !is_nil(ptr->right))
				ptr = ptr->right;
			return ptr;
		}
};

template <class Val, class Cmp, class Alloc>
	bool operator==( const RBTree<Val,Cmp,Alloc>& lhs,
					const RBTree<Val,Cmp,Alloc>& rhs) {
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

template <class Val, class Cmp, class Alloc>
	bool operator<( const RBTree<Val,Cmp,Alloc>& lhs,
					const RBTree<Val,Cmp,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

template <class Val, class Cmp, class Alloc>
	void swap( const RBTree<Val,Cmp,Alloc>& lhs,
				const RBTree<Val,Cmp,Alloc>& rhs) {
		lhs.swap(rhs);
	}

#endif
