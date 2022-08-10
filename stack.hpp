#ifndef __STACK_HPP__
# define __STACK_HPP__

#include "vector.hpp"

namespace ft
{
	template <class T, class Cont = ft::vector<T> >
	class stack
	{
	public:
		typedef			 Cont										container_type;
		typedef typename Cont::value_type							value_type;
		typedef typename Cont::size_type							size_type;
		typedef typename Cont::reference							reference;
		typedef typename Cont::const_reference						const_reference;

		explicit stack (const container_type& ctnr = container_type()):_cont(ctnr) { }

		stack(const stack &copy):_cont(copy._cont) { }

		stack& operator=(const stack &copy)	{
			if (this != &copy)
				_cont = copy._cont;
			return *this;
		}

		~stack() { }

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
		
		friend bool operator== (const stack<T,Cont>& lhs, const stack<T,Cont>& rhs) {
			return(lhs._cont == rhs._cont);
		}
		
		friend bool operator!= (const stack<T,Cont>& lhs, const stack<T,Cont>& rhs) {
			return(lhs._cont != rhs._cont);
		}
		
		friend bool operator< (const stack<T,Cont>& lhs, const stack<T,Cont>& rhs) {
			return(lhs._cont < rhs._cont);
		}
		
		friend bool operator<= (const stack<T,Cont>& lhs, const stack<T,Cont>& rhs) {
			return(lhs._cont <= rhs._cont);
		}
		
		friend bool operator> (const stack<T,Cont>& lhs, const stack<T,Cont>& rhs) {
			return(lhs._cont > rhs._cont);
		}
		
		friend bool operator>= (const stack<T, Cont>& lhs, const stack<T,Cont>& rhs) {
			return(lhs._cont >= rhs._cont);
		}
		
		private:
			container_type _cont;
	};

}

#endif