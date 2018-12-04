template <class T> class Scanner {
public:
	typedef bool ReadFunc(T *);
	virtual ~Scanner() {}
	virtual int ReadDatabase(ReadFunc *databaseLineReader) = 0;
	virtual T *Scan(T *item) = 0;
};
