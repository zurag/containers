#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__

#include <cstddef>
#include <iostream>
#include <iterator>


namespace ft
{

	template <class Iter>
	struct iterator_traits {
	public:
		typedef typename Iter::value_type								value_type;
		typedef typename Iter::difference_type								difference_type;
		typedef typename Iter::pointer									pointer;
		typedef typename Iter::reference								reference;
		typedef typename Iter::iterator_category							iterator_category;
	};
	
	template <typename T>
	struct iterator_traits<T*> {
	public:
		typedef T													value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef ptrdiff_t										difference_type;
		typedef std::random_access_iterator_tag								iterator_category;
	};


template <class Iter>
class reverse_iterator {
public:	
	public:
		typedef Iter																		iterator_type;
		typedef typename iterator_traits<Iter>::iterator_category							iterator_category;
		typedef typename iterator_traits<Iter>::value_type									value_type;
		typedef typename iterator_traits<Iter>::difference_type								difference_type;
		typedef typename iterator_traits<Iter>::reference									reference;
		typedef typename iterator_traits<Iter>::pointer										pointer;

		explicit reverse_iterator(iterator_type value) : iter(value) {}
		
		reverse_iterator() : iter() {}

		~reverse_iterator(){}
		
		iterator_type base() const { 
			return iter;
		}		

		template <class U>
		reverse_iterator(const reverse_iterator<U>& other,
				typename ft::enable_if<std::is_convertible<U, Iter>::value>::type* = 0)
						: iter(other.base()) {};
		
		reverse_iterator &operator=(const reverse_iterator &obj) {
			iter = obj.iter;
			return *this;
		}

		reference operator*() {
			Iter copy(iter);
			return *(--copy);
		}
		
		pointer operator->() {
			return iter.operator->();
		}
		
		reverse_iterator&	operator++() {
			--iter;
			return *this;
		}

		reverse_iterator 	operator++(int) {
			reverse_iterator tmp(*this);
			iter--;
			return tmp;
		}
		
		reverse_iterator& operator--() {
			++iter;
			return *this;
		}

		reverse_iterator 	operator--(int) {
			reverse_iterator tmp(*this);
			iter++;
			return tmp;
		}
		
		reverse_iterator 	operator+(difference_type n) const {
			return reverse_iterator(iter - n);
		}

		reverse_iterator& 	operator+=(difference_type n) {
			iter -= n;
			return *this;
		}

		reverse_iterator 	operator-(difference_type n) const {
			return reverse_iterator(iter + n);
		}
		
		reverse_iterator& 	operator-=(difference_type n) {
			iter += n;
			return *this;
		}
		
		reference operator[](difference_type n) const {
			return iter[-n-1];
		}

		template <class Iter1>
		bool operator!= (const reverse_iterator<Iter1>& rhs) const {
			return this->base() != rhs.base();
		}

		template <class Iter1>
		bool operator> (const reverse_iterator<Iter1>& rhs) const{
			return this->base() < rhs.base();
		}

		template <class Iter1>
		bool operator>= (const reverse_iterator<Iter1>& rhs) const{
			return this->base() <= rhs.base();
		}

		template <class Iter1>
		bool operator< (const reverse_iterator<Iter1>& rhs) const{
			return this->base() > rhs.base();
		}

		template <class Iter1>
		bool operator<= (const reverse_iterator<Iter1>& rhs) const{
			return this->base() >= rhs.base();
		}
	
		template <class Iter1>
		bool operator== (const reverse_iterator<Iter1>& rhs) const{
			return this->base() == rhs.base();
		}

	private:
		Iter iter;
};

	template <class Iter1, class Iter2>
	typename reverse_iterator<Iter1>::difference_type operator- (
			const reverse_iterator<Iter1>& lhs,
			const reverse_iterator<Iter2>& rhs) {
		return(lhs.base() - rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it) {
		return (rev_it + n);
	}

}


#endif