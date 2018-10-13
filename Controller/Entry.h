#ifndef ENTRY
#define ENTRY
#include <stdlib.h>
#include <map>
#include "Entry.h"

class Entry {
  public:
  	std::map<const char*, const char*> *fields;

  	// Constructor and Destructor
  	Entry();
  	virtual ~Entry() { };

  	/* ============ */
  	/* Main Methods */
  	/* ============ */

  	/*
  	// Overloaded comparison operators
  	friend bool operator> (const &Entry1, const &Entry2);
  	friend bool operator< (const &Entry1, const &Entry2);
  	friend bool operator>= (const &Entry1, const &Entry2);
  	friend bool operator<= (const &Entry1, const &Entry2);
  	friend bool operator== (const &Entry1, const &Entry2);
  	friend bool operator!= (const &Entry1, const &Entry2);
  	*/

  	// Modifying and Adding data
  	void addField(const char* key, const char* value);
  	void changeField(const char* key, const char* value);

  	// Getting data
  	const char* getFieldData(const char* key);
  	const char* format();
};

#endif