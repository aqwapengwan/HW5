using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <iostream>

#include "BST.h"
#include "UPC.h"
#include "BarcodeBSTScanner.h"


#ifdef _WIN32
#pragma warning(disable : 4996)
#endif


//Read and store UPCs in BST
int BarcodeBSTScanner::ReadDatabase() {
	UPC upc;

	int count = 0;
	while(DatabaseLineReader(&upc)) {
		tree.Insert(upc);
		count++;
	}

	return count;
}

//locates UPC in BST
UPC BarcodeBSTScanner::FindItem(int64_t c) {
	UPC upc(c);
	return tree.Search(upc);
}

