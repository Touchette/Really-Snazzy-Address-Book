#ifndef ADDRESSBOOK
#define ADDRESSBOOK
#include <stdlib.h>
#include <list>
#include "Entry.h"

class AddressBook {
  public:
  	std::list<Entry*> entries;

  	// Constructor and Destructor
  	AddressBook() { };
  	virtual ~AddressBook() { };

  	/* ============ */
  	/* Main Methods */
  	/* ============ */

  	// Entry, Removal
  	void add(Entry *entry); // add uses Entry::Change to set values
	void addColumn(std::string key);
  	void remove(Entry *entry); // UI should get the entry pointer for this function
	void removeColumn(std::string key);

  	// Printing and Serializing
  	void printEntries();
  	std::list<Entry*> retEntries();

  private:
  	std::list<std::string> fields; // if this is larger than one, adding uses
};

#endif
