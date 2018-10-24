#include "Deserializer.h"
#include "AddressBook.h"
#include "Entry.h"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

Deserializer::Deserializer(){
}

Deserializer::~Deserializer(){
}

void Deserializer::openFile(string path_string){
	//opens file, checks if result is NULL
	if((file_ptr = fopen(path_string.c_str(), "r")) == NULL){
		fprintf(stderr, "ERROR OPENING FILE FOR READING");
	}
}

void Deserializer::closeFile(){
	fclose(file_ptr);
}

AddressBook* Deserializer::deserializeToBook(AddressBook* starting_book){
	/*
	Deserializes a JSON array to an address book;
	*/
	char token;
	AddressBook* book = starting_book;
	while((token = fgetc(file_ptr)) != ']'){
		switch (token){
			case '[':
			{
				// "[" begins a json array
				if (book == NULL)
					book = new AddressBook();
				break;
			}
			case '{':
			{
				// "{" begins a json object
				book->add(deserializeToEntry());
				break;
			}
			default:
			{
				break;
			}
		}
	}
	return book;
}

Entry* Deserializer::deserializeToEntry(){
	/*
	deserializes an entry of the form
	{key1 : value1 , key2 : value2 , ...}
	*/
	char token;
	Entry* entry = new Entry();

	bool is_in_quotes = false;

	string field = "";
	string value = "";
	string* write_ptr = &field;

	while((token = fgetc(file_ptr)) != '}' || is_in_quotes){
		switch (token){
			case ':':
			{
				// ":" marks the change between a key and value, unless inside a key or value's name
				if(is_in_quotes){
					write_ptr->append(sizeof(char), token);
				}
				else{
					write_ptr = &value;
				}
				break;
			}
			case ',':
			{
				// "," marks the change between a key and value, unless inside a key or value's name
				if(is_in_quotes){
					write_ptr->append(sizeof(char), token);
				}
				else{
					if(entry->fields.count(field)){
						entry->changeField(field, value);
					}
					else{
						entry->addField(field, value);
					}
	                field = "";
	                value = "";
					write_ptr = &field;
				}
				break;
			}
			case '\"':
			{
				is_in_quotes = !is_in_quotes;
				break;
			}
			case ' ':
			{
				// Only parse white space if it appears as part of a name
				if(is_in_quotes){
					write_ptr->append(sizeof(char), token);
				}
				break;
			}
			case '\n':
			case '\t':
			{
				// Never parse tabs or newlines
				break;
			}
			default:
			{
				write_ptr->append(sizeof(char), token);
				break;
			}
		}
	}
	entry->fields[field] = value;
	return entry;
}

AddressBook* Deserializer::deserializeTabbedValues(AddressBook* starting_book){
	/*
	Deserializes tabbed values of the form
	name 	name 	name 	name 	...
	value 	value 	value 	value 	...
	...
	*/
    char token;
    AddressBook *book = starting_book == NULL ? new AddressBook() : starting_book;
    
    string field = "";
    string value = "";
    vector<string> field_names;

    //Inital sweep to get all field names
    while((token = fgetc(file_ptr)) != '\n'){
    	switch(token){
    		case '\t':
    		{
    			field_names.push_back(field);
    			field = "";
    			break;
    		}
    		default:
    		{
    			field.append(sizeof(char), token);
    			break;
    		}
    	}
    }
    field_names.push_back(field);
    
    Entry* currentEntry = new Entry();

    int field_number = 0;
    
    //second sweep to get values associated with names
    while((token = fgetc(file_ptr)) != EOF){
        switch(token){
            case '\n':
            {
            	//Newline marks a new entry beginning
                book->add(currentEntry);
                currentEntry = new Entry();
                field_number = 0;
                break;
            }
            case '\t':
            {
            	//tab marks a new field beginning
            	string key = field_names.at(field_number++);

            	if(currentEntry->fields.count(key)){
            		currentEntry->changeField(key, value);
            	}
            	else{
	                currentEntry->addField(key, value);
	            }
                value = "";
                break;
            }
            default:
            {
                value.append(sizeof(char), token);
                break;
            }
        }
    }
    if(currentEntry->fields.size() == 0){
    	delete currentEntry;
    }
    return book;
}