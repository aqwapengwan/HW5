template<class T> struct node {
	T data;
	node *next;
};

template<class T> class LinkedList {
protected:
	node<T> *head;
	node<T> *tail;

public:
	LinkedList(); //constructor
	virtual node<T> *insertFirst(T&);
	virtual node<T> *insertLast(T&);
	virtual bool deleteNode(T&);
	void deleteList();
	virtual T* search(T&);
	T *iterator(node<T> **p);
	bool isEmpty();
	~LinkedList(); //destructor

protected:
	node<T> *insertAt(node<T> *p, T& item);
	void deleteNext(node<T> *p);

private:
	node<T> *searchNode(T&, node<T> **previous = NULL);
};

//constructor
template<class T> LinkedList<T>::LinkedList() {
	head = NULL;
	tail = NULL;
}

template<class T> T *LinkedList<T>::iterator(node<T> **p) {
	node<T> *q;
	if(*p == NULL)
		q = head;
	else
		q = (*p)->next;

	*p = q;
	if(q == NULL)
		return NULL;
	T *item = &q->data;
	return item;
}

template <class T> node<T> *LinkedList<T>::insertAt(node<T> *p, T& item) {
	if(p == tail) {
		return LinkedList<T>::insertLast(item);
	}

	node<T> *n = new node<T>;
	n->data = item;

	if(p == NULL) {
		n->next = head;
		head = n;
	} else {
		n->next = p->next;
		p->next = n;
	}
	return n;
}

//add to start of list
template<class T> node<T> *LinkedList<T>::insertFirst(T& item) {
	if(isEmpty())
		return insertLast(item);

	node<T> *newNode = new node<T>;
	newNode->data = item;
	newNode->next = head;
	head = newNode;
	return newNode;
}

//add to end of list
template<class T> node<T> *LinkedList<T>::insertLast(T& item) {
	node<T> *newNode = new node<T>;
	newNode->data = item;
	newNode->next = NULL;
	if(isEmpty()) {
		head = newNode;
		tail = newNode;
	} else {
		tail->next = newNode;
		tail = newNode;
	}
	return newNode;
}

//delete one
template<class T> bool LinkedList<T>::deleteNode(T& item) {
	node<T> *x;
	node<T> *p = searchNode(item, &x);
	if(p == NULL)
		return NULL;

	if(x == NULL) // Was head node
		head = p->next;
	else
		x->next = p->next;

	delete p;
	return true;
}

template<class T> void LinkedList<T>::deleteNext(node<T> *p) {
	if(p == NULL) {
		p = head;
		head = head->next;
		delete p;
	} else {
		node<T> *q = p->next;
		p->next = q->next;
		delete q;
	}
}

//delete all
template<class T> void LinkedList<T>::deleteList() {
	node<T> *p = head;
	while(p != NULL) {
		node<T> *t = p->next;
		delete p;
		p = t;
	}
	head = NULL;
	tail = NULL;
}

//search and return
template<class T> node<T>* LinkedList<T>::searchNode(T& item, node<T> **previous) {
	node<T> *p = head;
	node<T> *x = NULL;
	while(p != NULL) {
		if(p->data == item) {
			if(previous != NULL)
				*previous = x;
			return p;
		}

		x = p;
		p = p->next;
	}

	return NULL;
}

template <class T> T* LinkedList<T>::search(T& item) {
	node<T> *p = searchNode(item);
	if(p == NULL)
		return NULL;
	return &p->data;
}

//is list empty
template<class T> bool LinkedList<T>::isEmpty() {
		return head == NULL;
}

//destructor
template<class T>LinkedList<T>::~LinkedList() {
	deleteList();
}
