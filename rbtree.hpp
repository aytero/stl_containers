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
	};

	struct Node*	root_;
	Alloc			alloc_;

	Node *get_root( struct Node *n ) {
		while (n && n->parent)
			n = n->parent;
		return n;
	}

	public:
		//typedef struct Node	NodePtr;
	
		RBTree( const Alloc& alloc = Alloc()) : root_(NULL), alloc_(alloc) {}

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

		Node*	getRoot() { return root_; }

};

#endif
