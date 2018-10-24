#ifndef SERIALIZER
#define SERIALIZER

#include "AddressBook.h"
#include "Entry.h"

class Serializer{
public:
	Serializer();
	~Serializer();
	void openFile(std::string file_path);
	void serializeBook(AddressBook* book);
	void serializeEntry(Entry* entry);
    void serializeToTabbedValues(AddressBook* book);
	void closeFile();
private:
	FILE* file_ptr;
};

#endif
