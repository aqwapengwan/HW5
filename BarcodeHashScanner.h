template <class T> class BarcodeHashScanner : public Scanner<T> {
public:
	typedef bool ReadFunc(T *);
	BarcodeHashScanner(HashTable<T> *hashTable) : table(hashTable) {}
	int ReadDatabase(ReadFunc *databaseLineReader);
	T *Scan(T *item);

private:
	HashTable<T> *table;
};

template <class T> int BarcodeHashScanner<T>::ReadDatabase(ReadFunc *databaseLineReader) {
	T item;
	int count = 0;
	while(databaseLineReader(&item)) {
		table->Insert(&item);
		count++;
	}

	return count;
}

template <class T> T *BarcodeHashScanner<T>::Scan(T *item) {
	if(!table->Get(item))
		return NULL;

	return item;
}
