#pragma once
#include <iostream>

template <typename T>
class node {
public:
	T d;
	std::shared_ptr<node<T>> next;
	node(T _d) : d(_d) {}
};
template <typename T>
class List {
public:
	std::shared_ptr<node<T>> n;
	unsigned int length;
public:
	List() : length(0) {
		n = nullptr;
	}
	List(List<T>& list) : length(list.length) {
		n = list.n;
	}
	List<T>& operator = (List<T>& list) {
		length = list.length;
		n = list.n;
		return *this;
	}

	void add(T item) {
		if (n == nullptr) {
			n = std::make_shared<node<T>>(node<T>(item));
		}
		else
		{
			node<T>* nd = n.get();
			for (int i = 1; i < length; i++) {
				nd = (nd->next).get();
			}
			nd->next = std::make_shared<node<T>>(node<T>(item));
		}
		length++;
	}
	void removeAt(unsigned int index) {
		node<T>* nd = n.get();
		if (index < length) {
			if (index == 0) {
				n = (nd->next);
				length--;
			}
			else
			{
				for (unsigned int i = 1; i < length; i++) {
					if (i == index) {
						node<T>* nnext = (nd->next).get();
						nd->next = (nnext->next);
						length--;
						break;
					}
					nd = (nd->next).get();
				}
			}
		}
	}
	void remove(T item) {
		node<T>* nd = n.get();
		if (nd->d == item) {
			n = (nd->next);
			length--;
		}
		else
		{
			for (int i = 1; i < length; i++) {
				if (nd->next != nullptr) {
					node<T>* nnext = (nd->next).get();
					if (nnext->d == item) {
						nd->next = (nnext->next);
						length--;
						break;
					}
					nd = (nd->next).get();
				}
			}
		}
	}
	void removeAll(T item) {
		node<T>* nd = n.get();
		if (nd->d == item) {
			n = (nd->next);
			length--;
		}
		for (int i = 0; i < length; i++) {
			if (nd->next != nullptr) {
				node<T>* nnext = (nd->next).get();
				if (nnext->d == item) {
					nd->next = (nnext->next);
					length--;
				}
				nd = (nd->next).get();
			}
		}
	}
	void clear() {
		length = 0;
		n = nullptr;
	}
	T& operator[] (unsigned int index) {
		node<T>* nd = n.get();
		if (index < length) {
			for (int i = 0; i < index; i++) {
				nd = (nd->next).get();
			}
		}
		return nd->d;
	}
};