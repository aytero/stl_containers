#ifndef RBTREE_HPP
# define RBTREE_HPP

# include "rbtree_iterator.hpp"

# include <iostream>

template < class Data, class Compare = std::less<Data>, class Allocator = std::allocator<Data> >
class RBTree {

	public:

		typedef Data	value_type;
		typedef Compare	value_compare;
		typedef Allocator	allocator_type;

		//typename Alloc::template rebind<Node>::other alloc_;
		// node alloc
		// node alloc type
		typedef typename Allocator::template rebind< Node<Data> >::other	node_allocator;
		typedef typename node_allocator::pointer	nodePtr; // node_pointer

		typedef typename Allocator::reference		reference;
		typedef typename Allocator::const_reference	const_reference;
		typedef std::size_t							size_type;
		typedef std::ptrdiff_t						difference_type;
		//typedef ft::iterator_traits<iterator>::difference_type	diference_type;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;

		typedef TreeIterator<Data>						iterator;
		typedef TreeIterator<const Data>				const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	private:
		allocator_type	val_alloc_;
		node_allocator	node_alloc_;
		value_compare	compare_;
		nodePtr			root_;
		nodePtr			nil_;
		nodePtr			head_;
		size_type		size_;

		//struct Node*	tnull_;
	

	public:
		RBTree() : root_(NULL) {}
		
		//RBTree( Data data ) : root_(NULL) {
		//}

		//RBTree( const RBTree &ref ) {}
		//const RBTree& operator=( const RBTree &other ) {}

		~RBTree() { free_node(root_); }
	
		//ft::pair<iterator, bool> insert(const value_type &value){
		//return ft::pair<iterator, bool>
		void	insert( const Data& data ) {
			//nodePtr	node = new Node(data);
			nodePtr	node = new Node<value_type>(data);

			root_ = insertBST(root_, node);
			balanceInsertRBTree(node);
			//fixInsertRBTree(node);
		}

		/*
		iterator insert( iterator position, const Data& data ) {
			;
		}
*/
		//const_iterator insert( const_iterator position, const Data& data ) {
		//	;
		//}
	
		/*
		template<class InputIt>
		void insert(typename ft::enable_if< !ft::is_integral<InputIt>::value,
				InputIt >::type first, InputIt last) {
				for (; first != last; ++first)
					insert(*first);
		}
		*/

		void	deleteValue( Data data ) {
			nodePtr	node = findVal(root_, data);

			// not Data but iterator
			// check if n has only  one !null child
			/*
		if(n->left && n->right)
		{
			rbnode *p = n->parent;
			rbnode *nl = n->left;
			rbnode *nr = n->right;
			rbnode *s = n->next();
			rbnode *sp = s->parent;
			rbnode *sr = s->right;
			if(p && n==p->left)
				p->left = s;
			else if(p && n==p->right)
				p->right = s;
			s->parent = p;
			s->left = nl;
			if(nl)
				nl->parent = s;
			if(s==nr)
			{
				s->right = n;
				n->parent = s;
			}else{
				s->right = nr;
				nr->parent = s;
				sp->left = n;
				n->parent = sp;
			}
			n->right = sr;
			if(sr)
				sr->parent = n;
			n->left = NULL;
			_root = get_root(s);
		}
		*/

			deleteNode(node);
			//balanceDeleteRBTree(node);
			
			//deleteBST(root_, data);//tmp
		}

		// private later
		void	treePrint() {
			if (root_)
				printHelper(root_, 0);
		}

		const nodePtr getRoot() const { return root_; }

		// constructor, allocator
		//colorSwap() {}// or recolor
		//delete() {}// or erase
		//getPredecessor
		// find val
		// iterators ? 
/*
	rbnode *find(Key key) const
	{
		rbnode *n = _root;
		while (n)
			if (_comp(key, n->key))
				n = n->left;
			else if (_comp(n->key, key))
				n = n->right;
			else
				break;
		return n;
	}
*/
		nodePtr find( Data data ) const {
			nodePtr	node = root_;

			while (node) {
				if (data < node->data)
				//if (cmp_(data, node->data))
					node = node->left;
				else if (node->data < data)
				//else if (cmp_(node->data, data))
					node = node->right;
				else
					break ;
			}
			return node;
		}





