#ifndef __MAP_HPP__
# define __MAP_HPP__

#include <utility>
#include <functional>
#include <iterator>
#include <iostream>
// #include "iterator.hpp"
#include "utility.hpp"


namespace ft {

template <class Key, class T>
struct Node {

	Node *left;
	Node *right;
	Node *p;
	pair<const Key,T> value_;
	bool color; // true -> Red, false -> Black

	Node(pair<const Key,T> value, bool color = false):value_(value)
	{
		left = nullptr;
		right = nullptr;
		p = nullptr;
		this->color = color;
	}

	Node(Node &node):value_(node.value_)
	{
		left = node.left;
		right = node.right;
		p = node.p;
		color = node.color;
	}
};


template < class Key, class T, class Compare = std::less<Key>,
			class Alloc = std::allocator<Node<Key, T> > >
class map
{
	class Iterator :public std::iterator<std::bidirectional_iterator_tag, Key, T>
		{			

		public:
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef ptrdiff_t difference_type;
			// typedef T value_type;
			// typedef T* pointer;
			// typedef T& reference;
			typedef  Key										key_type;
			typedef  T											mapped_type;
			typedef pair<const key_type, mapped_type>			value_type;
			// typedef Compare										key_compare;
			// typedef Alloc										allocator_type;
			typedef Node<Key, T> TreeNode;

			Iterator():_node(NULL) { }
			
			Iterator(const Iterator &x):_node(x._node) { }

			Iterator(TreeNode *x):_node(x) {}
			
			value_type &operator*(){return _node->value_;}
		
			value_type *operator->(){return &(_node->value_);}
			
			Iterator& operator= (const Iterator &x) {
				_node = x._node;
				return *this;
			}
			
			friend bool operator==(const Iterator &x, const Iterator &y) {return x._node == y._node;}

			friend bool operator!=(const Iterator &x, const Iterator &y) {return x._node != y._node;}
			
			Iterator& operator++() {
				if (!_node) {
					return *this;
				}
				TreeNode *tmp = nullptr;
				if (_node->right) {
					tmp = _node->right;
					if (tmp->left && tmp->left->value_.first > _node->value_.first) { // Заменить на CMP
						while (tmp->left != nullptr)
							tmp = tmp->left;
							_node = tmp;
						}
					else
						_node = _node->right;
				}
				else {
					tmp = _node->p;
					while (tmp && tmp->value_.first < _node->value_.first) // Заменить на CMP
						tmp = tmp->p;
					_node = tmp;
				}				
				return *this;
			}

			Iterator operator++(int) {
				Iterator copy(*this);
				if (!_node) {
					return copy;
				}
				TreeNode *tmp = nullptr;
				if (_node->right) {
					tmp = _node->right;
					if (tmp->left && tmp->left->value_.first > _node->value_.first) { // Заменить на CMP
						while (tmp->left != nullptr)
							tmp = tmp->left;
							_node = tmp;
						}
					else
						_node = _node->right;
				}
				else {
					tmp = _node->p;
					while (tmp && tmp->value_.first < _node->value_.first) // Заменить на CMP
						tmp = tmp->p;
					_node = tmp;
				}
				return copy;
			}
			
			Iterator& operator--() {
				if (!_node) {
					return *this;
				}
				TreeNode *tmp = nullptr;
				if(_node->left) {
					tmp = _node->left;
					while (tmp != nullptr)
						tmp = tmp->right;
					_node = tmp;
				}
				else {
					tmp = _node->p;
					while (tmp && tmp->value_.first > _node->value_.first) // Заменить на CMP
						tmp = tmp->p;
					_node = tmp;
				}
				return *this;
			}

			Iterator operator--(int) {
				Iterator copy(*this);
				if (!_node) {
					return copy;
				}
				TreeNode *tmp = nullptr;
				if(_node->left ) {
					tmp = _node->left;
					while (tmp != nullptr)
						tmp = tmp->right;
					_node = tmp;
				}
				else {
					tmp = _node->p;
					while (tmp && tmp->value_.first > _node->value_.first) // Заменить на CMP
						tmp = tmp->p;
					_node = tmp;
				}
				return copy;
			}
			private:
				TreeNode *_node;
		};



public:

	typedef  Key										key_type;
	typedef  T											mapped_type;
	typedef pair<const key_type, mapped_type>			value_type;
	typedef Compare										key_compare;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;

	typedef Node<Key, T>	TreeNode;
	typedef TreeNode		*TreeNodeptr;
	typedef Iterator		iterator;
	typedef const Iterator const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator; // Заменить на ft
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator; // Заменить на ft


	map (const key_compare& comp = key_compare(),
            	const allocator_type& alloc = allocator_type()):_alloc(alloc),
				_comp(comp), _root(nullptr), _size(0) {
	}

	// template <class InputIterator>
 	// map (InputIterator first, InputIterator last,
    //    const key_compare& comp = key_compare(),
    //    const allocator_type& alloc = allocator_type()) {

