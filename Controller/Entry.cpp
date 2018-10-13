#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <map>
#include "AddressBook.h"
#include "Entry.h"

// Constructor
Entry::Entry() {
	fields["firstname"] = "NULL";
	fields["lastname"] = "NULL";
	fields["zipcode"] = "NULL";
	fields["address"] = "NULL";
}

// Modifying and Adding data
void Entry::addField(std::string key, std::string value) {
	fields[key] = value;
}

void Entry::changeField(std::string key, std::string value) {
	if (fields.count(key) > 0) {
		printf("test");
		fields[key] = value;
	}
	else {
		printf("entry not found, adding new key\n");
		addField(key, value);
	}
}

// Getting data
std::string Entry::getFieldData(std::string key) {
	if (fields.count(key) > 0) {
		printf("found key with value \"%s\"\n", fields[key]);
		return fields[key];
	}
}

std::string Entry::format() {
	return ("%s %s,. %s\n", getFieldData("lastname"), getFieldData("firstname"), getFieldData("address"));
}