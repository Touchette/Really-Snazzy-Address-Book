#include <stdlib.h>
#include <stdio.h>
#include <map>
#include "AddressBook.h"
#include "Entry.h"

// Constructor
Entry::Entry() {
	(*fields)["firstname"] = "NULL";
	(*fields)["lastname"] = "NULL";
	(*fields)["zipcode"] = "NULL";
	(*fields)["address"] = "NULL";
}

// Modifying and Adding data
void Entry::addField(const char* key, const char* value) {
	(*fields)[key] = value;
}

void Entry::changeField(const char* key, const char* value) {
	if (fields->count(key) > 0) {
		printf("test");
		(*fields)[key] = value;
	}
	else {
		printf("entry not found, adding new key\n");
		addField(key, value);
	}
}

// Getting data
const char* Entry::getFieldData(const char* key) {
	if (fields->count(key) > 0) {
		printf("found key with value \"%s\"\n", (*fields)[key]);
		return (*fields)[key];
	}
}

const char* Entry::format() {
	return ("%s %s,. %s\n", getFieldData("lastname"), getFieldData("firstname"), getFieldData("address"));
}