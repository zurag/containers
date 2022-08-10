#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

#include <iterator>
#include <memory>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "type_traits.hpp"
#include "utility.hpp"
#include <type_traits>
#include "iterator.hpp"
#include <cstring>

namespace ft
{

	template <class T, class Alloc = std::allocator<T> >
	class vector
	{	
		template <class U>
		class Iterator :public std::iterator<std::random_access_iterator_tag, U>
		{
		public:
			typedef std::random_access_iterator_tag iterator_category;
			typedef ptrdiff_t difference_type;
			typedef typename delConst<U>::type		value_type;
			typedef typename delConst<U&>::type		reference;
			typedef typename delConst<U*>::type		pointer;

			typedef pointer iterator_type;

			Iterator():_ptr(nullptr) { }
			
			template <typename Iter>
			Iterator(const Iterator<Iter>& other,
				typename ft::enable_if<std::is_convertible<Iter, U>::value>::type* = 0)
						: _ptr(other.operator->()) {};

			Iterator(const pointer x):_ptr(x) {}

			~Iterator() {}
			
			reference operator*() const {return *_ptr;}
		
			pointer operator->() const {return _ptr;}

			Iterator& operator= (const Iterator<typename delConst<U>::type> &x) {
				_ptr = x.operator->();
				return *this;
			}

			Iterator& operator+= (int n) {
				_ptr += n;
				return *this;
			}

			Iterator& operator-= (int n) {
				_ptr -= n;
				return *this;
			}
			
			Iterator& operator++() {
				++_ptr;
				return *this;
			}
			
			Iterator operator++(int) {
				Iterator copy(*this);
				++_ptr;
				return copy;
			}
			
			Iterator& operator--() {
				--_ptr;
				return *this;
			}
			
			Iterator operator--(int) {
				Iterator copy(*this);
				--_ptr;
				return copy;
			}

			Iterator operator+(int n) const {
				Iterator copy = *this;
				copy += n;
				return copy;
			}
			
			Iterator operator-(int n) const {
				Iterator copy = *this;
				copy -= n;
				return copy;
			}
			
			reference operator[](size_t n) const {
				return *(_ptr + n);
			}

			friend Iterator operator+(int n, const Iterator &x) {
				Iterator it(x);
				return it + n;
			}
			
			friend Iterator operator-(int n, const Iterator &x) {
				Iterator it(x);
				return it - n;
			}

			template <class Iter1>
			bool operator!= (const Iterator<Iter1>& rhs) const{
				return this->operator->() != rhs.operator->();
			}

			template <class Iter1>
			bool operator> (const Iterator<Iter1>& rhs) const{
				return this->operator->() > rhs.operator->();
			}

			template <class Iter1>
			bool operator>= (const Iterator<Iter1>& rhs) const{
				return this->operator->() >= rhs.operator->();
			}

			template <class Iter1>
			bool operator< (const Iterator<Iter1>& rhs) const{
				return this->operator->() < rhs.operator->();
			}

			template <class Iter1>
			bool operator<= (const Iterator<Iter1>& rhs) const{
				return this->operator->() <= rhs.operator->();
			}
		
			template <class Iter1>
			bool operator== (const Iterator<Iter1>& rhs) const{
				return this->operator->() == rhs.operator->();
			}

			template <class Iter1>
			difference_type operator-(const Iterator<Iter1> &x) const {return _ptr - x.operator->();}

			template <class Iter1>
			difference_type operator+(const Iterator<Iter1> &x) const {return _ptr + x.operator->();}

		private:
			pointer _ptr;
		};

	public:
		typedef T value_type;

		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		
		typedef size_t size_type; 
		typedef ptrdiff_t difference_type;
		typedef Iterator<T> iterator; 
		typedef Iterator<const T> const_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;

		iterator begin() {
			return iterator(&_arr[0]);
		}

		const_iterator begin() const {
			return const_iterator(&_arr[0]);
		}

		iterator end() {
			return iterator(&_arr[_size]);
		}
		
