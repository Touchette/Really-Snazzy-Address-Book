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
	void openJSON(std::string path_string);
	AddressBook* deserializeToBook(AddressBook* starting_book);
	Entry* deserializeToEntry(std::string json);
	AddressBook* deserializeTabbedValues(std::string tabbed_values, AddressBook* starting_book);
	void closeJSON();
private:
	char* stringToPath(std::string path);
	FILE* file_ptr;
};

#endif
