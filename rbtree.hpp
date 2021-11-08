#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <iostream>


namespace ft
{
	template < class Data, class Alloc >
		class RBTree;
}


// < ..., class Compare >
template < class Data, class Alloc = std::allocator<Data> >
class	ft::RBTree {
	struct Node {
		//int	data;
		Data		data;
		struct Node	*parent;
		struct Node	*left;
		struct Node	*right;
		bool		color;
		//enum color_t color;
	};

	struct Node*	root_;
	struct Node*	tnull_;
	Alloc			alloc_;

	Node *get_root( struct Node *n ) {
		while (n && n->parent)
			n = n->parent;
		return n;
	}

	void	printHelper( struct Node *root, std::string indent, bool last ) {
		//if (root_ != tnull_) {
		if (root_) {
			std::cout << indent;
			if (last) {
				std::cout << "R--- ";
				indent += "\t ";
			} else {
				std::cout << "L--- ";
				indent += "|\t";
			}

			std::string sColor = root->color ? "RED" : "BLACK";
			std::cout << root->data << "(" << sColor << ")\n";
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}

	}

	void printHelper1(const struct Node *root, int lvl)
	{
		if (!root)
			return ;
		printHelper1(root->right, lvl + 1);
		for (int i = 0; i < lvl * 4; i++)
			std::cout << " ";
		std::cout << root->data << (root->color == RED ? "r" : "b") << std::endl;
		printHelper1(root->left, lvl + 1);
	}

	public:
		enum color_t { BLACK, RED };
		//typedef struct Node	NodePtr;
	
		RBTree( const Alloc& alloc = Alloc()) : root_(NULL), alloc_(alloc) {
			/*
			tnull_ = new Node;
			tnull_->color = 0;
			//tnull_->data = 0;
			tnull_->left = NULL;
			tnull_->right = NULL;
			tnull_->parent = NULL;
			root_ = tnull_;
			*/
		}

		~RBTree() { free_node(root_); }
	
		void free_node( struct Node *n )
		{
			if (!n)
				return ;
			free_node(n->left);
			free_node(n->right);
			n->~Node();
			//alloc_.deallocate(n, 1);
			delete n;
		}
		//void	tree_print( struct Node *p );
		struct Node*	tree_insert( struct Node* p, Data x ) {

			Node*	tmp = root_;
			
			if (p == NULL) {
				//p = (struct Node*)malloc(sizeof(struct Node));
				p = new Node;
				//struct Node *n = alloc_.allocate(1);
				//new (n) Node(Data);
		//rbnode *n = _node_alloc.allocate(1);
		//new (n) rbnode(key);
				p->data = x;
				p->left = p->right = NULL;
				p->parent = tmp;
				p->color = 1;
				//head_ = p;
			} else if (x < p->data)
				p->left = tree_insert(p->left, x);
			else if (x > p->data)
				p->right = tree_insert(p->right, x);
			
			root_ = get_root(p);
			return p;
		}

		void	tree_print( struct Node *p ) {
			if (p == NULL)
				return ;
			tree_print(p->left);
			//printf("%d ", p->data);
			std::cout << p->data << " ";
			tree_print(p->right);
		}

		void	treePrint() {
			if (root_)
				printHelper1(root_, 0);
				//printHelper(root_, "", true);
		}

		Node*	getRoot() { return root_; }
		//const Node*	getRoot() const { return root_; }

		// constructor, allocator
		// from ru wiki
		/*
		void rotateLeft( struct Node* n ) {
			struct Node *pivot = NULL;

			pivot->parent = n->parent;
			if (n->parent != NULL) {
				if (n->parent->left == n)
					n->parent->left = pivot;
				else
					n->parent->right = pivot;
			}

			n->right = pivot->left;
			if (pivot->left != NULL)
				pivot->left->parent = n;

			n->parent = pivot;
			pivot->left = n;
		}
		*/
		//rotateRight() {}
		//colorSwap() {}// or recolor
		/*
		//insert() {}
		// balance after insertion
		insertCase1() // T is empty
		insertCase2() // P is black
		*/
		//delete() {}// or erase
};

#endif
