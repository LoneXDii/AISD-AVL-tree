#ifndef AVLTREE_CPP
#define AVLTREE_CPP

template <typename T>
struct Node {
	T value;
	int height;
	Node<T>* left;
	Node<T>* right;

	Node(T value) {
		this->value = value;
		this->height = 1;
		this->left = this->right = nullptr;
	}
};

template <typename T>
int height(Node<T>* root) {
	return root ? root->height : 0;
}

template <typename T>
int balanceFactor(Node<T>* root) {
	return height(root->right) - height<T>(root->left);
}

template <typename T>
void fixHeight(Node<T>* root) {
	int hl = height(root->left);
	int hr = height(root->right);
	root->height = 1 + (hl > hr ? hl : hr);
}

template <typename T>
Node<T>* rotateLeft(Node<T>* node) {
	Node<T>* p = node->right;
	node->right = p->left;
	p->left = node;
	fixHeight(node);
	fixHeight(p);
	return p;
}

template <typename T>
Node<T>* rotateRight(Node<T>* node) {
	Node<T>* p = node->left;
	node->left = p->right;
	p->right = node;
	fixHeight(node);
	fixHeight(p);
	return p;
}

template<typename T>
Node<T>* balance(Node<T>* root) {
	fixHeight(root);
	if (balanceFactor(root) == 2) {
		if (balanceFactor(root->right) < 0)
			root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	if (balanceFactor(root) == -2)
	{
		if (balanceFactor(root->left) > 0)
			root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	return root;
}


template <typename T>
Node<T>* insert(Node<T>* root, T value) {
	if (!root) 
		return new Node<T>(value);

	if (value < root->value)
		root->left = insert(root->left, value);
	else
		root->right = insert(root->right, value);

	return balance(root);
}

template <typename T>
Node<T>* findmin(Node<T>* root)
{
	return root->left ? findmin(root->left) : root;
}

template <typename T>
Node<T>* removeMin(Node<T>* root)
{
	if (root->left == 0)
		return root->right;
	root->left = removeMin(root->left);
	return balance(root);
}

template <typename T>
Node<T>* remove(Node<T>* root, T value) {
	if (!root)
		return 0;

	if (value < root->value)
		root->left = remove(root->left, value);
	else if (value > root->value)
		root->right = remove(root->right, value);
	else {
		Node<T>* l = root->left;
		Node<T>* r = root->right;
		delete root;
		if (!r) return l;
		Node<T>* min = findmin(r);
		min->right = removeMin(r);
		min->left = l;
		return balance(min);
	}
	return balance(root);
}

#endif