#include <stdio.h>
#include <string>
#include "AddressBook.h"
#include "Entry.h"

int main(int argc, char *argv[]) {
	AddressBook ab;
	Entry entry1;

	entry1.changeField("lastname", "Letz");
	entry1.changeField("firstname", "Nate");
	entry1.changeField("zipcode", "97402");
	entry1.changeField("address", "3784 Peppertree Dr");

	ab.add(&entry1);

	ab.printEntries();

	ab.remove(&entry1);

	ab.printEntries();
}
