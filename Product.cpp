using namespace std;

#include <stdint.h>
#include <string.h>
#include <iostream>

#include "Product.h"

//constructor
Product::Product(int64_t code, char *desc) {
	upc = code;
	int n = strlen(desc) + 1;
	description = new char[n];
	memcpy(description, desc, n);
}

//copy constructor
Product::Product(const Product &o) {
	description = NULL;
	*this = o;
}

//sets product description
void Product::SetDescription(const char *desc) {
	int n = strlen(desc) + 1;
	description = new char[n];
	memcpy(description, desc, n);
}

//assignment operator
void Product::operator=(const Product& o) {
	delete description;

	upc = o.upc;
	if(o.description == NULL) {
		description = NULL;
		return;
	}

	SetDescription(o.description);
}

//out stream operator
ostream& operator<<(ostream& ob, Product& item) {
	ob << item.upc << ' ' << item.description << endl;
	return ob;
}
