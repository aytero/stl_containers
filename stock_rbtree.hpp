


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

// recolor opts
		void	insert_case1( nodePtr n ) {

			std::cout << n->data <<"\n";
			std::cout << "case1\n";
				
			//if (n->data == 8 && n->left) 
			//o	std::cout << n->left->color << "  color of 4\n";
			if (n->parent == NULL)
				n->is_black = true;
				//n->color = true;
			else
				insert_case2(n);
		}

		void	insert_case2( nodePtr n ) {

			std::cout << "case2\n";
			//if (n->data == 11) 
			//	std::cout << uncle(n)->color << "  color of 4\n";

			if (n->parent->is_black == true)
				return ;
			insert_case3(n);
		}

		void	insert_case3( nodePtr n ) {
			nodePtr u = uncle(n);
			nodePtr	g;
			std::cout << "case3\n";

			if ((u != NULL) && (u->is_black == false)) {
				n->parent->is_black = true;
				u->is_black = true;
				g = grandparent(n);
				g->is_black = false;
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

			n->parent->is_black = true;
			g->is_black = false;
			if ((n == n->parent->left) && (n->parent == g->left))
				rotateRight(g);
			else
				rotateLeft(g);
		}


		void	delete_case1( nodePtr n ) {
			std::cout << "del case1\n";
			if (n->parent != NULL)
				delete_case2(n);
		}

		void	delete_case2( nodePtr n ) {
			nodePtr	s = sibling(n);

			std::cout << "del case2\n";
			if (s->is_black == false) {
				n->parent->is_black = false;
				s->is_black = true;
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
			if (n->parent->is_black == true && s->is_black == true
					&& s->left->is_black == true && s->right->is_black == true) {
				s->is_black = false;
				delete_case1(n->parent);
			} else
				delete_case4(n);
		}

		void	delete_case4( nodePtr n ) {
			nodePtr	s = sibling(n);

			std::cout << "del case4\n";
			if (n->parent->is_black == false && s->is_black == true
					&& s->left->is_black == true && s->right->is_black == true) {
				s->is_black = false;
				n->parent->is_black = true;
			} else
				delete_case5(n);
		
		}

		void	delete_case5( nodePtr n ) {
			nodePtr	s = sibling(n);

			std::cout << "del case5\n";
			if (s->is_black == true) {
				if (n->parent->left && s->right->is_black == true && s->left->is_black == false) {
					s->is_black = false;
					s->left->is_black = true;
					rotateRight(s);
				} else if (n == n->parent->right && s->left->is_black == true && s->right->is_black == false) {
					s->is_black = false;
						s->right->is_black = true;
					rotateLeft(s);
				}
			}
			delete_case6(n);
		}

		void	delete_case6( nodePtr n ) {
			nodePtr	s = sibling(n);

			std::cout << "del case6\n";
			s->is_black = n->parent->is_black;
			n->parent->is_black = true;

			if (n == n->parent->left) {
				s->right->is_black = true;
				rotateLeft(n->parent);
			} else {
				s->left->is_black = true;
				rotateRight(n->parent);
			}
		}


		/*
		nodePtr	sibling( nodePtr n ) {
			if (n == n->parent->left)
				return n->parent->right;
			return n->parent->left;
		}*/

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
			//if (n->color == true) {
			if (n->is_black == true && child) {
					std::cout << "EEEE\n";
				if (child->is_black == false) {
					child->is_black = true;
				} else {
					rb_delete_fixup(child);
				}
			}
			//n->~Node();
			//alloc_.deallocate(n, 1);
			// or
			free(n);
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

			nodePtr	tmp = tree_min(root->right);
			root->data = tmp->data;
			return deleteBST(root->right, tmp->data);

			//return root;//tmp
		}
*/

		//getPredecessor

		/*
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
		}*/
		/*
		nodePtr get_root( nodePtr n ) {
			while (n && n->parent)
				n = n->parent;
			return n;
		}*/
			//erase
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


			
			_insert_into_tree(new_node, _root);


			if (position == begin()){
				if (position != end() && _compare(value, *position))
					_insert_into_tree(new_node, tree_min(_root));
				else
					_insert_into_tree(new_node, _root);
			}
			else if (position == end()){
				if (position != begin() && _compare(*(--position), value))
					_insert_into_tree(new_node, _header->parent);
				else
					_insert_into_tree(new_node, _root);
			}
			else
				_insert_into_tree(new_node, _root);


			// mccont
		rbnode *c = _root;
		if (hint)
		{
			rbnode *hnxt = hint->next();
			if(_comp(hint->key,key) && (!hnxt || _comp(key,hnxt->key)))
				c = hint->right ? hnxt : hint;
		}
		while (c)
			if (_comp(key, c->key))
			{
				if (!c->left)
					break;
				c = c->left;
			}
			else if (_comp(c->key, key))
			{
				if (!c->right)
					break;
				c = c->right;
			}
			else
				return make_pair(c, false);

		rbnode *n = _node_alloc.allocate(1);
		new (n) rbnode(key);

		n->parent = c;
		if (c && _comp(key, c->key))
			c->left = n;
		else if (c && _comp(c->key, key))
			c->right = n;

		insert_case1(n);
		_root = get_root(n);
		return make_pair(n, true);
