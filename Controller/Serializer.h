#ifndef SERIALIZER
#define SERIALIZER

#include "AddressBook.h"
#include "Entry.h"
#include <string.h>

class Serializer{
public:
	Serializer();
	~Serializer();
	void openFile(std::string file_path);
	void serializeBook(AddressBook* book);
	void serializeEntry(Entry* entry);
	void closeFile();
private:
	char* stringToPath(std::string path);
	FILE* file_ptr;
};

#endif
