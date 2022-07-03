#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

#include <iterator>
#include <memory>
#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{	
	public:
	


		typedef T value_type;
		
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		
		typedef size_t size_type; 
		typedef ptrdiff_t difference_type;

		// typedef iterator; 
		// typedef const_iterator; 
		// typedef const_reverse_iterator;


		explicit vector (const allocator_type& alloc = allocator_type()):_alloc(alloc)
		{
			_arr = nullptr;
			_capacity = 0;
			_size = 0;
		}

		explicit vector (size_type n, const value_type& val,
						const allocator_type& alloc = allocator_type()):_alloc(alloc) {
			if (n > 0) {
				_arr = _alloc.allocate(n);
				_capacity = n;
				for (_size = 0; _size < n; ++_size) {
					_alloc.construct(_arr + _size, val);
				}
				_size = n;
			}
			else {
				_arr = NULL;
				_capacity = 0;
				_size = 0;
			}
		}

		explicit vector (size_type n,
						const allocator_type& alloc = allocator_type()):_alloc(alloc) {
			if (n > 0) {
				_arr = _alloc.allocate(n);
				_capacity = n;
				for (_size = 0; _size < n; ++_size) {
					_alloc.construct(_arr + _size);
				}
				_size = n;
			}
			else {
				_arr = NULL;
				_capacity = 0;
				_size = 0;
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
			return *this;
		}

		~vector() {
			if (_capacity) {
				for (size_t i = 0; i < _size; ++i) {
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
				size_t	mem = _capacity * 2;
				if (count > mem)
					mem = count;
				this->reserve(mem);
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
				for (size_t i = _size - 1; i > count; --i) {
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
					for (size_t i = 0; i < _size; ++i) {
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

		void push_back(const value_type& val) {
			if (_size == _capacity) {
				if (!_capacity) {
					reserve(1);
					_capacity = 1;
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
			if (_capacity) {
				for (size_t i = 0; i < _size; ++i) {
					_alloc.destroy(_arr + i);
				}
			}
			_size = 0;
		}

		allocator_type get_allocator() const {
			return _alloc;
		}

	private:
		T				*_arr;
		int				_capacity;
		int				_size;
		allocator_type	_alloc;
	};


}


#endif