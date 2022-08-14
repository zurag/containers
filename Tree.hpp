#ifndef TREE_HPP
# define TREE_HPP

#include <memory>
#include <utility>
#include <stack>
#include <functional>
#include <iterator>
#include <iostream>
#include "type_traits.hpp"
#include "iterator.hpp"
#include "utility.hpp"
#include <vector>
#include <stack>

namespace ft {

template <class U>
struct Node {

	Node *left;
	Node *right;
	Node *p;
	U value_;
	bool color; // true -> Red, false -> Black
	bool is_nill;

	Node(bool nill):left(nullptr), right(nullptr), p(nullptr), color(false), is_nill(nill){}

	Node(const U &value, bool new_color = false, bool nill = false):left(nullptr),
		right(nullptr), p(nullptr), value_(value), color(new_color), is_nill(nill){}

	Node(const Node &node):left(node.left), right(node.right),
		p(node.p), value_(node.value_), color(node.color), is_nill(node.is_nill){}
	
	~Node() {p = nullptr; left = nullptr; right = nullptr;}
};

template <typename T>
struct cmp_val {typedef T key_type;};

template <class Key, class Value>
struct cmp_val<pair<Key, Value> > {typedef Key key_type;};


template < class Value, class Compare = std::less<Value>,
			class Alloc = std::allocator<Value> >
class Tree {

public:

	typedef Value															value_type;
	typedef typename cmp_val<value_type>::key_type							key_type;
	typedef typename Alloc::template rebind<Node<Value> >::other            node_allocator;
	typedef Compare															key_compare;
	typedef node_allocator													allocator_type;
	typedef typename allocator_type::reference								reference;
	typedef typename allocator_type::const_reference						const_reference;
	typedef typename allocator_type::pointer								pointer;
	typedef typename allocator_type::const_pointer							const_pointer;
	typedef typename allocator_type::size_type								size_type;
	typedef typename allocator_type::difference_type						difference_type;
	typedef Node<value_type>												TreeNode;

private:


template <class T>
class TreeIterator :public std::iterator<std::bidirectional_iterator_tag, T>
{
public:
	friend class Tree;
	typedef std::bidirectional_iterator_tag iterator_category;


	// typedef ptrdiff_t difference_type;
	// typedef typename delConst<T>::type		value_type;
	// typedef typename delConst<T&>::type		reference;
	// typedef typename delConst<T*>::type		pointer;


	typedef typename ft::iterator_traits<T*>::value_type 		value_type;
	typedef typename ft::iterator_traits<T*>::reference 		reference;
	typedef typename ft::iterator_traits<T*>::pointer			pointer;
	typedef typename ft::iterator_traits<T*>::difference_type	difference_type;




	typedef pointer iterator_type;
	typedef Node<typename delConst<T>::type >					TreeNode;
	typedef TreeNode *											TreeNodePtr;



	TreeNode *getNode() const {return _node;}
	TreeNode *getRoot() const {return _root;}

	TreeIterator():_node(nullptr), _root(nullptr) { }


	// template <typename Iter>
	// TreeIterator(const TreeIterator<Iter>& x,
	// 	typename ft::enable_if<std::is_convertible<Iter, value_type>::value>::type* = 0): _node(x._node), _root(x._root) {}

	TreeIterator(const TreeIterator<typename delConst<T>::type>& x): _node(x._node), _root(x._root)  {}

	TreeIterator(const TreeNodePtr x, const TreeNodePtr root):_node(x), _root(root) {}
	
	reference operator*() const {return _node->value_;}

	pointer operator->() const {return &(_node->value_);}
	
	TreeIterator& operator=(const TreeIterator<typename delConst<T>::type>& x) {
		if (this == &x)
			return *this;
		_node = x.getNode();
		_root = x.getRoot();
		return *this;
	}