		const_iterator end() const {
			return const_iterator(&_arr[_size]);
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

		explicit vector (const allocator_type& alloc = allocator_type()):_alloc(alloc),
						_arr(nullptr), _capacity(0), _size(0) {}

		explicit vector (size_type n, const value_type& val,
						const allocator_type& alloc = allocator_type()):_alloc(alloc), 
						_arr(nullptr), _capacity(n), _size(n) {
			if (n > 0) {
				_arr = _alloc.allocate(n);
				for (size_type i  = 0; i < n; ++i) {
					_alloc.construct(_arr + i, val);
				}
			}
			else {
				_capacity = 0;
				_size = 0;
			}
		}

		explicit vector (size_type n,
						const allocator_type& alloc = allocator_type()):_alloc(alloc),
						_arr(nullptr), _capacity(n), _size(n) {
			if (n > 0) {
				_arr = _alloc.allocate(n);
				_capacity = n;
				for (size_type i  = 0; i < n; ++i) {
					_alloc.construct(_arr + i);
				}
			}
			else {
				_capacity = 0;
				_size = 0;
			}
		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!std::is_integral<InputIterator>::value>::type* = 0)
				:_alloc(alloc), _arr(nullptr), _capacity(0), _size(0) {
			_capacity = static_cast<size_type>(std::distance(first, last));
			_arr = _alloc.allocate(_capacity);
			for (; first != last; ++first) {
				push_back(*first);
			}
		}

		vector (const vector& x): _alloc(x.get_allocator()){
			_size = 0;
			_arr = NULL;
			size_t x_size = x.size();

			if (x.capacity() > 0) {
				_arr = _alloc.allocate(x.capacity());
				for (_size = 0; _size < x_size; ++_size) {
					_alloc.construct(_arr + _size, x[_size]);
				}
				_size = x_size;
			}
			_capacity = x.capacity();
		}

		vector& operator= (const vector& x) {
			if (&x != this) {
				size_t x_size = x.size();
				if (_capacity > 0) {
					for (size_t i = 0; i < _size; ++i) {
						_alloc.destroy(_arr + i);
					}
					_alloc.deallocate(_arr, _capacity);
				}
				if (x.capacity() > 0) {
					_arr = _alloc.allocate(x.capacity());
					for (_size = 0; _size < x_size; ++_size) {
						_alloc.construct(_arr + _size, x[_size]);
					}
				}
				else
					_arr = NULL;
				_capacity = x.capacity();
				_size = x.size();
			}
			return *this;
		}

		~vector() {
			if (_capacity) {
				for (size_type i = 0; i < _size; ++i) {
					_alloc.destroy(_arr + i);
				}
				_alloc.deallocate(_arr, _capacity);
			}
			_capacity = 0;
			_size = 0;
		}

		size_type size() const {
			return _size;
		}

		size_type max_size() const {
			return _alloc.max_size();
		}

		size_type capacity() const {
			return _capacity;
		}

		bool empty() const {
			return (_size == 0);
		}

		void resize(size_type count, T value = T()) {

			if (count > _capacity) {
				size_type	mem = _capacity * 2;
				if (count > mem)
					mem = count;
				reserve(mem);
				for (; _size < count; ++_size) {
					_alloc.construct(_arr + _size, value);
				}
			}
			else if (count >_size && count < _capacity) {
				for (; _size < count; ++_size) {
					_alloc.construct(_arr + _size, value);
				}
			}
			else if (count < _size) {
				for (size_type i = _size - 1; i > count; --i) {
					_alloc.destroy(_arr + i);
				}
				_size = count;
			}
		}

		void reserve (size_type n) {
			T *tmp = NULL;

			if (n > _capacity) {
				tmp = _alloc.allocate(n);
				for (size_t i = 0; i < _size; ++i) {
					_alloc.construct(tmp + i, _arr[i]);
				}
				if (_capacity > 0) {
					for (size_type i = 0; i < _size; ++i) {
						_alloc.destroy(_arr + i);
					}
					_alloc.deallocate(_arr, _capacity);
				}
				_capacity = n;
				_arr = tmp;
			}
		}

		reference operator[] (size_type n) {
			return *(_arr + n);
		}
		
		const_reference operator[] (size_type n) const {
			return *(_arr + n);
		}

		reference at (size_type n) {
			if (n >= _size)
				throw std::out_of_range("vector");
			return *(_arr + n);
		}
		
		const_reference at (size_type n) const {
			if (n >= _size)
				throw std::out_of_range("vector");
			return *(_arr + n);
		}

		reference front() {			
			return _arr[0];
		}
		
		const_reference front() const {
			return _arr[0];
		}

		reference back() {
			return _arr[_size - 1];	
		}
		
		const_reference back() const {
			return _arr[_size - 1];
		}

		value_type* data() {
			return _arr;
		}
		
		const value_type* data() const {
			return _arr;
		}

		void push_back(const value_type& val) {
			if (_size == _capacity) {
				if (!_capacity) {
					reserve(1);
				}
				else
					reserve(_capacity * 2);
			}
			_alloc.construct(_arr + _size, val);
			++_size;
		}

		void pop_back() {
			_alloc.destroy(_arr + _size - 1);
			--_size;
		}

		void clear() {
			if (_size) {
				for (size_type i = 0; i < _size; ++i) {
					_alloc.destroy(_arr + i);
				}
			}
			_size = 0;
		}

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
			clear();
			reserve(static_cast<size_type>(std::distance(first, last)));
			for (; first != last; ++first) {
				push_back(*first);
			}
		}

