#ifndef DESERIALIZER
#define DESERIALIZER

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "AddressBook.h"
#include "Entry.h"

class Deserializer{
public:
	Deserializer();
	~Deserializer();
	void openFile(std::string path_string);
	AddressBook* deserializeToBook(AddressBook* starting_book = NULL);
	Entry* deserializeToEntry();
    AddressBook* deserializeTabbedValues(AddressBook* starting_book = NULL);
	void closeFile();
private:
	FILE* file_ptr;
};

#endif
