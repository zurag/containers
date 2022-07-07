#include <vector>
#include "vector.hpp"
#include <iterator>
#include <assert.h>
#include <iostream>
#include <typeinfo>
#define assertm(exp, msg) assert(((void)msg, exp))


//typedef need add test "typydef iterator"
void TypedefTest() {
	assertm(typeid(std::vector<int>::value_type) == typeid(ft::vector<int>::value_type), "value_type");
	assertm(typeid(std::vector<char *>::value_type) != typeid(ft::vector<int>::value_type), "value_type differents type");
	assertm(typeid(std::vector<int>::allocator_type) == typeid(ft::vector<int>::allocator_type), "allocator_type");
	assertm(typeid(std::vector<void *>::allocator_type) != typeid(ft::vector<int>::allocator_type), "allocator_type differents type");
	assertm(typeid(std::vector<int>::reference) == typeid(ft::vector<int>::reference), "reference");
	assertm(typeid(std::vector<void *>::reference) != typeid(ft::vector<int>::reference), "reference differents type");
	assertm(typeid(std::vector<int>::const_reference) == typeid(ft::vector<int>::const_reference), "const_reference");
	assertm(typeid(std::vector<void *>::const_reference) != typeid(ft::vector<int>::const_reference), "const_reference differents type");
	assertm(typeid(std::vector<int>::size_type) == typeid(ft::vector<int>::size_type), "size_type");
	assertm(typeid(std::vector<int>::difference_type) == typeid(ft::vector<int>::difference_type), "difference_type");
}


class A {
private:
	A(const A &a){val = a.val;}
public:
	int val;
	A() {
		val = 1;
	}
	A(int value) {
		val = value;
	}
	~A() {

	}
};

class B {
public:
	int val;
	B() {
		val = 2;
	}
	B(const B &b){ val = b.val;}
	B(int value) {
		val = value;
	}
	~B() {}
};


void ConstructorTest() {

	ft::vector<int> fvec1;
	std::vector<int> svec1;
	assertm(fvec1.empty() == svec1.empty(), "Default constructor check empty");
	assertm(fvec1.size() == svec1.size(), "Default constructor check size");
	assertm(fvec1.capacity() == svec1.capacity(), "Default constructor check capacity");

	ft::vector<B> fvec2(100, B(20));
	std::vector<B> svec2(100, B(20));

	for (size_t i = 0; i < 100; ++i) {
		assertm(svec2[i].val == fvec2[i].val, "Fill Constructor check value");
	}
	assertm(fvec2.size() == svec2.size(), "fill constructor check size");
	assertm(fvec2.empty() == svec2.empty(), "fill constructor check empty");
	assertm(fvec2.max_size() == svec2.max_size(), "fill constructor check max size");
	assertm(fvec2.capacity() == svec2.capacity(), "fill constructor check capacity");
	
	ft::vector<A> fvec3(100);
	std::vector<A> svec3(100);

	ft::vector<B> fvec4(fvec2);
	std::vector<B> svec4(svec2);
	
	for (size_t i = 0; i < 100; ++i) {
		assertm(svec4[i].val == fvec4[i].val, "Copy Constructor check value");
	}
	assertm(fvec4.size() == svec4.size(), "Copy Constructor check size");
	assertm(fvec4.max_size() == svec4.max_size(), "Copy Constructor check max size");
	assertm(fvec4.capacity() == svec4.capacity(), "Copy Constructor check capacity");
	
	ft::vector<B> fvec5(100, B(30));
	std::vector<B> svec5(100, B(30));
	fvec5 = fvec4;
	svec5 = svec4;
	for (size_t i = 0; i < 100; ++i) {

		assertm(svec5[i].val == fvec5[i].val, "Operator = check value");
	}
	assertm(fvec5.size() == svec5.size(), "Operator = check size");
	assertm(fvec5.max_size() == svec5.max_size(), "Operator =  check max size");
	assertm(fvec5.capacity() == svec5.capacity(), "Operator = check capacity");
}


void ResizeTest() {
	ft::vector<int> fvec(10, 1);
	std::vector<int> svec(10, 1);
	fvec.resize(22, 2);
	svec.resize(22, 2);
	for (int i = 0; i < svec.size(); ++i) {
		assertm(svec[i] == fvec[i], "Resize check value");
	}
	assertm(fvec.size() == svec.size(), "Resize check size");
	assertm(fvec.max_size() == svec.max_size(), "Resize check max size");
	assertm(fvec.capacity() == svec.capacity(), "Resize check capacity");
	
	ft::vector<int> fvec2(10, 1);
	std::vector<int> svec2(10, 1);
	fvec2.resize(2, 2);
	svec2.resize(2, 2);
	for (int i = 0; i < svec2.size(); ++i) {
		assertm(svec2[i] == fvec2[i], "Resize check value");
	}
	assertm(fvec2.size() == svec2.size(), "Resize check size");
	assertm(fvec2.max_size() == svec2.max_size(), "Resize check max size");
	assertm(fvec2.capacity() == svec2.capacity(), "Resize check capacity");
	//  std::cout << fvec2.size() << " " << svec2.size() << '\n';
}


