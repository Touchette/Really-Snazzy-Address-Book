#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "AddressBook.h"
#include "Entry.h"

// Constructor
Entry::Entry() {
	/* Constructor automatically adds all default fields and initializes
	 * them to empty strings.
	 */
    fields["First Name"] = "";
    fields["Last Name"] = "";
    fields["St. Address"] = "";
    fields["Postal Code"] = "";
}

// Modifying and Adding data
void Entry::addField(std::string key, std::string value) {
	/* Adds a user-inputted field to the entry. This function
	 * is called a lot by the addressbook when making a new column,
	 * updating old entries, etc..
	 */
    fields.insert(std::pair<std::string, std::string>(key, value));
}


void Entry::changeField(std::string key, std::string value) {
	/* Changes a field's value if it exists within the map,
	 * otherwise does nothing.
	 */
	if (fields.count(key) > 0) {
		fields[key] = value;
	}
	else { }
}

void Entry::removeField(std::string key) {
	/* Simply removes a field, called a lot by the addressbook
	 * when removing columns, updating old entries, etc..
	 */
	fields.erase(key);
}

// Getting data
std::string Entry::getFieldValue(std::string key) {
	/* Gets a given key's value, used a lot when putting values
	 * into a new addressbook, etc.
	 */
    if (fields.count(key) > 0) {
        return fields[key];
	}
	else { }
}

std::vector<std::string> Entry::getKeys() {
	/* This will simply get all keys from the fields map and return
	 * them in the form of a list.
	 */
	std::vector<std::string> keys;
    std::map<std::string, std::string>::iterator it;
    for (it = fields.begin(); it != fields.end(); ++it) {
		keys.push_back(it->first);
	}
    return keys;
}

std::string Entry::format() {
	/* This is the equivalent of a python __str__() method. */
	char s[256];
	sprintf(s, "%s %s, %s",
        getFieldValue("Last Name").c_str(),
        getFieldValue("First Name").c_str(),
        getFieldValue("St. Address").c_str());
	return s;
}
