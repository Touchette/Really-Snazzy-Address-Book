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
<<<<<<< HEAD:AddressBookQT/backend/AddressBook.h
  	void add(Entry *entry); // add uses Entry::changeField to set values
	void addColumn(std::string key);
  	void remove(Entry *entry); // UI should get/create the entry pointer for this function
=======
  	void add(Entry *entry); // add uses Entry::Change to set values
	void addColumn(std::string key);
  	void remove(Entry *entry); // UI should get the entry pointer for this function
>>>>>>> ec44a42071a4b301fde83dc2843abb1c8f9192a6:Controller/AddressBook.h
	void removeColumn(std::string key);

  	// Printing and Getting Data
  	void printEntries();
  	std::list<Entry*> retEntries();

  private:
<<<<<<< HEAD:AddressBookQT/backend/AddressBook.h
  	std::list<std::string> fields; // if len(fields)>0, used by "add"
=======
  	std::list<std::string> fields; // if this is larger than one, adding uses
>>>>>>> ec44a42071a4b301fde83dc2843abb1c8f9192a6:Controller/AddressBook.h
};

#endif
