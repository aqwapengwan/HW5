//Alanna Romao HW5
//CS300
//This program reads in UPC codes and descriptions from a file
//and stores them in an array, a BST, and a hash table.
//It then searches for five UPCs and returns the search time
//for each storage method.

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <iostream>

#include "UPC.h"
#include "BST.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "BarcodeBSTScanner.h"
#include "BarcodeArrayScanner.h"
#include "BarcodeHashScanner.h"

#ifdef _WIN32
#pragma warning(disable : 4996)
#define ITEMFORMAT "UPC code: %I64d\nDescription: %s\n"
#else
#define ITEMFORMAT "UPC code: %ld\nDescription: %s\n"
#endif

#define lenof(x) (sizeof(x) / sizeof(*x))

bool ReadUpcItem(UPC *item);
bool GetLine(char *buff, int size, FILE *f);
void PrintElapsedTime(clock_t start, clock_t end, const char *name);

static FILE *f;


int main(int argc, char *argv[]) {
	if(argc < 2) { //not enough command line arguments given
		printf("Usage: HW5 <upcfile>\n");
		return -1;
	}

	f = fopen(argv[1], "r");
	if(f == NULL) { //can't open file
		printf("Can't open UPC file '%s'\n", argv[1]);
		return -1;
	}

	BarcodeBSTScanner bstScan(ReadUpcItem); //reads UPCs into BST and prints out number read
	printf("Reading UPC items into BST...\n");
	int n = bstScan.ReadDatabase();
	printf("%d UPC items read into BST\n", n);

	BarcodeArrayScanner arrayScan(ReadUpcItem); //reads UPCs into array and prints out number read
	fseek(f, 0, SEEK_SET);
	printf("Reading UPC items into array...\n");
	n = arrayScan.ReadDatabase();
	printf("%d UPC items read into array\n", n);

	BarcodeHashScanner hashScan(ReadUpcItem); //reads UPCs into hash table and prints out number read
	fseek(f, 0, SEEK_SET);
	printf("Reading UPC items into hash table...\n");
	n = hashScan.ReadDatabase();
	printf("%d UPC items read into hash table\n", n);

	printf("\n\n");

	int64_t codes[] = { //UPCs being searched for
		308109481, 28000705909, 341520313073, 74213006777, 688267019500
	};

	n = lenof(codes);
	int i;
	for(i = 0; i < n; i++) {
		clock_t t0 = clock();
		UPC upc = bstScan.FindItem(codes[i]); //find UPCs in BST
		clock_t t1 = clock();

		printf(ITEMFORMAT, upc.GetUpcCode(), upc.GetDescription()); //print out UPCs and description
		PrintElapsedTime(t0, t1, "BST"); //print time took to search in BST

		t0 = clock();
		upc = arrayScan.FindItem(codes[i]); //find UPCs in array
		t1 = clock();
		PrintElapsedTime(t0, t1, "Array"); //print time took to search in array

		t0 = clock();
		upc = hashScan.FindItem(codes[i]); //find UPCs in hash table
		t1 = clock();
		PrintElapsedTime(t0, t1, "Hash"); //print time took to search in hash table

		printf("\n");
	}

	return 0;
}

//read UPC method
bool ReadUpcItem(UPC *item) {
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

//get line from file method
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