	private:

		nodePtr get_root( nodePtr n ) {
			while (n && n->parent)
				n = n->parent;
			return n;
		}
	
	
		void printHelper(const nodePtr root, int lvl)
		{
			if (!root)
				return ;
			printHelper(root->right, lvl + 1);
			for (int i = 0; i < lvl * 4; i++)
				std::cout << " ";
			std::cout << root->data << (root->color == RED ? "r" : "b") << std::endl;
			printHelper(root->left, lvl + 1);
		}

		void rotateLeft( nodePtr n ) {
			nodePtr	pivot = n->right;

			std::cout << "rl\n";

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
		}

		void	rotateRight( nodePtr n ) {
			nodePtr	pivot = n->left;

			std::cout << "rr\n";
	
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
		}

		nodePtr grandparent( nodePtr n ) {
			if (n != NULL && n->parent != NULL)
				return n->parent->parent;
			return NULL;
		}

		nodePtr uncle( nodePtr n ) {
			nodePtr	g = grandparent(n);
			if (g == NULL)
				return NULL;
			if (n->parent == g->left)
				return g->right;
			return g->left;
		}


		// recolor opts
		void	insert_case1( nodePtr n ) {

			std::cout << n->data <<"\n";
			std::cout << "case1\n";
				
			//if (n->data == 8 && n->left) 
			//o	std::cout << n->left->color << "  color of 4\n";
			if (n->parent == NULL)
				n->color = BLACK;
			else
				insert_case2(n);
		}

		void	insert_case2( nodePtr n ) {

			std::cout << "case2\n";
			//if (n->data == 11) 
			//	std::cout << uncle(n)->color << "  color of 4\n";

			if (n->parent->color == BLACK)
				return ;
			insert_case3(n);
		}

		void	insert_case3( nodePtr n ) {
			nodePtr u = uncle(n);
			nodePtr	g;
			std::cout << "case3\n";

			if ((u != NULL) && (u->color == RED)) {
				n->parent->color = BLACK;
				u->color = BLACK;
				g = grandparent(n);
				g->color = RED;
				insert_case1(g);
			} else
				insert_case4(n);
		}

		void	insert_case4( nodePtr n ) {

			std::cout << "case4\n";

			nodePtr	g = grandparent(n);
			if ((n == n->parent->right) && (n->parent == g->left)) {
				rotateLeft(n->parent);
				n = n->left;
			} else if ((n == n->parent->left) && (n->parent == g->right)) {
				rotateRight(n->parent);
				n = n->right;
			}
			insert_case5(n);
		}

		void	insert_case5( nodePtr n ) {
			nodePtr	g = grandparent(n);
			std::cout << "case5\n";

			n->parent->color = BLACK;
			g->color = RED;
			if ((n == n->parent->left) && (n->parent == g->left))
				rotateRight(g);
			else
				rotateLeft(g);
		}



		nodePtr insertBST( nodePtr root, nodePtr n ) {
			if (root == NULL)
				return n;
			if (n->data < root->data) {
				root->left = insertBST(root->left, n);
				root->left->parent = root;
			} else if (n->data > root->data) {
				root->right = insertBST(root->right, n);
				root->right->parent = root;
			}
			return root;
		}
		
		void	balanceInsertRBTree( nodePtr n ) {
			insert_case1(n);
		}

		void free_node( nodePtr n ) {
			if (!n)
				return ;
			free_node(n->left);
			free_node(n->right);
			n->~Node();
			//alloc_.deallocate(n, 1);
			delete n;
		}


		nodePtr	sibling( nodePtr n ) {
			if (n == n->parent->left)
				return n->parent->right;
			return n->parent->left;
		}

		nodePtr findVal( nodePtr root, Data data ) {
			if (root == NULL)
				return root;

			if (data < root->data)
				return findVal(root->left, data);
			if (data > root->data)
				return findVal(root->right, data);

			if (root->left == NULL || root->right == NULL)
				return root;

			nodePtr	tmp = minValueNode(root->right);
			root->data = tmp->data;
			return findVal(root->right, tmp->data);

			//return root;//tmp
		}

