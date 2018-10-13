#ifndef ENTRY
#define ENTRY
#include <stdlib.h>
#include <map>
#include <string>
#include "Entry.h"

class Entry {
  public:
  	std::map<std::string, std::string> fields;

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
  	void addField(std::string key, std::string value);
  	void changeField(std::string key, std::string value);

  	// Getting data
  	std::string getFieldData(std::string key);
  	std::string format();
};

#endif