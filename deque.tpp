
#include "deque.hpp"

template<class ItemType>
Node<ItemType>::Node() : next(nullptr), prev(nullptr) {}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr), prev(nullptr) {}

template<typename T>
Deque<T>::Deque() : size(0), frontPtr(nullptr), backPtr(nullptr) {
}

template<typename T> 
Deque<T>::~Deque() {
	while (!isEmpty()) {
		popFront();
	}
}

template<typename T>
Deque<T>::Deque(const Deque<T>& toCopy) {
	if (toCopy.frontPtr == nullptr) {
		frontPtr = backPtr = nullptr;
		size = toCopy.size;
	}
	else {
		size = 0;
		Node<T>* copyNode = toCopy.frontPtr;
		while (copyNode != nullptr) {
			pushBack(copyNode->getItem());
			copyNode = copyNode->getNext();
		}
	}
}

template<typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& toCopy) {
	if (this == &toCopy) {
		return *this;
	}
	while (!isEmpty()) {
		popFront();
	}
	Node<T>* temp = toCopy.frontPtr;
	while (temp != nullptr) {
		pushBack(temp->getItem());
		temp = temp->getNext();
	}
	return *this;
}

template<typename T>
bool Deque<T>::isEmpty() const noexcept {
	return (size == 0);
}

template<typename T>
void Deque<T>::pushFront(const T & item) {
	if (!isEmpty()) {
		//create new Node
		Node<T>* newNode = new Node<T>(item);
		size++;
		frontPtr->setPrev(newNode);
		newNode->setNext(frontPtr);
		frontPtr = newNode;
	}
	else if (isEmpty()) {
		//create new Node
		Node<T>* newNode = new Node<T>(item);
		size++;
		frontPtr = newNode;
		backPtr = newNode;
	}
}

template<typename T>
void Deque<T>::popFront() {
	if (!isEmpty()) {
		Node<T>* temp = frontPtr->getNext();
		delete frontPtr;
		frontPtr = temp;
		size--;
	}
	else {
		throw std::runtime_error("Deque is empty when popping front");
	}
}

template<typename T>
T Deque<T>::front() const {
	if (isEmpty()) {
		throw std::runtime_error("Deque is empty when getting front");
	}
	return frontPtr->getItem();
}

template<typename T>
void Deque<T>::pushBack(const T & item) {
	if (!isEmpty()) {
		Node<T>* newNode = new Node<T>(item);
		size++;
		backPtr->setNext(newNode);
		newNode->setPrev(backPtr);
		backPtr = newNode;
	}
	else if(isEmpty()) {
		//create new Node
		Node<T>* newNode = new Node<T>(item);
		size++;
		frontPtr = newNode;
		backPtr = newNode;
	}
}

template<typename T>
void Deque<T>::popBack() {
	if (!isEmpty()) {
		Node<T>* temp = backPtr->getPrev();
		delete backPtr;
		backPtr = temp;
		size--;
	}
	else {
		throw std::runtime_error("Deque is empty when popping back");
	}
}

template<typename T>
T Deque<T>::back() const {
	if (isEmpty()) {
		throw std::runtime_error("Deque is empty when getting back");
	}
	return backPtr->getItem();
}