#include <iterator>
#include "iterator.hpp"
#include <vector>
#include <iostream>
#include <typeinfo>
#include <list>
#include <set>

// No Compile
// void test1() {
// 	typedef std::iterator_traits<std::vector<int> > traits;
// 	std::cout << traits::difference_type() << '\n';
// }


//iterator type
void test2() {
	typedef ft::iterator_traits<int *> traits;
	typedef std::iterator_traits<std::list <int> > f_traits;

	if (typeid(traits::iterator_category) == typeid(std::random_access_iterator_tag))
		std::cout << "OK" << '\n';
	if (typeid(traits::iterator_category) == typeid(std::random_access_iterator_tag))
		std::cout << "OK" << '\n';



}











int main() {
	test2();
	return 0;
}