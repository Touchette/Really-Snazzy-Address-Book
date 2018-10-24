#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <list>
#include "AddressBook.h"
#include "Entry.h"

// Entry, Removal
void AddressBook::add(Entry *entry) {
    if (fields.size() > 0) {
        std::list<std::string>::iterator it;
	for (it = fields.begin(); it != fields.end(); ++it) {
	    entry->addField((*it), "");
	}
    }
    printf("adding entry with last name \"%s\"\n", entry->getFieldValue("lastname").c_str());
    entries.push_back(entry);
}

void AddressBook::remove(Entry *entry) {
    int i;
    std::list<Entry*>::iterator it = std::find(entries.begin(), entries.end(), entry);
    if (it != entries.end()) {
        printf("removing entry with last name \"%s\"\n", entry->getFieldValue("lastname").c_str());
        entries.erase(it);
    }
    else {
        printf("entry not found\n");
    }
}

void AddressBook::addColumn(std::string key) {
	fields.push_back(key);
	std::list<Entry*>::iterator it;
	for (it = entries.begin(); it != entries.end(); ++it) {
		(*it)->addField(key, "");
	}
}

void AddressBook::removeColumn(std::string key) {
	std::list<Entry*>::iterator it;
	for (it = entries.begin(); it != entries.end(); ++it) {
		(*it)->removeField(key);
	}
}

// Printing and Serializing
void AddressBook::printEntries() {
    std::list<Entry*>::iterator it = entries.begin();
    for (it; it != entries.end(); ++it) {
        printf("%s\n", (*it)->format().c_str());
    }
}

std::list<Entry*> AddressBook::retEntries() {
    return entries;
}
