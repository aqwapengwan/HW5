template <class T> class ArrayDatabase {
public:
	ArrayDatabase();
	~ArrayDatabase();
	void Insert(T *item);
	T *Find(T *item);
	int GetCount() { return itemCount; }

private:
	T *array;
	int itemCount;
	int arraySize;
};

//constructor
template <class T> ArrayDatabase<T>::ArrayDatabase() {
	arraySize = 1000;
	array = (T *)malloc(arraySize * sizeof(T));
	itemCount = 0;
}

//destructor
template <class T> ArrayDatabase<T>::~ArrayDatabase() {
	free(array);
}

//insert item into array database
template <class T> void ArrayDatabase<T>::Insert(T *item) {
	if(itemCount >= arraySize) {
		arraySize += 10000;
		array = (T *)realloc(array, arraySize * sizeof(T));
	}

	T *x = &array[itemCount++];
	memset(x, 0, sizeof(T));
	*x = *item;
}

//search for item in array and return item if found
template <class T> T *ArrayDatabase<T>::Find(T *item) {
	int i;
	for(i = 0; i < itemCount; i++) {
		T *x = &array[i];
		if(*x == *item) {
			*item = *x;
			return item;
		}
	}

	return NULL;
}