	TreeIterator& operator++() {
		TreeNode *tmp = _node->p;

		if (_node->is_nill) {
			return *this;
		}
		if (!_node->right->is_nill) {
			_node = _node->right;
			while (!_node->left->is_nill){
				_node = _node->left;
			}
		}
		else {
			tmp = _node->p;
			while (!tmp->is_nill && tmp->right == _node) {
				_node = tmp;
				tmp = tmp->p;
			}
			_node = tmp;
		}
		return *this;
	}

	TreeIterator operator++(int) {
		TreeIterator copy(*this);
		this->operator++();
		return copy;
	}
	
	TreeIterator& operator--() {	
		TreeNode *tmp = nullptr;
		if (_node->is_nill) {
			_node = _root;
			while(!_node->right->is_nill)
				_node = _node->right;
			return *this;
		}
		else if(!_node->left->is_nill) {
			_node = _node->left;
			while (!_node->right->is_nill)
				_node = _node->right;
		}
		else {
			tmp = _node->p;
			while (!tmp->is_nill && tmp->left == _node) {
				_node = tmp;
				tmp = tmp->p;
			}
			_node = tmp;
		}
		return *this;
	}

	TreeIterator operator--(int) {
		TreeIterator copy(*this);
		this->operator--();
		return copy;
	}

	template <class Iter1>
	bool operator!= (const TreeIterator<Iter1>& rhs) const{
		return this->operator->() != rhs.operator->();
	}

	template <class Iter1>
	bool operator> (const TreeIterator<Iter1>& rhs) const{
		return this->operator->() > rhs.operator->();
	}

	template <class Iter1>
	bool operator>= (const TreeIterator<Iter1>& rhs) const{
		return this->operator->() >= rhs.operator->();
	}

	template <class Iter1>
	bool operator< (const TreeIterator<Iter1>& rhs) const{
		return this->operator->() < rhs.operator->();
	}

	template <class Iter1>
	bool operator<= (const TreeIterator<Iter1>& rhs) const{
		return this->operator->() <= rhs.operator->();
	}

	template <class Iter1>
	bool operator== (const TreeIterator<Iter1>& rhs) const{
		return this->operator->() == rhs.operator->();
	}

	private:
		TreeNode *_node;
		TreeNode *_root;
};

public:

	typedef TreeIterator<value_type>			iterator;
	typedef TreeIterator<const value_type>		const_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;

	Tree (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()):_root(nullptr),_nill(nullptr),
				_size(0), _alloc(alloc), _comp(comp) {
		_nill = _alloc.allocate(1);
		_alloc.construct(_nill, true);
		_root = _nill;
		_root->p = _nill;
		_root->left = _nill;
		_root->right = _nill;
	}

	template <class InputIterator>
 	Tree (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()): _root(nullptr),_nill(nullptr),
				_size(0), _alloc(alloc), _comp(comp){
		_nill = _alloc.allocate(1);
		_alloc.construct(_nill, true);
		_root = _nill;
		_root->p = _nill;
		_root->left = _nill;
		_root->right = _nill;
		insert(first, last);
	}

	Tree (const Tree& x): _root(nullptr),_nill(nullptr),
				_size(x.size()), _alloc(x.get_allocator()), _comp(x.key_comp()){
		_nill = _alloc.allocate(1);
		_alloc.construct(_nill, true);
		_root = _nill;
		_root->p = _nill;
		_root->left = _nill;
		_root->right = _nill;
		this->operator=(x);
	}

