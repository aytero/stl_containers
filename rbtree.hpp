#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <iostream>


namespace ft
{
	template < class Data, class Alloc = std::allocator<Data> >
		class RBTree;
}


// < ..., class Compare >
template < class Data, class Alloc >
class	ft::RBTree {
	public:
		enum color_t { BLACK, RED };

		struct Node {
			Data		data;
			struct Node	*parent;
			struct Node	*left;
			struct Node	*right;
			int			color;
			//bool		color;
			//enum color_t color;

			Node( Data data ) {
				this->data = data;
				color = RED;
				left = right = parent = NULL;
			}
		};
		//typedef struct Node	NodePtr;
	
		RBTree() : root_(NULL) {}
		
		//RBTree( Data data ) : root_(NULL) {
		//	
		//}

		//RBTree( const RBTree &ref ) {}
		//const RBTree& operator=( const RBTree &other ) {}

		~RBTree() { free_node(root_); }
	
		/*
		struct Node*	insert( struct Node* p, Data x ) {
			// BST insert 
			// balance/fix tree

			Node*	tmp = root_;
			
			if (p == NULL) {
				p = new Node;
				//struct Node *n = alloc_.allocate(1);
				//new (n) Node(Data);
				p->data = x;
				p->left = p->right = NULL;
				p->parent = tmp;
				p->color = 1;
			} else if (x < p->data)
				p->left = insert(p->left, x);
			else if (x > p->data)
				p->right = insert(p->right, x);
			root_ = get_root(p);
			return p;
		}
		*/
		void	insert( Data data ) {
			Node*	node = new Node(data);

			root_ = insertBST(root_, node);
			balanceInsertRBTree(node);
			//fixInsertRBTree(node);
		}

		void	deleteValue( Data data ) {
			Node *node = findVal(root_, data);
			deleteNode(node);
			//balanceDeleteRBTree(node);
			
			//deleteBST(root_, data);//tmp
		}

		// private later
		void	treePrint() {
			if (root_)
				printHelper(root_, 0);
		}

		const Node*	getRoot() const { return root_; }

		// constructor, allocator
		//colorSwap() {}// or recolor
		//delete() {}// or erase
		//getPredecessor

	private:
		struct Node*	root_;
		//struct Node*	tnull_;
		typename Alloc::template rebind<Node>::other alloc_;
	
		Node *get_root( struct Node *n ) {
			while (n && n->parent)
				n = n->parent;
			return n;
		}
	
	
		void printHelper(const struct Node *root, int lvl)
		{
			if (!root)
				return ;
			printHelper(root->right, lvl + 1);
			for (int i = 0; i < lvl * 4; i++)
				std::cout << " ";
			std::cout << root->data << (root->color == RED ? "r" : "b") << std::endl;
			printHelper(root->left, lvl + 1);
		}

