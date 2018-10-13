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
    printf("adding entry with last name \"%s\"\n", entry->getFieldData("lastname").c_str());
    entries.push_back(entry);
}

void AddressBook::remove(Entry *entry) {
    int i;
    std::list<Entry*>::iterator it = std::find(entries.begin(), entries.end(), entry);
    if (it != entries.end()) {
        printf("removing entry with last name \"%s\"\n", entry->getFieldData("lastname").c_str());
        entries.erase(it);
    }
    else {
        printf("entry not found\n");
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