#include <map>
#include <iterator>
#include <assert.h>
#include <iostream>
#include <typeinfo>
#include "map.hpp"


#define assertm(exp, msg) assert(((void)msg, exp))

void ConstructorTest() {
	{
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

	{
		ft::map<int, int> f_m;
		std::map<int, int> s_m;
		
		for (size_t i = 0; i < 30 * 10000; ++i) {
			f_m.insert(ft::make_pair(i, i + 10));
			s_m.insert(std::make_pair(i, i + 10));
		}
		ft::map<int, int> f_m2(f_m.begin(), f_m.end());
		std::map<int, int> s_m2(s_m.begin(), s_m.end());

		std::map<int, int>::iterator s_it = s_m2.begin();
		for (ft::map<int, int>::iterator it = f_m2.begin(); it != f_m2.end(); it++, s_it++) {
			assertm(it->first == s_it->first, "Fill construct check first value");
			assertm(it->second == s_it->second, "Fill construct check second value");
		}
		f_m2.clear();
	}
	{
		ft::map<int, int> f_m2;
		ft::map<int, int> f_m(f_m2.end(), f_m2.end());
		ft::map<int, int> f_m3;
		f_m3.insert(ft::make_pair(1, 1));
		f_m.clear();
	}
}

// void TreeNodeTest() {
// 	ft::Node<int, int> node(ft::make_pair(1, 1), true);
// 	std::cout << node.color << ' ' << node.value_.first << ' ' << node.value_.second << '\n';
// 	ft::Node<int, int> node2(node);
// 	std::cout << node2.color << ' ' << node2.value_.first << ' ' << node2.value_.second << '\n';
// }

void InsertTest() {

	{
		ft::map<int, int> f_m;
		std::map<int, int> s_m;
		
		f_m.insert(ft::make_pair(0, 10));
		s_m.insert(std::make_pair(0,10));
		f_m.insert(ft::make_pair(10, 10));
		s_m.insert(std::make_pair(10, 10));
		f_m.insert(ft::make_pair(50, 10));
		s_m.insert(std::make_pair(50, 10));
		f_m.insert(ft::make_pair(-10, 10));
		s_m.insert(std::make_pair(-10, 10));
		f_m.insert(ft::make_pair(6, 10));
		s_m.insert(std::make_pair(6, 10));
		ft::map<int, int>::iterator  it = f_m.find(6);
		std::map<int, int>::iterator s_it = s_m.find(6);

		f_m.insert(it, ft::make_pair(8, 8));
		s_m.insert(s_it, std::make_pair(8, 8));
		
		it = f_m.find(50);
		s_it = s_m.find(50);

		f_m.insert(it, ft::make_pair(60, 60));
		s_m.insert(s_it, std::make_pair(60, 60));

		f_m.insert(it, ft::make_pair(-20, -20));
		s_m.insert(s_it, std::make_pair(-20, -20));

		it = f_m.find(10);
		s_it = s_m.find(10);

		f_m.insert(it, ft::make_pair(12, 12));
		s_m.insert(s_it, std::make_pair(12, 12));

		s_it = s_m.begin();
		it = f_m.begin();
		for (; it != f_m.end(); ++it, ++s_it) {
			std::cout << it->first << ' ' << s_it->first << '\n';
			assertm(it->first == s_it->first, "Insert position check first value");
			assertm(it->second == s_it->second, "Insert position check second value");
		}

	}
}


void EraseBaseTest() {
	{
		ft::map<int, int> f_m;
		std::map<int, int> s_m;

		for (size_t i = 0; i < 100; ++i) {
			f_m.insert(ft::make_pair(i, i + 10));
			s_m.insert(std::make_pair(i, i + 10));
		}
		f_m.erase(f_m.begin());
		s_m.erase(s_m.begin());
		f_m.erase(--f_m.end());
		s_m.erase(--s_m.end());
		f_m.erase(f_m.begin());
		s_m.erase(s_m.begin());

		assertm(f_m.size() == s_m.size(), "Erase check size");
		std::map<int, int>::iterator s_it = s_m.begin();
		for (ft::map<int, int>::iterator it = f_m.begin(); it != f_m.end(); it++, s_it++) {
			assertm(it->first == s_it->first, "Erase check first value");
			assertm(it->second == s_it->second, "Erase check second value");
		}
	}
	{
		ft::map<int, int> f_m;
		std::map<int, int> s_m;

		for (size_t i = 0; i < 100; ++i) {
			f_m.insert(ft::make_pair(i, i + 10));
			s_m.insert(std::make_pair(i, i + 10));
		}
		f_m.erase(f_m.begin(), --f_m.end());
		s_m.erase(s_m.begin(), --s_m.end());
		assertm(f_m.size() == s_m.size(), "Erase check size");
		std::map<int, int>::iterator s_it = s_m.begin();
		for (ft::map<int, int>::iterator it = f_m.begin(); it != f_m.end(); it++, s_it++) {
			assertm(it->first == s_it->first, "Erase check first value");
			assertm(it->second == s_it->second, "Erase check second value");
		}
	}
}


void EraseKeyTest() {
	ft::map<int, int> f_m;
	std::map<int, int> s_m;

	for (size_t i = 0; i < 100; ++i) {
		f_m.insert(ft::make_pair(i, i + 10));
		s_m.insert(std::make_pair(i, i + 10));
	}

	f_m.erase(19);
	f_m.erase(15);
	f_m.erase(14);
	f_m.erase(12);
	f_m.erase(19);

	f_m.erase(86);
	f_m.erase(42);
	f_m.erase(21);

	s_m.erase(19);
	s_m.erase(15);
	s_m.erase(14);
	s_m.erase(12);
	s_m.erase(19);

	s_m.erase(86);
	s_m.erase(42);
	s_m.erase(21);

	std::map<int, int>::iterator s_it = s_m.begin();
	ft::map<int, int>::iterator it = f_m.begin();
	for (; it != f_m.end(); ++it, ++s_it) {
		assertm(it->first == s_it->first, "Erase key check first value");
		assertm(it->second == s_it->second, "Erase key check second value");
	}

}

void FindTest() {
	ft::map<int, int> f_m;

	for (size_t i = 0; i < 18; ++i) {
		f_m.insert(ft::make_pair(i, i + 10));
	}
	for (size_t i = 0; i < 18; ++i) {
		assertm(f_m.find(i) != f_m.end(), "Dont find value");
	}
	for (size_t i = 19; i < 30; ++i) {
		assertm(f_m.find(i) == f_m.end(), "Find value that dont exist");
	}	
}

void CountTest() {
	ft::map<int, int> f_m;

	for (size_t i = 0; i < 18; ++i) {
		f_m.insert(ft::make_pair(i, i + 10));
	}
	for (size_t i = 0; i < 18; ++i) {
		assertm(f_m.count(i) == 1, "Count");
	}
	for (size_t i = 19; i < 30; ++i) {
		assertm(f_m.count(i) == 0, "Count");
	}
}


void BoundTest() {
	{
		ft::map<char,int> mymap;
		ft::map<char,int>::iterator itlow,itup;
		mymap.insert(ft::make_pair('a', 20));
		mymap.insert(ft::make_pair('b', 40));
		mymap.insert(ft::make_pair('c', 60));
		mymap.insert(ft::make_pair('d', 80));
		mymap.insert(ft::make_pair('f', 100));
		mymap.insert(ft::make_pair('g', 100));

		
		itlow = mymap.lower_bound ('b');
		assertm(itlow->first == 'b', "Lower Bound");
		itlow = mymap.lower_bound ('e');
		assertm(itlow->first == 'f', "Lower Bound");
		itlow = mymap.lower_bound ('h');
		assertm(itlow == mymap.end(), "Lower Bound");

		itup = mymap.upper_bound ('d');
		assertm(itup->first == 'f', "Upper Bound");
		itup = mymap.upper_bound ('g');
		assertm(itup == mymap.end(), "Upper Bound");
	}
	{
		ft::map<int,int> f_m;
		std::map<int,int> s_m;

		for (size_t i = 0; i < 50; ++i) {
			s_m.insert(std::make_pair(i, i + 10));
			f_m.insert(ft::make_pair(i, i + 10));
		}

		for (int i = -2; i < 10; ++i) {
 			assertm(f_m.upper_bound(i)->first == s_m.upper_bound(i)->first, "Upper Bound first value");
			assertm(f_m.upper_bound(i)->second == s_m.upper_bound(i)->second, "Upper Bound second value");
			assertm(f_m.lower_bound(i)->first == s_m.lower_bound(i)->first, "Lower Bound first value");
			assertm(f_m.lower_bound(i)->second == s_m.lower_bound(i)->second, "Lower Bound first value");
		}
	}
}


void EqualityOperatorTest() {
	ft::map<int, int> f_m;
	for (size_t i = 0; i < 10; ++i) {
		f_m.insert(ft::make_pair(i, i));
	}
	ft::map<int, int> f_copy;
	f_copy = f_m;
	ft::map<int, int>::iterator it2 = f_copy.begin();
	for (ft::map<int, int>::iterator it = f_m.begin(); it != f_m.end(); ++it, ++it2) {
		assertm(it->first == it2->first, " Equality check first value");
		assertm(it->second == it2->second, " Equality check second value");
	}
	assertm(f_m.size() == f_copy.size(), " Equality check value");
}

void clearTest() {
	ft::map<int, int> f_m;

	for (size_t i = 0; i < 1000000; ++i)
		f_m.insert(ft::make_pair(i, i));
	f_m.clear();

	// std::map<int, int> s_m;
	// // std::cout << s_m.max_size() << std::endl;
	// for (size_t i = 0; i < 1000000; ++i)
	// 	s_m.insert(std::make_pair(i, i));
	// s_m.clear();
}


void ReverseIteratorTest() {
	ft::map<int, int> f_m;
	std::map<int, int> s_m;

	for (size_t i = 0; i < 50; ++i) {
		f_m.insert(ft::make_pair(i, i + 10));
		s_m.insert(std::make_pair(i, i + 10));
	}
	ft::map<int, int>::reverse_iterator r_fit = f_m.rbegin();
	std::map<int, int>::reverse_iterator r_sit = s_m.rbegin();

	for (; r_sit != s_m.rend(); ++r_sit, ++r_fit) {
		assertm(r_sit->first == r_fit->first, " Reverse Iterator check first value");
		assertm(r_sit->second == r_fit->second, " Reverse Iterator check second value");
	}
	r_fit = f_m.rbegin();
	r_sit = s_m.rbegin();
	for (; r_sit != s_m.rend(); ++r_sit, ++r_fit) {
		assertm((*r_sit).first == (*r_fit).first, " Reverse Iterator check operator* first value");
		assertm((*r_sit).second == (*r_fit).second, " Reverse Iterator check operator* second value");
	}
}


void CompareTest() {
	ft::map<int, int, std::greater<int> > f_m;
	std::map<int, int, std::greater<int> > s_m;

	for (size_t i = 0; i < 50; ++i) {
		f_m.insert(ft::make_pair(i, i + 10));
		s_m.insert(std::make_pair(i, i + 10));
	}
	ft::map<int, int >::iterator fit = f_m.begin();
	std::map<int, int>::iterator sit = s_m.begin();

	for (; sit != s_m.end(); ++sit, ++fit) {
		assertm(sit->first == fit->first, "Greater compare check first value");
		assertm(sit->second == fit->second, "Greater compare check second value");
	}

}


int main() {
	// TreeNodeTest();
	ConstructorTest();
	std::cout << "ConstructorTest OK" << std::endl;
	EqualityOperatorTest();
	std::cout << "EqualityOperatorTest OK" << std::endl;
	InsertTest();
	std::cout << "InsertTest OK" << std::endl;
	EraseBaseTest();
	std::cout << "EraseBaseTest OK" << std::endl;
	EraseKeyTest();
	std::cout << "EraseKeyTest OK" << std::endl;
	FindTest();
	std::cout << "Find OK" << std::endl;
	CountTest();
	std::cout << "Count OK" << std::endl;
	BoundTest();
	std::cout << "BoundTest OK" << std::endl;
	clearTest();
	std::cout << "clearTest OK" << std::endl;
	ReverseIteratorTest();
	std::cout << "ReverseIteratorTest OK" << std::endl;
	CompareTest();
	std::cout << "CompareTest OK" << std::endl;
	return 0;
}