	// }

	

	// map (const map& x) {

	// }

	~map() {

	}

	// map& operator= (const map& x);

	iterator begin() {
		TreeNode *tmp = _root;

		if (_size == 0)
			return end();
		while (tmp->left != nullptr) {
			tmp = tmp->left;
		}
		return iterator(tmp);
	}
	
	// const_iterator begin() const;

	iterator end() {
		return iterator(nullptr);
	}
	
	// const_iterator end() const;

	// reverse_iterator rbegin();
	
	// const_reverse_iterator rbegin() const;

	// reverse_iterator rend();
	
	// const_reverse_iterator rend() const;

	// bool empty() const {
	// 	return _size == 0;
	// }

	// size_type size() const {
	// 	return _size;
	// }

	// size_type max_size() const {
	// 	return _alloc.max_size();
	// }

	// mapped_type& operator[] (const key_type& k) {
	// 	iterator it = find(k);
	// 	if (it != end())
	// 		return it->second;
	// 	else
	// 		return (*((this->insert(make_pair(k,mapped_type()))).first)).second;
	// }


	pair<iterator,bool> insert (const value_type& val) {
		// bool		ret = false;
		TreeNode	*new_node = _alloc.allocate(1);
		_alloc.construct(new_node, val, true);

		TreeNode *y = NULL;
		TreeNode *x = _root;
		iterator	it(new_node);

		while (x) {
			y = x;
			if (new_node->value_.first < x->value_.first) {
				x = x->left;
			}
			else if (new_node->value_.first == x->value_.first) {
				_alloc.destroy(new_node);
				_alloc.deallocate(new_node, 1);
				return (pair<iterator, bool>(iterator(x), false));
			}
			else
				x = x->right;
		}
		new_node->p = y;
		if (!y)
			_root = new_node;
		else if (new_node->value_.first < y->value_.first)
			y->left = new_node;
		else
			y->right = new_node;
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->color = true;
		insert_fixup(new_node); // функция восстанавливающая свойства дерева
		// std::cout << "head === " << _root->value_.first << '\n';
		++_size;
		return (pair<iterator, bool>(it, true));
	}

	// iterator insert (iterator position, const value_type& val);

	// template <class InputIterator>
	// void insert (InputIterator first, InputIterator last);

	// void erase (iterator position);

	// size_type erase (const key_type& k);

	// void erase (iterator first, iterator last);

	// void swap (map& x) {
	// 	map<Key, T> tmp(x);
	// 	x = *this;
	// 	*this = tmp;
	// }

	// void clear();

	// key_compare key_comp() const {
	// 	return _comp;
	// }

	// value_compare value_comp() const;

	// iterator find (const key_type& k);
	
	// const_iterator find (const key_type& k) const;

	// size_type count (const key_type& k) const;

	// iterator lower_bound (const key_type& k);
	
	// const_iterator lower_bound (const key_type& k) const;

	// iterator upper_bound (const key_type& k);
	
	// const_iterator upper_bound (const key_type& k) const;

	// pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
	
	// pair<iterator,iterator> equal_range (const key_type& k);

	// allocator_type get_allocator() const {
	// 		return _alloc;
	// }

private:

	void insert_fixup(TreeNode *node) {
		TreeNode *y = nullptr;
		if (node == _root) {
			node->color = false;
			// _root->color = false;
			return ;
		}
		if (node->p == _root)
			return ;
		while (node->p && node->p->p && node->p->color == true) {
			if (node->p == node->p->p->left) {
				y = node->p->p->right;
				if (y && y->color == true) {
					node->p->color = false;
					y->color = false;
					node->p->p->color = true;
				}
				else {
					if (node == node->p->right) {
						node = node->p;
						left_rotate(node);
					}
					node->p->color =  false;
					node->p->p->color = true;
					right_rotate(node->p->p);
				}	
			}
			else {
				y = node->p->p->left;
				if (y && y->color == true) {
					node->p->color = false;
					y->color = false;
					node->p->p->color = true;
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
		if (!x || !x->right)
			return ;
		TreeNode *y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->p = x;
		}
		y->p = x->p;
		if (!x->p) {
			_root = y;
		}
		else if (x == x->p->left)
			x->p->left = y;
		else
			x->p->right = y;
		y->left =x;
		x->p = y;
	}

	void right_rotate(TreeNode *y) {
		if (!y || !y->left)
			return ;
		TreeNode *x = y->left;
		y->left = x->right;
		if (x->right)
			x->right->p = y;
		x->p = y->p;	
		if (!y->p)
			_root = x;
		else if (y == y->p->left)
			y->p->left = x;
		else
			y->p->right = x;
		y->p = x;
		x->right = y;
	}


	TreeNode		*_root;
	size_type		_size;
	allocator_type	_alloc;
	key_compare		_comp;
};


}

#endif	