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
	dict.insert(std::make_pair(-20, -20));
	dict.insert(std::make_pair(-10, -10));
	dict.insert(std::make_pair(-15, -15));
	dict.insert(std::make_pair(-1, -1));
	dict.insert(std::make_pair(-4, -4));
	std::map<int, int>::iterator sit;
	for (sit = dict.begin(); sit != dict.end(); ++sit) {
		std::cout << sit->first << ' ' << sit->second << ' ';
	}
	std::cout << '\n';
	--sit;
	for (; sit != dict.begin(); --sit) {
		std::cout << sit->first << ' ' << sit->second << ' ';
	}
	std::cout << '\n';
	std::cout << '\n';


	ft::map<int, int> dict2;
	i = 0;
	for (int i = 0; i < 10; ++i) {
		dict2.insert(ft::make_pair(i, i));
	}
	dict2.insert(ft::make_pair(-20, -20));
	dict2.insert(ft::make_pair(-10, -10));
	dict2.insert(ft::make_pair(-15, -15));
	dict2.insert(ft::make_pair(-1, -1));
	dict2.insert(ft::make_pair(-4, -4));
	ft::map<int, int>::iterator fit;
	for (fit = dict2.begin(); fit != dict2.end(); ++fit) {
		std::cout << fit->first << ' ' << fit->second << ' ';
	}
	std::cout << '\n';
	--fit;

	for (; fit != dict2.begin(); --fit) {
		std::cout << fit->first << ' ' << fit->second << ' ';	
	}
	std::cout << '\n';
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