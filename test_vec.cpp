#include <vector>
#include "vector.hpp"
#include <assert.h>
#include <iostream>
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
	assertm(fvec1.size() == svec1.size(), "Default constructor check size");
	assertm(fvec1.capacity() == svec1.capacity(), "Default constructor check capacity");

	
	ft::vector<B> fvec2(100, B(20));
	std::vector<B> svec2(100, B(20));
	for (size_t i = 0; i < 100; ++i) {
		assertm(svec2[i].val == fvec2[i].val, "Fill Constructor check value");
	}
	assertm(fvec2.size() == svec2.size(), "fill constructor check size");
	assertm(fvec2.capacity() == svec2.capacity(), "fill constructor check capacity");

	ft::vector<A> fvec3(100); // не работает если у класса нет коструктора копирования и аргумент не передается 
	std::vector<A> svec3(100);

}


int main()
{
	TypedefTest();
	std::cout << "Typedef test OK\n";
	ConstructorTest();
	std::cout << "Constructor test OK\n";
 	return (0);
}