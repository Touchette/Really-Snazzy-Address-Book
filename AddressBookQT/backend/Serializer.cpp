#include "Serializer.h"
#include "AddressBook.h"
#include "Entry.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

Serializer::Serializer(){

}
Serializer::~Serializer(){

}
void Serializer::serializeBook(AddressBook* book){
	/*
	writes address books to json as a json array
	[
	{
	key : value,
	key : value,
	...
	},
	...
	]
	*/
	fputc('[', file_ptr);
	//newlines are for json readability
	fputc('\n', file_ptr);

	std::list<Entry*>::iterator entry;

	for(entry = book->entries.begin(); entry != book->entries.end(); entry++){
		serializeEntry(*entry);

		if(next(entry) != book->entries.end())
			fputc(',', file_ptr);

		fputc('\n', file_ptr);
	}
	fputc(']', file_ptr);
}

void Serializer::serializeEntry(Entry* entry){
	//Each entry takes the form
	//{key : value, key : value , ...}
	fputc('{', file_ptr);
	fputc('\n', file_ptr);

    std::map<string, string>::iterator field;

	for(field = entry->fields.begin(); field != entry->fields.end(); field++){
		fputc('\"', file_ptr);
		for(const char &character : field->first)
			fputc(character, file_ptr);
		fputc('\"', file_ptr);

		fputc(':', file_ptr);

		fputc('\"', file_ptr);
		for(const char &character : field->second)
			fputc(character, file_ptr);
		fputc('\"', file_ptr);

		if(next(field) != entry->fields.end())
			fputc(',', file_ptr);
		
		fputc('\n', file_ptr);
	}
	fputc('}', file_ptr);
}

void Serializer::serializeToTabbedValues(AddressBook* book){

    std::list<Entry*>::iterator entry;
    std::list<std::string>::iterator field_name;
    std::map<string, string>::iterator field;

    //initial sweep to get field names
    entry = book->entries.begin();
    for(field = (*entry)->fields.begin(); field != (*entry)->fields.end(); field++){
		for(const char &character : field->first){
            fputc(character, file_ptr);
        }
        fputc('\t', file_ptr);
    }
    fputc('\n', file_ptr);
    //secondary sweep to write field contents
    for(entry = book->entries.begin(); entry != book->entries.end(); entry++){
    	for(field = (*entry)->fields.begin(); field != (*entry)->fields.end(); field++){
            for(const char &character : field->second){
                fputc(character, file_ptr);
            }
            fputc('\t', file_ptr);
        }
        fputc('\n', file_ptr);
    }
}

void Serializer::openFile(string path){
	//opens file, checks if result is NULL
	if((file_ptr = fopen(path.c_str(), "w")) == NULL){
		fprintf(stderr, "ERROR OPENING FILE FOR WRITING");
	}
}

void Serializer::closeFile(){
	fclose(file_ptr);
}
