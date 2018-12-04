//Alanna Romao CS300 HW5
//This program takes a file with UPCs and product descriptions and stores them in an array, a BST, and a hash table.
//The program then searches for four UPCs and returns the time it took to search in the three storage methods.

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <iostream>

#include "Product.h"
#include "BST.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "ArrayDatabase.h"
#include "Scanner.h"
#include "BarcodeBSTScanner.h"
#include "BarcodeArrayScanner.h"
#include "BarcodeHashScanner.h"
#include "CRC32.h"

#ifdef _WIN32
#pragma warning(disable : 4996)
#define ITEMFORMAT "Product code: %I64d\nDescription: %s\n"
#else
#define ITEMFORMAT "Product code: %ld\nDescription: %s\n"
#endif

#define lenof(x) (sizeof(x) / sizeof(*x))

bool ReadUpcItem(Product *item);
bool GetLine(char *buff, int size, FILE *f);
void PrintElapsedTime(clock_t start, clock_t end, const char *name);

static FILE *f;

//hash table constructor
class ProductHashTable : public HashTable<Product> {
public:
	ProductHashTable(int size) : HashTable(size) {}
	uint32_t Hash(Product *);
};

//hash function
uint32_t ProductHashTable::Hash(Product *item) {
	uint64_t c = item->GetUpcCode();
	return crc32((uint8_t *)&c, sizeof(c), 0);
}

int main(int argc, char *argv[]) {
	if(argc < 2) { //check for command line argument
		printf("Usage: HW5 <upcfile>\n");
		return -1;
	}

	f = fopen(argv[1], "r");
	if(f == NULL) { //checks to open file
		printf("Can't open Product file '%s'\n", argv[1]);
		return -1;
	}

	//reads products and stores them in BST
	BST<Product> bstDatabase;
	Scanner<Product> *bstScan = new BarcodeBSTScanner<Product>(&bstDatabase);
	printf("Reading Product items into BST...\n");
	int n = bstScan->ReadDatabase(ReadUpcItem);
	printf("%d Product items read into BST\n", n);

	//reads products and stores them in array
	ArrayDatabase<Product> arrayDatabase;
	Scanner<Product> *arrayScan = new BarcodeArrayScanner<Product>(&arrayDatabase);
	fseek(f, 0, SEEK_SET);
	printf("Reading Product items into array...\n");
	n = arrayScan->ReadDatabase(ReadUpcItem);
	printf("%d Product items read into array\n", n);

	//reads products and stores them in hash table
	ProductHashTable hashDatabase(1000);
	Scanner<Product> *hashScan = new BarcodeHashScanner<Product>(&hashDatabase);
	fseek(f, 0, SEEK_SET);
	printf("Reading Product items into hash table...\n");
	n = hashScan->ReadDatabase(ReadUpcItem);
	printf("%d Product items read into hash table\n", n);

	printf("\n\n");

	//UPCs to search for
	int64_t codes[] = {
		17229115163, 74369012370, 4006408825159, 52569735756
	};

	n = lenof(codes);
	Product upc;
	int i;
	for(i = 0; i < n; i++) {
		upc.SetUpc(codes[i]);
		clock_t t0 = clock();
		Product *item = bstScan->Scan(&upc); //searches for product in BST
		clock_t t1 = clock();

		printf(ITEMFORMAT, item->GetUpcCode(), item->GetDescription());
		PrintElapsedTime(t0, t1, "BST"); //returns time took to search for product

		t0 = clock();
		item = arrayScan->Scan(&upc); //searches for product in array
		t1 = clock();
		PrintElapsedTime(t0, t1, "Array"); //returns time took to search for product in array

		t0 = clock();
		item = hashScan->Scan(&upc); //searches for product in hash table
		t1 = clock();
		PrintElapsedTime(t0, t1, "Hash"); //returns time took to search for product in hash table

		printf("\n");
	}

	return 0;
}

//reads product UPC and description from line
bool ReadUpcItem(Product *item) {
	char buff[500];
	while(true) {
		if(!GetLine(buff, sizeof(buff), f))
			return false;

		const char *p = strchr(buff, ',');
		if(p == NULL)
			continue;

		int n = strlen(p) - 1;
		if(n < 1)
			p = "[No description]";
		else
			p++;

		int64_t u = atoll(buff);
		if(u == 0)
			continue;

		item->SetUpc(u);
		item->SetDescription(p);
		return true;
	}
}

//gets line from file
bool GetLine(char *buff, int size, FILE *f) {
	do {
		buff[0] = 0;
		if(fgets(buff, size, f) == NULL)
			return false;
		char *p = strchr(buff, '\n');
		if(p != NULL)
			*p = 0;
	} while(buff[0] == 0);
	return true;
}

// Print elapsed time
void PrintElapsedTime(clock_t start, clock_t end, const char *name) {
	printf("%s elapsed time: %f ms\n", name, (end - start) * 1000.0 / CLOCKS_PER_SEC);
}
