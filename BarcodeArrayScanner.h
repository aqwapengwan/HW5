template <class T> class BarcodeArrayScanner : public Scanner<T> {
public:
	typedef bool ReadFunc(T *);
	BarcodeArrayScanner(ArrayDatabase<T> *db) : database(db) {}
	int ReadDatabase(ReadFunc *databaseLineReader);
	T *Scan(T *item);

private:
	ArrayDatabase<T> *database;
};

template <class T> T *BarcodeArrayScanner<T>::Scan(T *item) {
	return database->Find(item);
}

template <class T> int BarcodeArrayScanner<T>::ReadDatabase(ReadFunc *databaseLineReader) {
	T item;
	while(databaseLineReader(&item)) {
		database->Insert(&item);
	}

	return database->GetCount();
}
