#ifndef DEQUE_HPP
#define DEQUE_HPP

template<class ItemType>
class Node {
	protected:
		ItemType item;
		Node<ItemType>* next;
		Node<ItemType>* prev;
	public:
		Node();
		Node(const ItemType& anItem);
		void setItem(const ItemType &value) { item = value; }
		void setNext(Node<ItemType>* nextNodePtr) { next = nextNodePtr; }
		void setPrev(Node<ItemType>* prevNodePtr) { prev = prevNodePtr; }
		Node<ItemType>* getNext() const { return next; }
		Node<ItemType>* getPrev() const { return prev; }
		ItemType getItem() const { return item; }
};

template <typename T>
class Deque {
	protected:
		Node<T>* frontPtr;
		Node<T>* backPtr;
		int size;
	public:
		Deque();
		~Deque();
		Deque(const Deque& toCopy);
		Deque& operator=(const Deque& toCopy);
		bool isEmpty() const noexcept;
		void pushFront(const T & item);
		void popFront();
		T front() const;
		void pushBack(const T & item);
		void popBack();
		T back() const;
};

#include "deque.tpp"
#endif