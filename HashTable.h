template<class T> class HashTable {
public:
	HashTable(int size);
	~HashTable();
	virtual uint32_t Hash(T*) = 0;
	void Insert(T*);
	bool Get(T*);

private:
	int tableSize;
	LinkedList<T> **table;
};


template<class T> HashTable<T>::HashTable(int size) {
	table = new LinkedList<T> *[size];

	int i;
	for(i = 0; i < size; i++) {
		table[i] = NULL;
	}

	tableSize = size;
}

template<class T> HashTable<T>::~HashTable() {
	int i;
	for(i = 0; i < tableSize; i++) {
		delete table[i];
	}

	delete [] table;
}

template<class T> void HashTable<T>::Insert(T *item) {
	uint32_t key = Hash(item) % tableSize;

	LinkedList<T> *list = table[key];
	if(list == NULL) {
		list = new LinkedList<T>();
		table[key] = list;
	}

	list->insertFirst(*item);
}

template<class T> bool HashTable<T>::Get(T *item) {
	uint32_t key = Hash(item) % tableSize;
	LinkedList<T> *list = table[key];

	if(list == NULL)
		return false;

	T *p = list->search(*item);
	if(p == NULL)
		return false;

	*item = *p;
	return true;
}
