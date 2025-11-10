#pragma once
#include <iostream>

template <typename T>
class component {
public:
	T d;
	std::shared_ptr<component<T>> next;
	component(T _d) : d(_d) {}
};
template <typename T>
class container {
public:
	std::shared_ptr<component<T>> n;
	unsigned int length;
public:
	container() : length(0) {
		n = nullptr;
	}

	void add(T com) {
		if (n == nullptr) {
			n = std::make_shared<component<T>>(com);
		}
		else
		{
			component<T>* curr = n.get();
			for (int i = 1; i < length; i++) {
				curr = (curr->next).get();
			}
			curr->next = std::make_shared<component<T>>(com);
		}
		length++;
	}
	void removeAt(int index) {
		auto curr = n.get();
		if (index < length) {
			if (index == 0) {
				n = (curr->next);
				length--;
			}
			else
			{
				for (int i = 1; i < length; i++) {
					if (i == index) {
						auto nnext = (curr->next).get();
						curr->next = (nnext->next);
						length--;
						break;
					}
					curr = (curr->next).get();
				}
			}
		}
	}
	
	template <typename U>
	void removeAll() {
		if (!n) return;
		while (n && typeid(*n->d) == typeid(U)) {
			n = n->next;
			length--;
		}
		if (!n) return;
		auto curr = n;
		while (curr->next) {
			if (typeid(*curr->next->d) == typeid(U)) {
				curr->next = curr->next->next;
				length--;
			}
			else {
				curr = curr->next;
			}
		}
	}
	template <typename U>
	U& get() {
		auto curr = n;
		while (curr) {
			if (auto* p = dynamic_cast<U*>(curr->d.get()))
				return *p;
			curr = curr->next;
		}
		throw std::runtime_error("component not found");
	}
	void clear() {
		length = 0;
		n = nullptr;
	}
	T& operator[] (unsigned int index) {
		component<T>* curr = n.get();
		if (index < length) {
			for (int i = 0; i < index; i++) {
				curr = (curr->next).get();
			}
		}
		return curr->d;
	}
};