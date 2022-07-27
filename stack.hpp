#ifndef __STACK_HPP__
# define __STACK_HPP__

#include <iterator>
#include <memory>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "type_traits.hpp"
#include <type_traits>
#include "vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
	public:

		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;


		explicit stack (const container_type& ctnr = container_type()):_cont(ctnr) { }
		
		bool empty() const {
			return _cont.empty();
		}
		
		size_type size() const {
			return _cont.size();
		}
		
		value_type& top() {
			return _cont.back();
		}
		
		const value_type& top() const {
			return _cont.back();
		}
		
		void push (const value_type& val) {
			_cont.push_back(val);
		}
		
		void pop() {
			_cont.pop_back();
		}
		
		template <class T, class Container>
		friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return(lhs._cont == rhs._cont);
		}
		
		template <class T, class Container>
		friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return(lhs._cont != rhs._cont);
		}
		
		template <class T, class Container>
		friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return(lhs._cont < rhs._cont);
		}
		
		template <class T, class Container>
		bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return(lhs._cont <= rhs._cont);
		}
		
		template <class T, class Container>
		bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return(lhs._cont > rhs._cont);
		}
		
		template <class T, class Container>
		bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return(lhs._cont >= rhs._cont);
		}
		
		private:
			container_type _cont;
	};

}

#endif