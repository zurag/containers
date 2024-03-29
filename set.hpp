#ifndef __SET_HPP__
# define __SET_HPP__

#include "Tree.hpp"

namespace ft {

template <class T, class Compare = std::less<T>,
			class Alloc = std::allocator<T> >
class set
{
public:

	typedef typename delConst<T>::type      		        key_type;
	typedef typename delConst<T>::type 	                    value_type;
	typedef Compare										key_compare;
    typedef Compare										value_compare;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;
	typedef Tree<value_type, value_compare, allocator_type>	Tree_type;

public:
	typedef typename Tree_type::iterator					iterator;
	typedef typename Tree_type::const_iterator				const_iterator;
	typedef typename Tree_type::reverse_iterator			reverse_iterator;
	typedef typename Tree_type::const_reverse_iterator		const_reverse_iterator;

	set (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()):_tree(new Tree_type(comp, alloc)),
				_comp(comp), _alloc(alloc)
	{
	
	}

	template <class InputIterator>
 	set (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()): _tree (new Tree_type(first, last, comp, alloc)),
				_comp(comp), _alloc(alloc){
	}

	set (const set& x): _tree (new Tree_type(*x._tree)), _comp(x._comp), _alloc(x._alloc) {
	}

	set& operator= (const set& x) {
		*_tree = *x._tree;
		_comp = x.key_comp();
		_alloc = x.get_allocator();
		return *this;
	}

	~set() {
		delete _tree;
	}

	iterator begin() {
		return _tree->begin();
	}
	
	const_iterator begin() const {
		return _tree->begin();
	}

	iterator end() {
		return _tree->end();
	}
	
	const_iterator end() const {
		return _tree->end();
	}

	reverse_iterator rbegin() {
		return _tree->rbegin();
	}

	const_reverse_iterator rbegin() const {
		return _tree->rbegin();
	}

	reverse_iterator rend() {
		return _tree->rend();
	}
	
	const_reverse_iterator rend() const {
		return _tree->rend();
	}

	bool empty() const {
		return _tree->empty();
	}

	size_type size() const {
		return _tree->size();
	}

	size_type max_size() const {
		return _tree->max_size();
	}

	// mapped_type& operator[] (const key_type& k) {
	// 	iterator it = _tree->find(k);
	// 	if (it != end())
	// 		return it->second;
	// 	else
	// 		return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
	// }

	pair<iterator,bool> insert (const value_type& val) {
		return _tree->insert(val);
	}

	iterator insert (iterator position, const value_type& val) {
		return _tree->insert(position, val);
	}

	template <class InputIterator>
	void insert (InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
		_tree->insert(first, last);
	}

	void erase (iterator position) {
		_tree->erase(position);
	}

	size_type erase (const key_type& k) {
		return _tree->erase(k);
	}

	void erase (iterator first, iterator last) {
		for (; first != last;) {
			_tree->erase(first++);
		}
	}

	void swap (set& x) {
		std::swap(this->_tree, x._tree);
	}

	void clear() {
		_tree->clear();
	}

	key_compare key_comp() const {
		return _comp;
	}

	value_compare value_comp() const {
		return value_compare(_comp);
	}

	iterator find (const key_type& k) {
		return _tree->find(k);
	}
	
	const_iterator find (const key_type& k) const {
		return _tree->find(k);
	}

	size_type count (const key_type& k) const {
		return _tree->count(k);
	}

	iterator lower_bound (const key_type& k) {
		return _tree->lower_bound(k);
	}
	
	const_iterator lower_bound (const key_type& k) const {
		return _tree->lower_bound(k);
	}

	iterator upper_bound (const key_type& k) {
		return _tree->upper_bound(k);
	}
	
	const_iterator upper_bound (const key_type& k) const {
		return _tree->upper_bound(k);
	}

	pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
		return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
	}
	
	pair<iterator,iterator> equal_range (const key_type& k) {
		return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
	}

	allocator_type get_allocator() const {
		return _alloc;
	}

	friend bool operator==( const set<T,Compare,Alloc>& lhs,
					const set<T,Compare,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	
	friend bool operator!=( const set<T,Compare,Alloc>& lhs,
					const set<T,Compare,Alloc>& rhs ) {
		return !(lhs == rhs);
	}

	friend bool operator<( const set<T,Compare,Alloc>& lhs,
					const set<T,Compare,Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	friend bool operator<=( const set<T,Compare,Alloc>& lhs,
					const set<T,Compare,Alloc>& rhs ) {
		return !(rhs < lhs);
	}

	friend bool operator>( const set<T,Compare,Alloc>& lhs,
					const set<T,Compare,Alloc>& rhs ) {
		return (rhs < lhs);
	}

	friend bool operator>=( const set<T,Compare,Alloc>& lhs,
					const set<T,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	}

private:
	Tree_type *_tree;
	key_compare	_comp;
	allocator_type _alloc;
};


}


#endif	