	Tree& operator= (const Tree& x) {
		if (&x == this) {
			return *this;
		}
		clear();
		_alloc = x.get_allocator();
		_comp = x.key_comp();
		if (x.size() > 0) {
			TreeNode *tmp = x._root;
			TreeNode *root = _alloc.allocate(1);
			_alloc.construct(root, *tmp);
			_root = root;
			_root->p = _nill;
			std::stack<TreeNode *> src;
			std::stack<TreeNode *> dst;
			src.push(tmp);
			dst.push(root);
			while (!src.empty()) {
				tmp = src.top();
				root = dst.top();
				src.pop();
				dst.pop();
				if (!tmp->left->is_nill) {
					root->left = _alloc.allocate(1);
					_alloc.construct(root->left, *(tmp->left));
					root->left->p = root;
					root->left->left = _nill;
					root->left->right = _nill;
					dst.push(root->left);
					src.push(tmp->left);
				}
				else
					root->left = _nill;
				if (!tmp->right->is_nill) {
					root->right = _alloc.allocate(1);
					_alloc.construct(root->right, *(tmp->right));
					root->right->p = root;
					root->right->left = _nill;
					root->right->right = _nill;
					dst.push(root->right);
					src.push(tmp->right);
				}
				else
					root->right = _nill;
			}
		}
		else {
			_root = _nill;
		}
		_size = x.size();
		return *this;
	}

	~Tree() {
		if (_size > 0) {
			clear();
		}
		if (_nill){
			_alloc.destroy(_nill);
			_alloc.deallocate(_nill, 1);
			_nill = nullptr;
			_root = nullptr;
		}
	}

	iterator begin() {
		TreeNode *tmp = _root;

		if (_size == 0)
			return end();
		while (!tmp->left->is_nill) {
			tmp = tmp->left;
		}
		return iterator(tmp, _root);
	}

	const_iterator begin() const {
		TreeNode *tmp = _root;

		if (_size == 0)
			return end();
		while (!tmp->left->is_nill) {
			tmp = tmp->left;
		}
		return const_iterator(tmp, _root);
	}

	iterator end() {
		return iterator(_nill, _root);
	}
	