void ReserveTest() {
	std::vector<int> svec;
	ft::vector<int> fvec;
	assertm(fvec.size() == svec.size(), "Reserve check size");
	svec.reserve(1);
	assertm(fvec.size() == svec.size(), "Reserve check size");
	svec.reserve(10);
	assertm(fvec.size() == svec.size(), "Reserve check size");
	svec.reserve(7);
	assertm(fvec.size() == svec.size(), "Reserve check size");
	svec.reserve(14);
	assertm(fvec.size() == svec.size(), "Reserve check size");

	std::vector<int> svec2(2, 1);
	ft::vector<int> fvec2(2, 1);
	svec.reserve(14);
	fvec.reserve(14);
	for (size_t i = 0; i < svec2.size();  ++i) {
		assertm(fvec2[i] == svec2[i], "Reserve check old value");
	}
	assertm(fvec.size() == svec.size(), "Reserve check size");
}


void AtTest() {
	std::vector<int> svec(10);
	svec.reserve(30);
	try {
		svec.at(10)=100;      // vector::at throws an out-of-range
	}
	catch (const std::out_of_range& oor) {
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	}
	ft::vector<int> fvec(10);
	try {
		fvec.at(20)=100;
	}
	catch (const std::out_of_range& oor) {
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	}


}

void FrontBackTest(){
	std::vector<int> svec(10, 1);
	ft::vector<int> fvec(10, 1);
	svec.push_back(2);
	fvec.push_back(2);
	assertm(fvec.front() == svec.front(), "Front check value");
	assertm(fvec.back() == svec.back(), "Back check value");
	
}

void Push_backTest()
{
	std::vector<int> svec;
	std::vector<int> fvec;
	for (size_t i = 0; i < 10; ++ i) {
		svec.push_back(i);
	}
	for (size_t i = 0; i < 10; ++ i) {
		fvec.push_back(i);
	}
	for (size_t i = 0; i < svec.size();  ++i) {
		assertm(fvec[i] == svec[i], "Push_back check value");
	}
	assertm(fvec.size() == svec.size(), "Push_back check size");
	assertm(fvec.capacity() == svec.capacity(), "Push_back check size");

	std::vector<int> svec2(1);
	std::vector<int> fvec2(1);
	for (size_t i = 0; i < 10; ++ i) {
		svec2.push_back(i);
	}
	for (size_t i = 0; i < 10; ++ i) {
		fvec2.push_back(i);
	}
	for (size_t i = 0; i < svec2.size();  ++i) {
		assertm(fvec2[i] == svec2[i], "Push_back check value");
	}
	assertm(fvec2.size() == svec2.size(), "Push_back check size");
	assertm(fvec2.capacity() == svec2.capacity(), "Push_back check size");
}

void AssignTest() {
	std::vector<int> svec;
	ft::vector<int> fvec;
	std::vector<int> tmp;
	for (size_t i = 0; i < 10; i++)
	{
		tmp.push_back(i * 10);
	}
	svec.assign(tmp.begin(), tmp.end());
	fvec.assign(tmp.begin(), tmp.end());

	for (size_t i = 0; i < svec.size(); ++i) {
		assertm(fvec[i] == svec[i], "Assign Iterator check value");
	}

	std::vector<int> svec2(12, 2);
	ft::vector<int> fvec2(12, 2);
	svec2.assign(13, 1);
	fvec2.assign(13, 1);

	for (size_t i = 0; i < svec2.size(); ++i) {
		assertm(fvec2[i] == svec2[i], "Assign fill check value");
		// std::cout << svec2[i] << '\n';
		// std::cout << fvec2[i] << '\n';
	}
	// assertm(fvec2.size() == svec2.size(), "Assign fill check size");
	// assertm(fvec2.capacity() == svec2.capacity(), "Assign fill check size");
	// std::cout << svec2.size() << ' ' << svec2.capacity() << '\n';
	// std::cout << fvec2.size() << ' ' << fvec2.capacity() << '\n';

	int myints[] = {1776,7,4};
	std::vector<int> svec3;
	ft::vector<int> fvec3;
	svec3.assign(myints,myints+3);
	fvec3.assign(myints,myints+3);
	for (size_t i = 0; i < svec3.size(); ++i) {
		assertm(fvec3[i] == svec3[i], "Assign fill check value");
		// std::cout << svec3[i] << '\n';
		// std::cout << fvec3[i] << '\n';
	}
}


