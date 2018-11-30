class UpcHashTable : public HashTable<UPC> {
public:
	UpcHashTable(int size) : HashTable(size) {}
	uint32_t Hash(UPC *);
};


class BarcodeHashScanner {
public:
	typedef bool ReadFunc(UPC *);
	BarcodeHashScanner(ReadFunc reader);
	int ReadDatabase();
	UPC FindItem(int64_t upc);

private:
	ReadFunc *DatabaseLineReader;
	UpcHashTable table = UpcHashTable(1000);
};