	const_iterator end() const {
		return const_iterator(_nill, _root);
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

	bool empty() const {
		return _size == 0;
	}

	size_type size() const {
		return _size;
	}

	size_type max_size() const {
		return _alloc.max_size();
	}

	// mapped_type& operator[] (const key_type& k) {

	// }

	pair<iterator,bool> insert (const value_type& val) {
		TreeNode	*new_node;
		TreeNode *y = _nill;
		TreeNode *x = _root;
		while (!x->is_nill) {
			y = x;
			if (_comp(val, x->value_)) {
				x = x->left;
			}
			else if (val.first == x->value_.first) {
				return (pair<iterator, bool>(iterator(x, _root), false));
			}
			else
				x = x->right;
		}
		new_node = _alloc.allocate(1);
		_alloc.construct(new_node, val, true, false);
		new_node->p = y;
		new_node->left = _nill;
		new_node->right = _nill;
		if (y->is_nill) {
			_root = new_node;
		}
		else if (_comp(val, y->value_))
			y->left = new_node;
		else
			y->right = new_node;
		insert_fixup(new_node);
		++_size;
		return (pair<iterator, bool>(iterator(new_node, _root), true));
	}

	iterator insert (iterator position, const value_type& val) {
		iterator end = position;
		++end;
		if (_comp(*position, val) && _comp(val, *end)) {
			TreeNode *x = position._node;
			TreeNode *tmp = x->right;
			TreeNode *new_node;

			new_node = _alloc.allocate(1);
			_alloc.construct(new_node, val, true, false);
			x->right = new_node;
			new_node->right = tmp;
			new_node->left = _nill;
			new_node->p = x;
			tmp->p = new_node;
			insert_fixup(new_node);
			++_size;
			return iterator(new_node, _root);
		}
		return insert(val).first;
	}

	template <class InputIterator>
	void insert (InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
		for ( ;first != last; ++first) {
			this->insert(*first);
		}
	}

	void erase (iterator position) {
		TreeNode *node = position._node;
		TreeNode *x;
		TreeNode *y = node;
		bool color = node->color;

		if (node->left->is_nill) {
			x = node->right;
			transplant(node, node->right);
		}
		else if (node->right->is_nill) {
			x = node->left;
			transplant(node, node->left);
		}
		else {
			y = node->right;
			while (!y->left->is_nill)
				y = y->left;
			color = y->color;
			x = y->right;
			if (y->p == node)
				x->p = y;
			else {
				transplant(y, y->right);
				y->right = node->right;
				y->right->p = y;
			}
			transplant(node, y);
			y->left = node->left;
			y->left->p = y;
			y->color = node->color;
		}
		_alloc.destroy(node);
		_alloc.deallocate(node, 1);
		node = _nill;
		if (!color)
			delete_fixup(x);
		--_size;
	}

	size_type erase (const key_type& k) {
		iterator it = find(k);

		if (it != end())
			erase(it);
		return it != end();
	}

	void erase (iterator first, iterator last) {
		for (; first != last;) {
			erase(first++);
		}
	}

	void swap (Tree& x) {
		std::swap(x._root, _root);
		std::swap(x._nill, _nill);
		std::swap(x._size, _size);
		std::swap(x._alloc, _alloc);
		std::swap(x._comp, _comp);
	}

	void clear() {
		clearNode(_root);
		_root = _nill;
		_size = 0;
	}

	key_compare key_comp() const {
		return _comp;
	}

	iterator find (const key_type& k) {
		TreeNode *tmp = _root;

		while (!tmp->is_nill) {
			if (tmp->value_.first == k) {
				return iterator(tmp, _root);
			}
			else if (_comp(tmp->value_, k))
				tmp = tmp->right;
			else
				tmp = tmp->left;
		}
		return end();
	}
	
	const_iterator find (const key_type& k) const {
		TreeNode *tmp = _root;
		while (!tmp->is_nill) {
			if (tmp->value_.first == k) {
				return const_iterator(tmp, _root);
			}
			else if (_comp(tmp->value_, k))
				tmp = tmp->right;
			else
				tmp = tmp->left;
		}
		return end();
	}


	size_type count (const key_type& k) const {
		return find(k) != end();
	}

	iterator lower_bound (const key_type& k) {
		TreeNode *tmp = _root;
		
		while (!tmp->is_nill) {
			if (tmp->value_.first == k) {
				return iterator(tmp, _root);
			}
			else if (_comp(tmp->value_, k))
				tmp = tmp->right;
			else {
				if (!tmp->left->is_nill)
					tmp = tmp->left;
				else					
					return iterator(tmp, _root);
			}
		}
		return iterator(tmp, _root);
	}
	
	const_iterator lower_bound (const key_type& k) const {
		TreeNode *tmp = _root;
		
		while (!tmp->is_nill) {
			if (tmp->value_.first == k) {
				return const_iterator(tmp, _root);
			}
			else if (_comp(tmp->value_, k))
				tmp = tmp->right;
			else {
				if (!tmp->left->is_nill)
					tmp = tmp->left;
				else					
					return const_iterator(tmp, _root);
			}
		}
		return const_iterator(tmp, _root);
	}

	iterator upper_bound (const key_type& k) {
		TreeNode *tmp = _root;
		while (!tmp->is_nill) {
			if (_comp(tmp->value_, k)) {
				tmp = tmp->right;
			}
			else if (tmp->value_.first == k) {
				return ++iterator(tmp, _root);
			}
			else {
				while(!tmp->left->is_nill && _comp(k, tmp->left->value_))
					tmp = tmp->left;
				return iterator(tmp, _root);
			}
		}
		return end();
	}
	
	const_iterator upper_bound (const key_type& k) const {
		TreeNode *tmp = _root;
		while (!tmp->is_nill) {
			if (_comp(tmp->value_, k)) {
				tmp = tmp->right;
			}
			else if (tmp->value_.first == k) {
				return ++const_iterator(tmp, _root);
			}
			else {
				while(!tmp->left->is_nill && _comp(k, tmp->left->value_))
					tmp = tmp->left;
				return const_iterator(tmp, _root);
			}
		}
		return end();
	}

	allocator_type get_allocator() const {
			return _alloc;
	}

private:

/*_____________________________________________________________________________*/

	void delete_fixup(TreeNode *x) {
		TreeNode *tmp;
		while (x != _root && !x->p->is_nill && !x->color) {
			if (x == x->p->left) {
				tmp = x->p->right;
				if (tmp->color) {
					tmp->color = false;
					x->p->color = true;
					left_rotate(x->p);
					tmp = x->p->right;
				}
				if (!tmp->left->color && !tmp->right->color) {
					tmp->color = true;
					x = x->p;
				}
				else { 
					if (!tmp->right->color) {
						tmp->left->color = false;
						tmp->color = true;
						right_rotate(tmp);
						tmp = x->p->right;
					}
					tmp->color = x->p->color;
					x->p->color = false;
					tmp->right->color = false;
					left_rotate(x->p);
					x = _root;
				}
			}
			else {
				tmp = x->p->left;
				if (tmp->color) {
					tmp->color = false;
					x->p->color = true;
					right_rotate(x->p);
					tmp = x->p->left;
				}
				if (!tmp->right->color && !tmp->left->color) {
					tmp->color = true;
					x = x->p;
				}
				else {
					if (!tmp->left->color) {
						tmp->right->color = false;
						tmp->color = true;
						left_rotate(tmp);
						tmp = x->p->left;
					}
					tmp->color = x->p->color;
					x->p->color = false;
					tmp->left->color = false;
					right_rotate(x->p);
					x = _root;
				}
			}
		}
	}

	void transplant(TreeNode *node1, TreeNode *node2) {
		if (node1 == _root) {
			_root = node2;
		}
		else if (node1 == node1->p->left) {
			node1->p->left = node2;
		}
		else
			node1->p->right = node2;
		node2->p = node1->p;
	}

	void insert_fixup(TreeNode *node) {
		TreeNode *y = nullptr;
		if (node == _root) {
			node->color = false;
			return ;
		}
		while (node != _root && node->p->color == true) {
			if (node->p == node->p->p->left) {
				y = node->p->p->right;
				if (y->color == true) {
					node->p->color = false;
					y->color = false;
					node->p->p->color = true;
				}
				else {
					if (node == node->p->right) {
						node = node->p;
						left_rotate(node);
					}
					node->p->color = false;
					node->p->p->color = true;
					right_rotate(node->p->p);
				}	
			}
			else {
				y = node->p->p->left;
				if (y->color == true) {
					node->p->color = false;
					y->color = false;
					node->p->p->color = true;
					node = node->p->p;
				}
				else {
					if (node == node->p->left) {
						node = node->p;
						right_rotate(node);

					}
					node->p->color = false;
					node->p->p->color = true;
					left_rotate(node->p->p);
				}		
			}
		}
		_root->color = false;
	}

	void left_rotate(TreeNode *x) {
		if (x->is_nill || x->right->is_nill)
			return ;
		TreeNode *y = x->right;
		x->right = y->left;
		if (!y->left->is_nill) {
			y->left->p = x;
		}
		y->p = x->p;
		if (x->p->is_nill) {
			_root = y;
		}
		else if (x == x->p->left)
			x->p->left = y;
		else
			x->p->right = y;
		y->left = x;
		x->p = y;
	}

	void right_rotate(TreeNode *y) {
		if (y->is_nill || y->left->is_nill)
			return ;
		TreeNode *x = y->left;
		y->left = x->right;
		if (!x->right->is_nill)
			x->right->p = y;
		x->p = y->p;	
		if (y->p->is_nill)
			_root = x;
		else if (y == y->p->left)
			y->p->left = x;
		else
			y->p->right = x;
		y->p = x;
		x->right = y;
	}

	void clearNode(TreeNode *node) {
		std::vector<TreeNode *> st;
	
		st.reserve(_size);
		if (!node->is_nill)
			st.push_back(node);
		while (!st.empty()) {
			node = st.back();
			st.pop_back();
			if (!node->left->is_nill)
				st.push_back(node->left);
			if (!node->right->is_nill)
				st.push_back(node->right);
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
		}
	}

	TreeNode		*_root;
	TreeNode		*_nill;
	size_type		_size;
	allocator_type	_alloc;
	key_compare		_comp;
};

}


#endif