		void	replaceNode( nodePtr n, nodePtr child ) {

			std::cout << "replace node\n";
			if (child)
				child->parent = n->parent;
			if (n->parent) {
				if (n == n->parent->left)
					n->parent->left = child;
				else
					n->parent->right = child;
			} else {
				root_ = child;
			}
		}

		// works with prefound by value node
		void	deleteNode( nodePtr n ) {
			nodePtr	child = n->right ? n->right : n->left;


			replaceNode(n, child);
			std::cout << "del node\n";
			// && child same cause of null ptrs not nodes
			//if (n->color == BLACK) {
			if (n->color == BLACK && child) {
					std::cout << "EEEE\n";
				if (child->color == RED) {
					child->color = BLACK;
				} else {
					delete_case1(child);
				}
			}
			//n->~Node();
			//alloc_.deallocate(n, 1);
			// or
			free(n);
		}

		void	delete_case1( nodePtr n ) {
			std::cout << "del case1\n";
			if (n->parent != NULL)
				delete_case2(n);
		}

		void	delete_case2( nodePtr n ) {
			nodePtr	s = sibling(n);

			std::cout << "del case2\n";
			if (s->color == RED) {
				n->parent->color = RED;
				s->color = BLACK;
				if (n == n->parent->left)
					rotateLeft(n->parent);
				else
					rotateRight(n->parent);
			}
			delete_case3(n);
		}

		void	delete_case3( nodePtr n ) {
			nodePtr	s = sibling(n);

			std::cout << "del case3\n";
			if (n->parent->color == BLACK && s->color == BLACK
					&& s->left->color == BLACK && s->right->color == BLACK) {
				s->color = RED;
				delete_case1(n->parent);
			} else
				delete_case4(n);
		}

		void	delete_case4( nodePtr n ) {
			nodePtr	s = sibling(n);

			std::cout << "del case4\n";
			if (n->parent->color == RED && s->color == BLACK
					&& s->left->color == BLACK && s->right->color == BLACK) {
				s->color = RED;
				n->parent->color = BLACK;
			} else
				delete_case5(n);
		
		}

		void	delete_case5( nodePtr n ) {
			nodePtr	s = sibling(n);

			std::cout << "del case5\n";
			if (s->color == BLACK) {
				if (n->parent->left && s->right->color == BLACK && s->left->color == RED) {
					s->color = RED;
					s->left->color = BLACK;
					rotateRight(s);
				} else if (n == n->parent->right && s->left->color == BLACK && s->right->color == RED) {
					s->color = RED;
						s->right->color = BLACK;
					rotateLeft(s);
				}
			}
			delete_case6(n);
		}

		void	delete_case6( nodePtr n ) {
			nodePtr	s = sibling(n);

			std::cout << "del case6\n";
			s->color = n->parent->color;
			n->parent->color = BLACK;

			if (n == n->parent->left) {
				s->right->color = BLACK;
				rotateLeft(n->parent);
			} else {
				s->left->color = BLACK;
				rotateRight(n->parent);
			}
		}

		/*
		nodePtr	deleteBST( nodePtr root, Data data ) {
			if (root == NULL)
				return root;

			if (data < root->data)
				return deleteBST(root->left, data);
			if (data > root->data)
				return deleteBST(root->right, data);

			if (root->left == NULL || root->right == NULL)
				return root;

			nodePtr	tmp = minValueNode(root->right);
			root->data = tmp->data;
			return deleteBST(root->right, tmp->data);

			//return root;//tmp
		}
*/

		nodePtr	minValueNode( nodePtr n ) {
			nodePtr	ptr = n;
			
			while (ptr->left != NULL)
				ptr = ptr->left;
			return ptr;
		}

		nodePtr	maxValueNode( nodePtr n ) {
			nodePtr	ptr = n;
			
			while (ptr->right != NULL)
				ptr = ptr->right;
			return ptr;
		}

		/*
		void	balanceDeleteRBTree( nodePtr node ) {
			if (node == NULL)
				return ;
			if (node == root_) {
				root_ = NULL;
				return ;
			}

			if (node->color == RED || node->left->color == RED || node->right == RED) {
				;
				//Node*	child = node->left;
			} else {
				;
			}

			if (node == node->parent->left)
				node->parent->left = NULL;
			else
				node->parent->right = NULL;
			delete(node);
			//delete node;
			root_->color = BLACK;
		}
		*/
};

#endif
