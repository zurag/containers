#include <map>
#include <iterator>
#include <assert.h>
#include <iostream>
#include <typeinfo>
#include "map.hpp"

void ConstructorTest() {
	size_t i = 0;
	std::map<int, int> dict;
	for (int i = 0; i < 10; ++i) {
		dict.insert(std::make_pair(i, i));
	}

	for (std::map<int, int>::iterator it = dict.begin(); it != dict.end(); ++it) {
		std::cout << it->first << ' ' << it->second << ' ';
	}
	std::cout << '\n';
	
	ft::map<int, int> dict2;
	i = 0;
	ft::pair<ft::map<int, int>::iterator, bool> p;
	// for (int i = 0; i < 10; ++i) {
	// 	dict2.insert(ft::make_pair(i, i));
	// 	// p = dict2.insert(ft::make_pair(i, i));
	// 	// std::cout << p.first->first << ' ' << p.second << '\n';
	// }

	dict2.insert(ft::make_pair(15, 1));
	dict2.insert(ft::make_pair(5, 1));
	dict2.insert(ft::make_pair(1, 1)); // head == 5 

	for (ft::map<int, int>::iterator it = dict2.end(); it != dict2.begin();) {
		--it;
		std::cout << it->first << ' ' << it->second << ' ';

		break;
	}
	// std::cout << '\n';


}

void TreeNodeTest() {
	ft::Node<int, int> node(ft::make_pair(1, 1), true);
	std::cout << node.color << ' ' << node.value_.first << ' ' << node.value_.second << '\n';
	ft::Node<int, int> node2(node);
	std::cout << node2.color << ' ' << node2.value_.first << ' ' << node2.value_.second << '\n';

}



int main() {
	// TreeNodeTest();
	ConstructorTest();
	return 0;
}