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
  	void add(Entry *entry); // add uses Entry::changeField to set values
	void addColumn(std::string key);
  	void remove(Entry *entry); // UI should get/create the entry pointer for this function
	void removeColumn(std::string key);

  	// Printing and Getting Data
  	void printEntries();
  	std::list<Entry*> retEntries();

  private:
  	std::list<std::string> fields; // if len(fields)>0, used by "add"
};

#endif