		void assign (size_type n, const value_type& val) {
			clear();
			reserve(n);
			for (size_type i = 0; i < n; ++i) {
				push_back(val);
			}
		}

		// template <typename std::enable_if<std::is_pod<T>::value>::type>
		// iterator erase (iterator position) {
		// 	size_type start = static_cast<size_type>(position.operator->() - _arr);
		// 	_alloc.destroy(_arr + start);
		// 	--_size;
		// 	std::memmove(_arr + start, _arr + start + 1, (_size - start - 1) * sizeof(T));
		// 	return position;
		// }

		iterator erase (iterator position) {
			size_type start = static_cast<size_type>(position.operator->() - _arr);

			for (size_type i = start; i < _size - 1; ++i) {
				_arr[i] = _arr[i + 1];
			}
			_alloc.destroy(_arr + _size - 1);
			--_size;
			return position;
		}

		iterator erase (iterator first, iterator last) {

			size_type start = static_cast<size_type>(first.operator->() - _arr);
			size_type size = static_cast<size_type>(last.operator->() - first.operator->());
			for (size_type i = 0; i < size; ++i) {
				_alloc.destroy(_arr + start + i);
			}
			
			for (size_type i = start; i < _size - size; ++i) {
				_alloc.construct(_arr + i, *(_arr + i + size));
				_alloc.destroy(_arr + i + size);
			}
			_size -= size;

			return first;
		}

		iterator insert (iterator position, const value_type& val) {
			T *tmp = nullptr;
			iterator new_position;
			size_type start = 0;
			if (_size == _capacity) {
				if (!_capacity) {
					reserve(1);
					_alloc.construct(_arr, val);
					++_size;
					return iterator(_arr);
				}
				else {
					tmp = _alloc.allocate(_capacity * 2);
					for (size_t i = 0; i < _size + 1; ++i, ++start) {
						if (_arr + i == position.operator->()) {
							_alloc.construct(tmp + i, val);
							new_position = (tmp + i);
							++i;
						}
						_alloc.construct(tmp + i, _arr[start]);
					}
					if (_capacity > 0) {
						for (size_type i = 0; i < _size; ++i) {
							_alloc.destroy(_arr + i);
						}
						_alloc.deallocate(_arr, _capacity);
					}
					_capacity *= 2;
					++_size;
					_arr = tmp;
				}
			}
			else {
				for (iterator it = end() - 1; it >= position; --it) {
					_alloc.construct((it + 1).operator->(), *it);
					_alloc.destroy(it.operator->());
				}
				_alloc.construct(position.operator->(), val);
				++_size;
				new_position = position;
			}
			return new_position;
		}

