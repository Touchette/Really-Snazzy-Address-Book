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
	/* This function adds entries to the book. It will add
	 * all user added fields to the new entry so that the table
	 * doesn't look messed up.
	 */
    if (fields.size() > 0) {
        std::list<std::string>::iterator it;
    for (it = fields.begin(); it != fields.end(); ++it) {
        entry->addField((*it), "");
        }
    }
    entries.push_back(entry);
}

void AddressBook::remove(Entry *entry) {
	/* This function removes entries from the entries list.
	 * It won't do anything if it doesn't find a matching entry.
	 */
    std::list<Entry*>::iterator it = std::find(entries.begin(), entries.end(), entry);
    if (it != entries.end()) {
        entries.erase(it);
    }
    else { }
}

void AddressBook::addColumn(std::string key) {
	/* This function is the backend equivalent to adding a
	 * new column to the UI. It adds a new field to every
	 * previous entry to ensure that everything is consistent.
	 */
    fields.push_back(key);
    std::list<Entry*>::iterator it;
    for (it = entries.begin(); it != entries.end(); ++it) {
        (*it)->addField(key, "");
    }
}

void AddressBook::removeColumn(std::string key) {
	/* This function removes columns from the entries, which
	 * is the backend equivalent to deleting a column from the UI.
	 * It removes the given field from all previous entries.
	 */
    std::list<Entry*>::iterator it;
    for (it = entries.begin(); it != entries.end(); ++it) {
        (*it)->removeField(key);
    }
}

// Printing and Getting Data
void AddressBook::printEntries() {
	/* Equivalent to going through all entries and printing them in
	 * human-readable format.
	 */
    std::list<Entry*>::iterator it;
    for (it = entries.begin(); it != entries.end(); ++it) {
        printf("%s\n", (*it)->format().c_str());
    }
}

std::list<Entry*> AddressBook::retEntries() {
	/* Returns the entry list. */
    return entries;
}
