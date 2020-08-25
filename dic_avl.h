#ifndef DIC_AVL_H_
#define DIC_AVL_H_
#include <iostream>

template<class Key, class Value>
class Avl {
public:
	class Node {
	public:
		Key key;
		Value value;
		Node* right;
		Node* left;

	public:
		friend class Avl;
		Node(Key key_t, Value value_t) : key(key_t), value(value_t), right(NULL), left(NULL) { //added new Value()

		}

		~Node() {

		}
	};

	Node* root;
	int size;
	int segments;

	Node* avlFind(Node* root, Key k) {
		if (!root)
			return NULL;

		if (root->key > k)
			return avlFind(root->left, k);
		if (root->key < k)
			return avlFind(root->right, k);
		return root;
	}

	// Maximum between a and b
	int max(int a, int b) {
		if (a > b)
			return a;
		return b;
	}

	// Returns node's height
	int nodeHeight(Node* node) {
		int h = 0;
		if (node) {
			int l_height = nodeHeight(node->left);
			int r_height = nodeHeight(node->right);
			int max_height = max(l_height, r_height);
			h = max_height + 1;
		}
		return h;
	}

	// Returns node's balance factor
	int bFactor(Node* node) {
		int l_height = nodeHeight(node->left);
		int r_height = nodeHeight(node->right);
		int b_factor = l_height - r_height;
		return b_factor;
	}

	Node* rotationLL(Node* p) {
		Node* temp;
		temp = p->left;
		p->left = temp->right;
		temp->right = p;
		return temp;
	}

	Node* rotationRR(Node* p) {
		Node* temp;
		temp = p->right;
		p->right = temp->left;
		temp->left = p;
		return temp;
	}

	Node* rotationLR(Node* p) {
		Node* temp;
		temp = p->left;
		p->left = rotationRR(temp);
		return rotationLL(p);
	}

	Node* rotationRL(Node* p) {
		Node* temp;
		temp = p->right;
		p->right = rotationLL(temp);
		return rotationRR(p);
	}

	Node* avlBalance(Node* node) {
		int b_factor = bFactor(node);

		if (b_factor > 1) {
			if (bFactor(node->left) >= 0)
				node = rotationLL(node);
			else
				node = rotationLR(node);
		}
		if (b_factor < -1) {
			if (bFactor(node->right) <= 0)
				node = rotationRR(node);
			else
				node = rotationRL(node);
		}

		return node;
	}

	Node* avlInsert(Node* root, Key k, Value v) {
		if (!root) {
			root = new Node(k, v);
			//size++;
			return root;
		}

		if (root->key > k) {
			root->left = avlInsert(root->left, k, v);
			root = avlBalance(root);
		}

		if (root->key < k) {
			root->right = avlInsert(root->right, k, v);
			root = avlBalance(root);
		}

		return root;
	}

	Node* getInorderSuccessor(Node* node) {
		Node* current = node;
		while (current->left != NULL)
			current = current->left;
		return current;
	}

	Node* avlDelete(Node* root, Key k) { // decrease size
		if (!root)
			return root;
		if (root->key > k) { // Searches for the node
			root->left = avlDelete(root->left, k);
			root = avlBalance(root);
		}
		else if (root->key < k) {
			root->right = avlDelete(root->right, k);
			root = avlBalance(root);
		}
		else {
			if (root->left == NULL) { // if it has one child
				Node* temp = root->right;
				delete root;
				return temp;
			}
			else if (root->right == NULL) { // if it has no childs
				Node* temp = root->left;
				delete root;
				return temp;
			}
			// if it has two childs
			Node* temp = getInorderSuccessor(root->right);
			root->key = temp->key;
			root->value = temp->value;
			root->right = avlDelete(root->right, temp->key);
			root = avlBalance(root);
		}
		return root;
	}

public:
	Avl(int n) : root(NULL), size(0), segments(n) {

	}

	~Avl() {
		avlDestroy(this->root);
	}

	void avlDestroy(Node* root) {
		if (!root)
			return;

		avlDestroy(root->left);
		avlDestroy(root->right);

		delete root;
	}

	int getSize() const {
		return size;
	}

	Node* Find(Key k) {
		return avlFind(root, k);
	}

	Node* Insert(Key k, Value v) { // maybe should return null instead of root in case it finds the root ...
		if (Find(k) != NULL)
			return root;
		root = avlInsert(root, k, v);
		size++;
		return root;
	}

	Node* Delete(Key k) { // same as insert
		if (Find(k) == NULL)
			return root;
		root = avlDelete(root, k);
		size--;
		return root;
	}

	Node* DeleteByPointer(Node* node) {
		return Delete(node->key);
	}
};

#endif /* DIC_AVL_H_ */
