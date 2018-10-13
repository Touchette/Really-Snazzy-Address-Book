#ifndef ADDRESSBOOK
#define ADDRESSBOOK
#include <stdlib.h>
#include <vector>
#include <string>
#include "Entry.h"

class AddressBook {
  public:
  	std::vector<Entry*> *entries;

  	// Constructor and Destructor
  	AddressBook() { };
  	virtual ~AddressBook() { };

  	/* ============ */
  	/* Main Methods */
  	/* ============ */

  	// Entry, Removal
  	void add(Entry *entry); // add uses Entry::Change to set values
  	void remove(Entry *entry); // UI should get the entry pointer for this function

  	// Printing and Serializing
  	void printEntries();
  	std::vector<Entry*> retEntries();

  private:
  	std::vector<std::string> *fields; // if this is larger than one, adding uses
};

#endif