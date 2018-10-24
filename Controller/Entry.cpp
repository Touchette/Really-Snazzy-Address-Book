#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <map>
#include "AddressBook.h"
#include "Entry.h"

// Constructor
Entry::Entry() {
	fields["firstname"] = "";
	fields["lastname"] = "";
	fields["zipcode"] = "";
	fields["address"] = "";
}

// Modifying and Adding data
void Entry::addField(std::string key, std::string value) {
	fields[key] = value;
}

void Entry::changeField(std::string key, std::string value) {
	if (fields.count(key) > 0) {
		fields[key] = value;
	}
	else {
		printf("entry not found, adding new key\n");
	}
}

void Entry::removeField(std::string key) {
	fields.erase(key);
}

// Getting data
std::string Entry::getFieldValue(std::string key) {
	if (fields.count(key) > 0) {
		return fields[key];
	}
	else {
		return NULL;
	}
}

std::string Entry::format() {
	char s[256];
	sprintf(s, "%s %s, %s",
		getFieldValue("lastname").c_str(),
		getFieldValue("firstname").c_str(),
		getFieldValue("address").c_str());
	return s;
}
