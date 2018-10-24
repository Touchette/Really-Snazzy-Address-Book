#include "Deserializer.h"
#include "AddressBook.h"
#include "Entry.h"
#include <stdio.h>
#include <string.h>

using namespace Deserializer;
using namespace std;

Deserializer(){
}

~Deserializer(){
}

void openJSON(string path_string){
	char* path = stringToPath(path_string);
	if((file_ptr = fopen(path, 'r')) == NULL){
		printf(stderr, "ERROR OPENING FILE FOR READING");
	}
	delete path;
}

void closeJSON(){
	fclose(file_ptr);
}

AddressBook* deserializeToBook(AddressBook* starting_book = NULL){
	char token;
	AddressBook* book = starting_book;

	while((token = fgetc(file_ptr)) != EOF){
		switch (token){
			case '[':
			{
				book = new AddressBook();
				break;
			}
			case '{':
			{
				book->add(deserializeToEntry());
			}
			case ']':
			{
				return book;
			}
			default:
			{
				break;
			}
		}
	}
	return book;
}

Entry* deserializeToEntry(){
	char token;
	Entry* entry = new Entry();

	string field = string("");
	string value = string("");
	string* write_ptr = &current_field;

	while((token = fgetc(file_ptr)) != EOF){
		switch (token){
			case ':':
			{
				write_ptr = &value;
				break;
			}
			case '}':
			{
				entry->[field] = value;
				return entry;
			}
			case ',':
			{
				entry->[field] = value;
				write_ptr = &field;
				break;
			}
			case '\"':
			case '\n':
			{
				break;
			}
			default:
			{
				write_ptr->append(token, 1);
				break;
			}
		}
	}
	return entry;
}

AddressBook* deserializeTabbedValues(string tabbed_values, AddressBook* starting_book = NULL){
	return NULL;
}

char* stringToPath(string path){
	int str_length = path.length();
	char* char_buffer = new char[str_length + 1];
	strcpy(char_buffer, path.c_str());
	return char_buffer;
}

