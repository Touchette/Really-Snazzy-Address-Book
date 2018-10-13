#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include "AddressBook.h"
#include "Entry.h"

// Entry, Removal
void AddressBook::add(Entry *entry) {
    printf("adding entry with last name \"%s\"\n", entry->getFieldData("lastname"));
    entries->push_back(entry);
}

void AddressBook::remove(Entry *entry) {
    int i;
    std::vector<Entry*>::iterator it = std::find(entries->begin(), entries->end(), entry);
    if (it != entries->end()) {
        printf("removing entry with last name \"%s\"\n", entry->getFieldData("lastname"));
        entries->erase(it);
    }
    else {
        printf("entry not found\n");
    }
}

// Printing and Serializing
void AddressBook::printEntries() {
    std::vector<Entry*>::iterator it = entries->begin();
    for (it; it != entries->end(); ++it) {
        printf("%p", *it);
    }
}

std::vector<Entry*> AddressBook::retEntries() {
    return *entries;
}