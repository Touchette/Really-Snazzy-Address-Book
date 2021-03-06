#ifndef ENTRY
#define ENTRY

#include <stdlib.h>
#include <string>
#include <vector>
#include <list>
#include <map>

class Entry {
  public:
	std::map<std::string, std::string> fields;

	// Constructor and Destructor
	Entry();
	virtual ~Entry() { };

	/* ============ */
	/* Main Methods */
	/* ============ */

	// Modifying and Adding data
	void addField(std::string key, std::string value);
	void removeField(std::string key);
	void changeField(std::string key, std::string value);

	// Getting data
	std::string getFieldValue(std::string key);
	std::string format();
	std::vector<std::string> getKeys();
  private:
	static std::list<std::string> userFields;
};

#endif
