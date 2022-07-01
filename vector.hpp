#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

#include <iterator>
#include <memory>
#include <cstddef>
#include <iostream>

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

		explicit vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()):_alloc(alloc) {
			_capacity = n;
			_size = n;
			_arr = _alloc.allocate(n);
			for (size_t i = 0; i < n; ++i) {
				_alloc.construct(_arr + i, val);
			}
		}

		// vector (const vector& x){
		// 	_capacity = x.capacity();
		// 	_size = x.size();
		// 	_arr = _alloc.allocate(x.capacity());
		// 	for (size_t i; i < _size; ++i) {
		// 		_alloc.construct(_arr + i, val);
		// 	}

		// }

		~vector() {
			if (_capacity) {
				for (size_t i = 0; i < _size; ++i) {
					_alloc.destroy(_arr + i);
				}
				_alloc.deallocate(_arr, _capacity);
			}
		}

		size_type size() const {
			return _size;
		}


		// size_type max_size() const {
		// }

		size_type capacity() const {
			return _capacity;
		}

		// void resize(size_type count, T value = T() ) {
		// 	if (count > _capacity) {
		// 		//выделяем заново память и копируем элементы
		// 	}
		// 	else
		// 		_size = count;
		// }

		reference operator[] (size_type n) {
			return *(_arr + n);
		}
		
		const_reference operator[] (size_type n) const {
			return *(_arr + n);
		}

	private:
		T				*_arr;
		int				_capacity;
		int				_size;
		allocator_type	_alloc;
	};


}


#endif