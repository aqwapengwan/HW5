template<class T> struct Node {
	T data;
	Node<T>* lessThan;
	Node<T>* greaterThan;
};

template<class T> class BST {
	Node<T>* root;

public:
	BST();
	~BST();
	void PrintInOrder();
	void PrintPreOrder();
	void PrintPostOrder();
	void Insert(T& item);
	T Search(T& item);
	T FindMax(T& e);
	T FindMin(T& e);
	int Maximum(int a, int b);
	int Height();
	void DeleteNode(T& item);

private:
	void PrintInOrder(Node<T>* p);
	void PrintPreOrder(Node<T>*p);
	void PrintPostOrder(Node<T>*p);
	void Insert(T& item, Node<T>*&p);
	Node<T>* Search(T& item, Node<T>* p);
	T FindMax(T& e, Node<T>* p);
	T FindMin(T& e, Node<T>* p);
	int Height(Node<T>* p);
	void DeleteNode(T& item, Node<T> *&p);
	void DeleteTree(Node<T>*p);
};

//constructor
template<class T> BST<T>::BST() {
	root = NULL;
}

//destructor
template<class T> BST<T>::~BST() {
	DeleteTree(root);
	root = NULL;
}

//public print in-order
template<class T> void BST<T>::PrintInOrder() {
	PrintInOrder(root);
}

//private print in-order
template<class T> void BST<T>::PrintInOrder(Node<T>* p) {
	if(p != NULL) {
		PrintInOrder(p->lessThan);
		cout << p->data << " ";
		PrintInOrder(p->greaterThan);
	}
}

//public print pre-order
template<class T> void BST<T>::PrintPreOrder() {
	PrintPreOrder(root);
}

//private print pre-order
template<class T> void BST<T>::PrintPreOrder(Node<T>*p) {
	if(p != NULL) {
		cout << p->data << " ";
		PrintPreOrder(p->lessThan);
		PrintPreOrder(p->greaterThan);
	}
}

//public print post-order
template<class T> void BST<T>::PrintPostOrder() {
	PrintPostOrder(root);
}

//public print post-order
template<class T> void BST<T>::PrintPostOrder(Node<T>*p) {
	if(p != NULL) {
		PrintPostOrder(p->lessThan);
		PrintPostOrder(p->greaterThan);
		cout << p->data << " ";
	}
}

//public insert
template<class T> void BST<T>::Insert(T& item) {
	Insert(item, root);
}

//private insert
template<class T> void BST<T>::Insert(T& item, Node<T>*&p) {
	if(p == NULL) {
		p = new Node<T>;
		p->data = item;
		p->lessThan = NULL;
		p->greaterThan = NULL;
	} else if(item < p->data) {
		Insert(item, p->lessThan);
	} else {
		Insert(item, p->greaterThan);
	}
}

//public search
template<class T> T BST<T>::Search(T& item) {
	Node<T>* n = Search(item, root);
	if(n != NULL)
		return n->data;

	return item;
}

//private search
template<class T> Node<T>* BST<T>::Search(T& item, Node<T>*p) {
	if(p == NULL)
		return NULL;

	if(item < p->data)
		return Search(item, p->lessThan);
	else if(item > p->data)
		return Search(item, p->greaterThan);
	return p;
}

//maximum for finding height
template<class T> int BST<T>::Maximum(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}

//find maximum node public
template<class T> T BST<T>::FindMax(T& e) {
	return FindMax(e, root);
}

//find maximum node private
template<class T> T BST<T>::FindMax(T& e, Node<T> *p) {
	if(p == NULL)
		return e;

	if(p->greaterThan == NULL)
		return p->data;
	else
		return FindMax(e, p->greaterThan);
}

//find minimum node public
template<class T> T BST<T>::FindMin(T& e) {
	return FindMin(e, root);
}

//find minimum node private
template<class T> T BST<T>::FindMin(T& e, Node<T> * p) {
	if(p == NULL)
		return e;

	if(p->lessThan == NULL)
		return p->data;
	else
		return FindMin(e, p->lessThan);
}

//find height of tree public
template<class T> int BST<T>::Height() {
	return Height(root);
}

//find height of tree private
template<class T> int BST<T>::Height(Node<T>*p) {
	if(p == NULL)
		return -1;

	return 1 + Maximum(Height(p->lessThan), Height(p->greaterThan));
}

//delete node public
template<class T> void BST<T>::DeleteNode(T& item) {
	DeleteNode(item, root, NULL);
}

//delete node private
template<class T> void BST<T>::DeleteNode(T& item, Node<T> *&p) {
	//item not found, do nothing
	if(p == NULL)
		return;
	else if(item < p->data)	//item is on the lessThan subtree
		deletenode(p->lessThan, item);
	else if(item > p->data)	//item is on the greaterThan subtree
		deletenode(p->greaterThan, item);
	else {//item is equal to data,  it is found
		if(p->lessThan != NULL && p->greaterThan != NULL) {// with two children
			int e = -1;
			p->data = findMax(p->lessThan, e);
			deletenode(p->lessThan, p->data);
		} else {
			Node<T>* old = p;
			if(p->lessThan != NULL)
				p = p->lessThan;
			else
				p = p->greaterThan;

			delete old;
		}
	}
}

//delete tree
template<class T> void BST<T>::DeleteTree(Node<T>*p) {
	if(p != NULL) {
		DeleteTree(p->lessThan);
		DeleteTree(p->greaterThan);
		delete p;
	}
}
