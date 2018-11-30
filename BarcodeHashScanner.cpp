using namespace std;

#include <iostream>
#include <stdlib.h>
#include <stdint.h>

#include "CRC32.h"
#include "UPC.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "BarcodeHashScanner.h"

//Hash function
uint32_t UpcHashTable::Hash(UPC *item) {
	uint64_t c = item->GetUpcCode();
	return crc32((uint8_t *)&c, sizeof(c), 0);
}

//constructor
BarcodeHashScanner::BarcodeHashScanner(ReadFunc reader) {
	DatabaseLineReader = reader;
}

//reads and inserts UPCs into hash table
int BarcodeHashScanner::ReadDatabase() {
	UPC upc;
	int count = 0;
	while(DatabaseLineReader(&upc)) {
		table.Insert(&upc);
		count++;
	}

	return count;
}

//Searches for UPC in hash table
UPC BarcodeHashScanner::FindItem(int64_t upc) {
	UPC item;
	item.SetUpc(upc);

	if(!table.Get(&item))
		return UPC(0);

	return item;
}
