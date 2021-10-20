#include <iostream>



//template <>
class	ft::RBTree {
	struct Node {
		void		*data;
		struct Node	*parent;
		struct Node	*left;
		struct Node	*right;
		bool		color;
	}
};

void	tree_print( struct Node *p ) {
	if (p == NULL)
		return ;
	tree_print(p->left);
	//printf("%d ", p->val);
	std::cout << p->val << " ";
	tree_print(p->right);
}


// * ??
//void	*tree_add( struct Node* p, Data x ) {
void	tree_add( struct Node* p, Data x ) {
	if (p == NULL) {
		p = malloc(sizeof(struct Node));
		p->val = x;
		p->left = p->right = NULL;
	} else if (x < p->val)
		p->left = tree_add(p->left, x);
	else if (x > p->val)
		p->right = tree_add(p->right, x);
	return p;
}