		void insert(iterator position, size_type n, const value_type& val) {
			T *tmp = NULL;
			size_t new_capacity = _capacity;
			size_t start = 0;
			if (_size + n > _capacity) {
				if (!_capacity) {
					reserve(n);
					for (size_t i = 0; i < n; ++i)
						_alloc.construct(_arr + i, val);
					_size = n;
					return ;
				}
				else {
					if (_capacity * 2 > _size + n)
						new_capacity *= 2;
					else
						new_capacity = _size + n;
					tmp = _alloc.allocate(new_capacity);
					for (size_t i = 0; i < _size; ++i) {
						if (_arr + i == position.operator->()) {
							for (size_t j = 0; j < n; ++j) {
								_alloc.construct(tmp + start++, val);
							}
						}
						_alloc.construct(tmp + start++, _arr[i]);
					}
					if (_capacity > 0) {
						for (size_type i = 0; i < _size; ++i) {
							_alloc.destroy(_arr + i);
						}
						_alloc.deallocate(_arr, _capacity);
					}
					_capacity = new_capacity;
					_size += n;
					_arr = tmp;
				}
			}
			else {
				for (iterator it = end() - 1; it >= position; --it) {
					_alloc.construct((it + n).operator->(), *it);
					_alloc.destroy(it.operator->());
				}
				for (size_t j = 0; j < n; ++j) {
					_alloc.construct(position.operator->() + j, val);
				}
				_size += n;
			}
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
			size_type n = static_cast<size_type>(std::distance(first, last));
 			T *tmp = nullptr;
			size_type new_capacity = _capacity;
			size_type start = static_cast<size_type>(position.operator->() - _arr);

			if (_size + n > _capacity) {
				if (_capacity * 2 > _size + n)
					new_capacity *= 2;
				else
					new_capacity = _size + n;
				tmp = _alloc.allocate(new_capacity);
				try {
					size_type i = 0;
					for (; i < start; ++i) {
						_alloc.construct(tmp + i, _arr[i]);
					}
					for (;first != last; ++first, ++i) {
						_alloc.construct(tmp + i, *first);
					}
					for (; start < _size; ++start, ++i) {
						_alloc.construct(tmp + i, _arr[start]);
					}
					for (size_type j = 0; j < _size; ++j) {
						_alloc.destroy(_arr + j);
					}
					_alloc.deallocate(_arr, _capacity);
				}
				catch (...) {
					for( size_type j = 0; j < new_capacity; ++j)
						_alloc.destroy(tmp + j);
					_alloc.deallocate(tmp, new_capacity);
					throw std::runtime_error("vector insert error");
				}
				_capacity = new_capacity;
				_size += n;
				_arr = tmp;
			}
			else {
				for (iterator it = end() - 1; it >= position; --it) {
					_alloc.construct((it + n).operator->(), *it);
					_alloc.destroy(it.operator->());
				}
				try {
					for (size_type j = 0; j < n; ++j) {
						_alloc.construct(position.operator->() + j, *(first++));
					}
				}
				catch (...) {
					for (size_type j = 0; j < n; ++j) {
						_alloc.destroy(position.operator->() + j);
					}
					throw std::runtime_error("vector insert error");
				}
				_size += n;
			}
		}

		void swap (vector& x) {
			std::swap(x._size, _size);
			std::swap(x._capacity, _capacity);
			std::swap(x._alloc, _alloc);
			std::swap(x._arr, _arr);
		}

		allocator_type get_allocator() const {
			return _alloc;
		}

	private:

		allocator_type	_alloc;
		T				*_arr;
		size_type		_capacity;
		size_type		_size;
	};

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i  < lhs.size(); ++i) {
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	}

	template <typename T, typename Alloc>
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T, typename Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}
	
	template <typename T, typename Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs > rhs);
	}
	
	template <typename T, typename Alloc>
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return rhs < lhs;
	}
	
	template <typename T, typename Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}
}

// namespace std {
// 	template <class T, class Alloc>
// 	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
// 		x.swap(y);
// 	}
// }


#endif