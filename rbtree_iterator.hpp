#ifndef RBTREE_ITERATOR_HPP
# define RBTREE_ITERATOR_HPP

# include "utility.hpp"
# include "type_traits.hpp"
# include "iterator_traits.hpp"

template < class Data >
	struct Node {
		public:
	
		Data	*data;
		Node	*parent;
		Node	*left;
		Node	*right;
		bool	is_black;
		bool	is_nil;

		explicit Node( Data *d = 0 ) : data(d), parent(0), left(0), right(0),
									is_black(false), is_nil(false) {}

		Node( const Node& ref ) { *this = ref; }

		virtual ~Node() {}

		Node& operator=( const Node& other ) {
			if (this == &other)
				return *this;
			data = other.data;
			parent = other.parent;
			left = other.left;
			right = other.right;
			is_black = other.is_black;
			is_nil = other.is_nil;
			return *this;
		}
	};

template <typename T>
class TreeIterator {

	public:
		typedef std::bidirectional_iterator_tag						iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type		value_type;
		typedef typename ft::iterator_traits<T*>::reference			reference;
		typedef typename ft::iterator_traits<T*>::pointer			pointer;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
		typedef Node<typename ft::remove_const<value_type>::type >* node_ptr;//node_pointer

	private:
		node_ptr	ptr_;

		node_ptr tree_min( node_ptr n ) const {
			while(n->left != NULL && !n->left->is_nil)
				n = n->left;
			return n;
		}

		node_ptr tree_max( node_ptr n ) const {
			while (!n->right->is_nil)
				n = n->right;
			return n;
		}

	public:
	
		TreeIterator() {}

		TreeIterator( void *ptr ) : ptr_(static_cast<node_ptr>(ptr)) {}

		TreeIterator( const TreeIterator<typename ft::remove_const<value_type>::type> &ref ) {
		// : ptr_(ref.ptr_) {
			*this = ref;
		}

		~TreeIterator() {}

		TreeIterator& operator=( const TreeIterator<typename ft::remove_const<value_type>::type> &other ) {
			ptr_ = other.getNode();
			return *this;
		}

		reference operator*() const { return *(ptr_->data); }
		pointer operator->() const { return ptr_->data; }

		TreeIterator& operator++() {
			if (ptr_->right && !ptr_->right->is_nil) {
				ptr_ = tree_min(ptr_->right);
			} else {
				node_ptr tmp = ptr_->parent;
				while (tmp != NULL && ptr_ == tmp->right) {
					ptr_ = tmp;
					tmp = tmp->parent;
				}
				ptr_ = tmp;
			}
			return *this;
		}

		TreeIterator operator++( int ) {
			TreeIterator<value_type> tmp = *this;

			if (!ptr_->right->is_nil) {
				ptr_ = tree_min(ptr_->right);
			} else {
				node_ptr p = ptr_->parent;
				while (p != NULL && ptr_ == p->right) {
					ptr_ = p;
					p = p->parent;
				}
				ptr_ = p;
			}

			return tmp;
		}

		TreeIterator& operator--() {
			if (ptr_->left && !ptr_->left->is_nil) {
				ptr_ = tree_max(ptr_->left);
			} else {
				node_ptr p = ptr_->parent;
				while (p != NULL && ptr_ == p->left) {
					ptr_ = p;
					p = p->parent;
				}
				ptr_ = p;
			}
			return *this;
		}

		TreeIterator operator--( int ) {
			TreeIterator<value_type> tmp = *this;

			if (ptr_->left && !ptr_->left->is_nil) {
				ptr_ = tree_max(ptr_->left);
			} else {
				node_ptr p = ptr_->parent;
				while (p != NULL && ptr_ == p->left) {
					ptr_ = p;
					p = p->parent;
				}
				ptr_ = p;
			}
			return tmp;
		}

		node_ptr getNode() const {
			return ptr_;
		}

};

template <class A, class B>
	bool operator==( const TreeIterator<A> &lhs, const TreeIterator<B> &rhs ) {
		return lhs.getNode() == rhs.getNode();
	}

template <class A, class B>
	bool operator!=( const TreeIterator<A> &lhs, const TreeIterator<B> &rhs ) {
		return lhs.getNode() != rhs.getNode();
	}

#endif
