class Product {
public:
	Product() { Init(); }
	Product(int64_t code) { upc = code; description = NULL; }
	Product(int64_t code, char *desc);
	Product(const Product&);
	~Product() { delete description; }

	void Init() { description = NULL; upc = 0; }
	void SetUpc(int64_t c) { upc = c; }
	void SetDescription(const char *desc);
	int64_t GetUpcCode() { return upc; }
	const char *GetDescription() { return description; }
	void operator=(const Product& o);
	bool operator==(Product& o) { return upc == o.upc; }
	bool operator<(Product& o) { return upc < o.upc; }
	bool operator>(Product& o) { return upc > o.upc; }
	friend ostream& operator<<(ostream& ob, Product&);

private:
	int64_t upc;
	char *description;
};
