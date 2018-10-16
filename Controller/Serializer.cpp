#include "Serializer.h"
#include "AddressBook.h"
#include "Entry.h"

using namespace std;
using namespace Serializer;

Serializer(){

}
~Serializer(){

}
void serializeBook(AddressBook* book){
	fputc('[', file_ptr);
	fputc('\n', file_ptr);

	for(auto &current_entry = book->entries.begin(); current_entry != book->entries.end(); current_entry++)){
		serializeEntry(current_entry);

		if(next(current_entry) != book->entries.end())
			fputc(',', file_ptr);

		fputc('\n', file_ptr);
	}
	fputc(']', file_ptr);
}

void serializeEntry(Entry* entry){
	fputc('{', file_ptr);
	fputc('\n', file_ptr);

	for(auto &field = entry->begin(); field != entry->end(); field++){
		fputc('\"', file_ptr);
		for(char &character : field->first)
			fputc(character, file_ptr)
		fputc('\"', file_ptr);

		fputc(':', file_ptr);

		fputc('\"', file_ptr);
		for(char &character : field->second)
			fputc(character, file_ptr)
		fputc('\"', file_ptr);

		if(next(field) != entry->end())
			fputc(',', file_ptr);
		
		fputc('\n', file_ptr);
	}
	fputc('}', file_ptr);
}

void openFile(string path){
	char* path = stringToPath(path_string);
	if((file_ptr = fopen(path, 'w')) == NULL){
		printf(stderr, "ERROR OPENING FILE FOR WRITING");
	}
	delete path;
}

void closeFile(){
	fclose(file_ptr);
}

char* stringToPath(string path){
	int str_length = path.length();
	char* char_buffer = new char[str_length + 1];
	strcpy(char_buffer, path.c_str());
	return char_buffer;
}