void IteratorTest() {
	std::vector<int> svec(10, 2);
	ft::vector<int> fvec(10, 2);
	std::vector<int>::iterator sit = svec.begin();
	ft::vector<int>::iterator fit = fvec.begin();
	for (; sit != svec.end(); ++sit) {
		std::cout << *sit << ' ';
	}
	std::cout << std::endl;
	for (; fit != fvec.end(); ++fit) {
		std::cout << *fit << ' ';
	}
	std::cout << std::endl;
	
	std::vector<int> svec2(svec.begin(), svec.end());
	ft::vector<int> fvec2(fvec.begin(), fvec.end());
	std::vector<int>::iterator sit2 = svec2.begin();
	ft::vector<int>::iterator fit2 = fvec2.begin();
	for (; sit2 != svec2.end(); ++sit2) {
		std::cout << *sit2 << ' ';
	}
	std::cout << std::endl;	
	for (; fit2 != fvec2.end(); ++fit2) {
		std::cout << *fit2 << ' ';
	}
	std::cout << std::endl;

}


void EraseTest() {
	std::vector<int> svec;
	ft::vector<int> fvec;
	
	for (int i = 0; i < 10; ++i) {
		svec.push_back(i);
		fvec.push_back(i);
	}
	std::vector<int>::iterator it = svec.erase(svec.begin());
	std::cout << *it << std::endl;
	ft::vector<int>::iterator it2 = fvec.erase(fvec.begin());
	std::cout << *it2 << std::endl;
	for (size_t i = 0; i < svec.size(); ++i) {
		std::cout << svec[i] << ' ';
	}
	std::cout << std::endl;
	for (size_t i = 0; i < fvec.size(); ++i) {
		std::cout << fvec[i] << ' ';
	}
	std::cout << std::endl;


	for (int i = 10; i < 20; ++i) {
		svec.push_back(i);
		fvec.push_back(i);
	}

	it = svec.erase(svec.begin() + 5, svec.begin() + 10);
	std::cout << *it << std::endl;
	it2 = fvec.erase(fvec.begin() + 5, fvec.begin() + 10);
	std::cout << *it2 << std::endl;
	for (size_t i = 0; i < svec.size(); ++i) {
		std::cout << svec[i] << ' ';
	}
	std::cout << std::endl;
	for (size_t i = 0; i < fvec.size(); ++i) {
		std::cout << fvec[i] << ' ';
	}
	std::cout << std::endl;
	it = svec.erase(svec.begin() + 5, svec.end());
	std::cout << *it << std::endl;
	it2 = fvec.erase(fvec.begin() + 5, fvec.end());
	std::cout << *it2 << std::endl;
}


void InsertTest() {
	std::vector<int> svec;
	ft::vector<int> fvec;
	
	svec.insert(svec.begin(), 0);
	fvec.insert(fvec.begin(), 0);
	std::cout << svec.capacity() << ' ' << svec.size() << std::endl;
	std::cout << fvec.capacity() << ' ' << fvec.size() << std::endl;
	for (int i = 1; i < 10; ++i) {
		svec.push_back(i);
		fvec.push_back(i);
	}

	std::vector<int>::iterator it = svec.insert(svec.begin() + 5, 404);
	ft::vector<int>::iterator it2 = fvec.insert(fvec.begin() + 5, 404);
	
	std::cout << *it << ' ' << *it2 << std::endl;
	for (size_t i = 0; i < svec.size(); ++i) {
		std::cout << svec[i] << ' ';
	}
	std::cout << std::endl;
	for (size_t i = 0; i < fvec.size(); ++i) {
		std::cout << fvec[i] << ' ';
	}
	std::cout << std::endl;

	svec.insert(svec.begin() + 5, 10, 55);
	fvec.insert(fvec.begin() + 5, 10, 55);
	std::cout << *it << ' ' << *it2 << std::endl;
	for (size_t i = 0; i < svec.size(); ++i) {
		std::cout << svec[i] << ' ';
	}
	std::cout << std::endl;
	for (size_t i = 0; i < fvec.size(); ++i) {
		std::cout << fvec[i] << ' ';
	}
	std::cout << std::endl;

}

int main()
{
	// func();
	// int *a = 0;
	// TypedefTest();
	// std::cout << "Typedef test OK\n";
	// ConstructorTest();
	// std::cout << "Constructor test OK\n";
	// ResizeTest();
	// std::cout << "Resize test OK\n";
	// ReserveTest();
	// std::cout << "Reserve test OK\n";
	// AtTest();
	// std::cout << "at test OK\n";
	// FrontBackTest();
	// std::cout << "FrontBackTest OK\n";
	// Push_backTest();
	// std::cout << "Push_backTest OK\n";
	// AssignTest();
	// std::cout << "AssignTest OK\n";
	// IteratorTest();
	// std::cout << "IteratorTest OK\n";
	// EraseTest();
	InsertTest();
	// std::cout << "InsertTest OK\n";
	
 	return (0);
}