		void rotateLeft( Node* n ) {
			Node *pivot = n->right;

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

		void	rotateRight( Node* n ) {
			Node*	pivot = n->left;

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

		Node*	grandparent( Node *n ) {
			if (n != NULL && n->parent != NULL)
				return n->parent->parent;
			return NULL;
		}

		Node*	uncle( Node* n ) {
			Node*	g = grandparent(n);
			if (g == NULL)
				return NULL;
			if (n->parent == g->left)
				return g->right;
			return g->left;
		}


		// recolor opts
		void	insert_case1( Node* n ) {

			std::cout << n->data <<"\n";
			std::cout << "case1\n";
				
			//if (n->data == 8 && n->left) 
			//o	std::cout << n->left->color << "  color of 4\n";
			if (n->parent == NULL)
				n->color = BLACK;
			else
				insert_case2(n);
		}

		void	insert_case2( Node* n ) {

			std::cout << "case2\n";
			//if (n->data == 11) 
			//	std::cout << uncle(n)->color << "  color of 4\n";

			if (n->parent->color == BLACK)
				return ;
			insert_case3(n);
		}

		void	insert_case3( Node* n ) {
			Node*	u = uncle(n);
			Node*	g;
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

		void	insert_case4( Node* n ) {

			std::cout << "case4\n";

			Node *g = grandparent(n);
			if ((n == n->parent->right) && (n->parent == g->left)) {
				rotateLeft(n->parent);
				n = n->left;
			} else if ((n == n->parent->left) && (n->parent == g->right)) {
				rotateRight(n->parent);
				n = n->right;
			}
			insert_case5(n);
		}

		void	insert_case5( Node* n ) {
			Node*	g = grandparent(n);
			std::cout << "case5\n";

			n->parent->color = BLACK;
			g->color = RED;
			if ((n == n->parent->left) && (n->parent == g->left))
				rotateRight(g);
			else
				rotateLeft(g);
		}



		Node*	insertBST( Node *root, Node *n ) {
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
		
		void	balanceInsertRBTree( Node* n ) {
			insert_case1(n);
		}

		void free_node( struct Node *n ) {
			if (!n)
				return ;
			free_node(n->left);
			free_node(n->right);
			n->~Node();
			//alloc_.deallocate(n, 1);
			delete n;
		}


		Node*	sibling( Node* n ) {
			if (n == n->parent->left)
				return n->parent->right;
			return n->parent->left;
		}

/*
	// mb cause of null ptr and not nodes
	void replaceNode( Node *n, Node *child ) {
		if (child)
			child->parent = n->parent;
		if (n->parent)
		{
			if (n == n->parent->left)
				n->parent->left = child;
			else
				n->parent->right = child;
		} else
			root_ = child;
	}
*/

		Node	*findVal( Node* root, Data data ) {
			if (root == NULL)
				return root;

			if (data < root->data)
				return findVal(root->left, data);
			if (data > root->data)
				return findVal(root->right, data);

			if (root->left == NULL || root->right == NULL)
				return root;

			Node*	tmp = minValueNode(root->right);
			root->data = tmp->data;
			return findVal(root->right, tmp->data);

			//return root;//tmp
		}

		void	replaceNode( Node* n, Node* child ) {
			child->parent = n->parent;
			if (n == n->parent->left)
				n->parent->left = child;
			else
				n->parent->right = child;
		}

		// works with prefound by value node
		void	deleteNode( Node *n ) {
			Node*	child = n->right ? n->right : n->left;

			replaceNode(n, child);
			// && child same cause of null ptrs not nodes
			if (n->color == BLACK && child) {
				if (child->color == RED)
					child->color = BLACK;
				else
					delete_case1(child);
			}
			//n->~Node();
			//alloc_.deallocate(n, 1);
			// or
			free(n);
		}

		void	delete_case1( Node* n ) {
			if (n->parent != NULL)
				delete_case2(n);
		}

		void	delete_case2( Node* n ) {
			Node*	s = sibling(n);

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

		void	delete_case3( Node* n ) {
			Node*	s = sibling(n);

			if (n->parent->color == BLACK && s->color == BLACK
					&& s->left->color == BLACK && s->right->color == BLACK) {
				s->color = RED;
				delete_case1(n->parent);
			} else
				delete_case4(n);
		}

		void	delete_case4( Node* n ) {
			Node*	s = sibling(n);

			if (n->parent->color == RED && s->color == BLACK
					&& s->left->color == BLACK && s->right->color == BLACK) {
				s->color = RED;
				n->parent->color = BLACK;
			} else
				delete_case5(n);
		
		}

		void	delete_case5( Node* n ) {
			Node*	s = sibling(n);

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

		void	delete_case6( Node* n ) {
			Node*	s = sibling(n);

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
		Node*	deleteBST( Node* root, Data data ) {
			if (root == NULL)
				return root;

			if (data < root->data)
				return deleteBST(root->left, data);
			if (data > root->data)
				return deleteBST(root->right, data);

			if (root->left == NULL || root->right == NULL)
				return root;

			Node*	tmp = minValueNode(root->right);
			root->data = tmp->data;
			return deleteBST(root->right, tmp->data);

			//return root;//tmp
		}
*/

		Node*	minValueNode( Node* n ) {
			Node*	ptr = n;
			
			while (ptr->left != NULL)
				ptr = ptr->left;
			return ptr;
		}

		Node*	maxValueNode( Node* n ) {
			Node*	ptr = n;
			
			while (ptr->right != NULL)
				ptr = ptr->right;
			return ptr;
		}

		/*
		void	balanceDeleteRBTree( Node* node ) {
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
