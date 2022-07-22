#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__

#include <cstddef>
#include <iterator>


namespace ft
{
template <class Iterator>
struct iterator_traits {
   typedef typename Iterator::iterator_category iterator_category;
   typedef typename Iterator::value_type value_type;
   typedef typename Iterator::difference_type difference_type;
   typedef difference_type distance_type;
   typedef typename Iterator::pointer pointer;
   typedef typename Iterator::reference reference;
};


template <class T *>
struct iterator_traits {
   typedef typename		random_access_iterator_tag iterator_category;
   typedef typename		T value_type;
   typedef typename		ptrdiff_t difference_type;
   typedef typename 	T* pointer;
   typedef typename 	T& reference;
};


template <class const T *>
struct iterator_traits {
   typedef typename		random_access_iterator_tag iterator_category;
   typedef typename		T value_type;
   typedef typename		ptrdiff_t difference_type;
   typedef typename 	const T* pointer;
   typedef typename 	const T& reference;
};



}

// template <class Iterator>
// class reverse_iterator {
// 	Iterator iter;
// public:
// 	reverse_iterator<Iterator>& operator++() {
// 		--iter;
// 		return *this;
// 	}

// 	Iterator base() const {return iter;}


// };






#endif