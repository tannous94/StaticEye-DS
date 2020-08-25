#ifndef DIC_LIST_H_
#define DIC_LIST_H_
#include <iostream>

template<class Key, class Value>
class List {
public:
	class Node {
	public:
		Key key;
		Value value;
		Node* next;
		Node* prev;

	public:
		friend class List;
		Node(Key key_t, Value value_t) : key(key_t), value(value_t), next(NULL), prev(NULL) {

		}

		~Node() {

		}
	};

	Node* head;
	int size;

public:
	List() : head(NULL), size(0) {

	}

	~List() {
		Node* to_delete = head;
		for (int i = 0; i < size; i++) {
			to_delete = head;
			head = head->next;
			//if (to_delete->value != NULL)
			//	delete to_delete->value;
			delete to_delete;
		}
	}

	int getSize() const {
		return size;
	}

	bool isEmpty() {
		if (size > 0)
			return false;
		return true;
	}

	Key getHeadKey() {
		return head->key;
	}

	Node* Find(Key k) {
		for (Node* iter = head; iter != NULL; iter = iter->next) {
			if (iter->key == k) {
				return iter;
			}
		}
		return NULL;
	}

	bool Insert(Key k, Value v) {
		if (Find(k) != NULL)
			return false;

		Node* new_node = new Node(k, v);
		if (head != NULL) {
			head->prev = new_node;
		}
		new_node->next = head;
		head = new_node;
		size++;
		return true;
	}

	bool Delete(Key k) {
		if (Find(k) == NULL)
			return false;

		Node* to_delete = head;
		for (int i = 0; i < size; i++) {
			if (to_delete->key == k) {
				if (to_delete == head) {
					head = head->next;
					if (head != NULL)
						head->prev = NULL;
					delete to_delete;
					size--;
					return true;
				}
				if (i == size - 1) {
					Node* prev_t = to_delete->prev;
					prev_t->next = NULL;
					delete to_delete;
					size--;
					return true;
				}
				else {
					Node* next_t = to_delete->next;
					Node* prev_t = to_delete->prev;
					prev_t->next = next_t;
					next_t->prev = prev_t;
					delete to_delete;
					size--;
					return true;
				}
			}
			to_delete = to_delete->next;
		}
		return false;
	}

	bool DeleteByPointer(Node* node) {
		return Delete(node->key);
	}
};

#endif /* DIC_LIST_H_ */
