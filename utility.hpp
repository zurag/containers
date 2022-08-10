#ifndef __UTILITY_HPP__
# define __UTILITY_HPP__


#include "vector.hpp"
// #include "map.hpp"
#include "type_traits.hpp"
#include "iterator.hpp"

namespace ft {

template <class T1, class T2>
struct pair
{	
	T1 first;
	T2 second;

	pair():first(T1()), second(T2()) {}

	template<class U, class V>
	pair(const pair<U, V> &pr):first(pr.first), second(pr.second) {}

	pair(const T1& a, const T2& b) : first(a), second(b) {}

	~pair() {}

	pair& operator= (const pair& pr) {
		if (&pr != this) {
			first = pr.first;
			second = pr.second;
		}
		return *this;
	}
};

template <class T1, class T2>
pair<T1,T2> make_pair (T1 x, T2 y) {
	return ft::pair<T1, T2>(x, y);
}

// template <class T1, class T2>
// bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y) {
// 	return x.first == y.first && x.second == y.second;
// }

// template <class T1, class T2>
// bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y) {
// 	return !(x == y);
// }

// template <class T1, class T2>
// bool operator< (const pair<T1, T2>& x, const pair<T1, T2>& y) {
// 	return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
// }

// template <class T1, class T2>
// bool operator> (const pair<T1, T2>& x, const pair<T1, T2>& y) {
// 	return y < x;
// }

// template <class T1, class T2>
// bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y) {
// 	return !(x < y);
// }

// template <class T1, class T2>
// bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y) {
// 	return !(y < x);
// }

template <class InputIterator1, class InputIterator2>
bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {

	for (; first1 != last1; ++first1, ++first2) {
		if (!(*first1 == *first2))
			return false;
	}
	return true;
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal (InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, BinaryPredicate pred) {
	for (; first1 != last1; ++first1, ++first2) {
		if (!pred(*first1,*first2))
			return false;
	}
	return true;
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2) {
	for (; first1 != last1; ++first1, ++first2) {
		if (first2 == last2 || *first2 < *first1)
			return false;
		else if (*first1 < *first2)
			return true;
	}
	return (first2 != last2);
}

// template <class InputIterator1, class InputIterator2, class Compare>
// bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
// 					InputIterator2 first2, InputIterator2 last2, Compare comp) {
// 	for (; first1 != last1; ++first1, ++first2) {
// 		if (first2 == last2 || comp(*first2 < *first1))
// 			return false;
// 		else if (comp(*first1 < *first2))
// 			return true;
// 	}
// 	return (first2 != last2);
// }






}



// namespace std {
// 	template <class T, class Alloc>
// 	void swap(ft::vector<T, Alloc> &v1, ft::vector<T, Alloc> &v2 ) {
// 		v1.swap(v2);
// 	}

// 	template < class Key, class T, class Compare , class Alloc >
// 	void swap(ft::map<Key, T, Compare, Alloc> &m1, ft::map<Key, T, Compare, Alloc> &m2 ) {
// 		m1.swap(m2);
// 	}
// }



#endif