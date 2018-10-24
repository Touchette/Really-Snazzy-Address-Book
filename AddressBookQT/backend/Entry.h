#ifndef ENTRY
#define ENTRY
#include <stdlib.h>
<<<<<<< HEAD:AddressBookQT/backend/Entry.h
#include <vector>
=======
#include <list>
#include <map>
>>>>>>> ec44a42071a4b301fde83dc2843abb1c8f9192a6:Controller/Entry.h
#include <string>
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
<<<<<<< HEAD:AddressBookQT/backend/Entry.h
    std::vector<std::string> getKeys();
=======
  private:
	static std::list<std::string> userFields;
>>>>>>> ec44a42071a4b301fde83dc2843abb1c8f9192a6:Controller/Entry.h
};

#endif
