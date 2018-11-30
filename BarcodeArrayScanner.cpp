using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <iostream>

#include "BST.h"
#include "UPC.h"
#include "BarcodeArrayScanner.h"

//Constructor
BarcodeArrayScanner::BarcodeArrayScanner(ReadFunc reader) {
	DatabaseLineReader = reader;
	array = NULL;
	count = 0;
}

//Reads and stores barcodes in array
int BarcodeArrayScanner::ReadDatabase() {
	int size = 10000;
	if(array == NULL) {
		array = (UPC *)malloc(size * sizeof(UPC));
	}

	UPC upc;
	while(DatabaseLineReader(&upc)) {
		if(count >= size) {
			size += 100000;
			array = (UPC *)realloc(array, size * sizeof(UPC));
		}

		array[count].Init();
		array[count] = upc;
		count++;
	}

	return count;
}

//searches and finds UPC in array
UPC BarcodeArrayScanner::FindItem(int64_t c) {
	int i;
	for(i = 0; i < count; i++) {
		UPC *upc = &array[i];
		if(upc->GetUpcCode() == c) {
			return *upc;
		}
	}

	return UPC(0);
}
