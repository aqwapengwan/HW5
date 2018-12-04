template <class T> class BarcodeBSTScanner : public Scanner<T> {
public:
	typedef bool ReadFunc(T *);
	BarcodeBSTScanner(BST<T> *bst) : tree(bst) {}
	int ReadDatabase(ReadFunc *databaseLineReader);
	T *Scan(T *item);

private:
	BST<T> *tree;
};

template <class T> T *BarcodeBSTScanner<T>::Scan(T *item) {
	*item = tree->Search(*item);
	return item;
}

template <class T> int BarcodeBSTScanner<T>::ReadDatabase(ReadFunc *databaseLineReader) {
	T item;
	int count = 0;
	while(databaseLineReader(&item)) {
		tree->Insert(item);
		count++;
	}

	return count;
}
