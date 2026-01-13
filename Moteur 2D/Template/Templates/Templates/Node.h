#pragma once
#include"Pair.h"
template<typename T>
class Node
{
public:
	Pair<Node<T>*, Node<T>*> chain;

	T value;

	Node(Node<T>* pre, Node<T>* post, T v) : chain({ pre, post }), value(v) {}

	void setNext(Node<T>* next) {chain.second = next }
	void setBefore(Node<T>* before) {chain.first = before }
};

