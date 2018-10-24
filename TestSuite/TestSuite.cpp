// Function Definitions for testing
#include <stdio.h>
#include <stdlib.h>
#include <printf.h>
#include "TestSuite.h"
#include "../Controller/Entry.h"
#include "../Controller/AddressBook.h"
#include "../Model/Serializer.h"
#include "../Model/Deserializer.h"
#include <time.h>

// timing tests
clock_t addContact(AddressBook * ab, Entry e1);
{
    clock_t time;
    time = clock()
    ab->add(&e1);
    time = clock()-time;
    return time;
}

clock_t deleteContact(AddressBook* ab, Entry e1);
{
    ab->add(&e1);
    clock_t time;
    time = clock()
    ab->remove(&e1);
    time = clock()-time;
    return time;
}

clock_t addColumn(AddressBook* ab)
{
    clock_t time;
    time = clock();
    ab->addColumn("Buffalo");
    time  = clock() - time;
    return time;
}

clock_t testSerializer(AddressBook* ab1, string path)
{
    clock_t time;
    Serializer serialize_book = new Serializer();
    time = clock();
    
    serialize_book.openFile(path);
    serialize_book(&ab1);
    serialize_book.closeFile();
    
    time  = clock() - time;
    return time;}

clock_t testDeserializer(string path serial_file)
{
    clock_t time;
    Deserializer deserializeBook = new Deserializer();
    AddressBook* ab1 = new AddressBook();
    
    time = clock();
    deserializeBook.openJSON(serial_file);
    ab1 = deserializeBook.deserializeToBook();
    deserializeBook.closeJSON();
    time  = clock() - time;
    
    delete ab1;
    delete deserializeBook;
    return time;
}

clock_t removeColumn(AddressBook* ab)
{
    ab->addColumn("butts");
    clock_t time;
    time = clock();
    ab->removeColumn("butts");
    time  = clock() - time;
    return time;
}

clock_t editField(AddressBook* ab)
{
    Entry e1 = new Entry();
    clock_t time;
    time = clock();
    e1.changeField("lastname", "neal");
    time  = clock() - time;
    return time;
}
/*
 This is not currently doable
clock_t searchContact(AddressBook* ab)
{
    clock_t time;
    time = clock();
    
    time  = clock() - time;
    return time;
}
*/

void testEntryClass(FILE* outputfile)
{
    /*
     These are going to be general tests for the entry class that should all be within its base functionality, if I run into any problems I'll comment them below depending on the category that I find them in. As of now I plan to do only a few basic tests for functionality. Most of the in depth testing will be in the use case tests.
     General Questions:
     Where is the sorting functionality going to be placed entry or AddressBook?
     
     The intialization tests will show the entires when they are in their base state of everything null, I will add questions/concerns/suggestions below.
     1. Fields should not be base named null I believe just an empty string "" would be fine, might work better to show blank fields in JSON instead of NULL being written as currently "NULL" is the default.
     
     The editing feature tests will look into how the entries will be manipulated. If I run onto any error or find anything that might need to be changed I'll comment it below this section.
     1. Does addField just do the same thing as changeField but will less steps?
     2. Adding a deleteField function is neccessary.
     3. I don't think that formatEntry would be useful, unless theres a future plan for it we should just discard it.
     
     */
    //Test Intialization
    Entry entrytest;
    fprintf(outputfile,"Init Test1:\n %s\n %s\n %s\n %s\n %s\n",
            entrytest.getFieldData("lastname"),
            entrytest.getFieldData("firstname"),
            entrytest.getFieldData("zipcode"),
            entrytest.getFieldData("address"),
            entrytest.getFieldData("XboxGT"));
    
    entrytest.changeField("firstname", "Derrick");
    entrytest.changeField("lastname", "Neal");
    entrytest.changeField("zipcode", "0000000-000000x");
    entrytest.changeField("address", "1234 Rainbow Road");
    entrytest.changeField("XboxGT" , "XxYxXD");
    fprintf(outputfile,"Init Test2:\n %s\n %s\n %s\n %s\n %s\n",
            entrytest.getFieldData("lastname"),
            entrytest.getFieldData("firstname"),
            entrytest.getFieldData("zipcode"),
            entrytest.getFieldData("address"),
            entrytest.getFieldData("XboxGT"));
    //End Test Init
    
    //Test Editing Features
    entrytest.addField("Battle.net", "Nerrick#11530");
    fprintf(outputfile,"ADDFIELDTEST1: Initialize New Field \" BATTLE.NET \"\n RESULT:  %s\n", entrytest.getFieldData("Battle.net"));
    // Behavioral Test
    entrytest.updateField("Battle.net", "ERROR");
    fprintf(outputfile,"ADDFIELDTEST2: ADDFIELD WITH SAME NAME AS PREV ADDED ONE\n  %s\n", entrytest.getFieldData("Battle.net"));
    
    entrytest.updateField("lastname", ""); //Set Default as Empty String for all as opposed to "NULL"?
    entrytest.updateField("zipcode", "N/a");
    entrytest.removeCol("Battle.net");
    entrytest.removeCol("zipcode");
    //entrytest.deleteField("Battle.net");
    //entrytest.deleteField("what");
    //End Editing Feature Test
    
}

void testAddressBookClass(FILE* outputfile)
{
    /*
     This function will test the AddressBook class and its basic funtionality. If I find any errors or have general concerns I will drop them below to discuss at meetings.
     
     */
    
    AddressBook ab1 = new AddressBook();
    Entry emptyentry = new Entry();
    Entry testentry1 = new Entry();
    
    ab1.add(&emptyentry); //Might wanna rename these to addEntry and removeEntry.
    ab1.remove(&emptyentry);
    
    ab1.add(&testentry1);
    testentry1.changeField("firstname", "Derrick");
    ab1.add(&testentry1); // Adding same Entry twice. when changes what do?
    //fprintf(outputfile,"Print after adding the same thing twice but modifying after the first time I add it." ab1.printEntries());
    ab1.removeEntry(&testentry1); //Remove again Behavioural Test
    
    
}


void testJSONSerialization(string path) // Use Palmer's Large JSON file generator
{
    /*
     This will serialize an addressbook and then deserialize it. A basic test of how the serialization works, might split this into a two function process to see output after serialization. If I have any questions/conerns/suggestions I'll place them below.
     */
    Serializer serialize_book = new Serializer();
    AddressBook ab1 = new AddressBook();
    Entry entry1 = new Entry();
    Entry entry2 = new Entry();
    
    serialize_book.openFile(path);
    entry1.changeField("firstname", "Derrick");
    entry1.changeField("lastname", "Neal");
    entry1.changeField("zipcode", "97401");
    entry1.changeField("address", "3225 Kinsrow Ave.");
    entry1.addField("11111101019q083093810239810398103801809283903", "1029383109381038193081309183018321038120318301830");
    ab1.add(&entry1);
    ab1.add(&entry2);
    
    serialize_book.openFile(path);
    serialize_book(&ab1);
    serialize_book.closeFile();
    
    delete ab1;
    delete serialize_book;
    delete entry2;
    delete entry1;
    
}

void testJSONDeserialization(string pathstring) // Test deserialization of Palmer's large JSON list that is serialized.
{
    Deserializer deserializeBook = new Deserializer;
    AddressBook* ab1;
    deserializeBook.openJSON(pathstring);
    ab1 = deserializeBook.deserializeToBook();
    
    ab1->printEntries();
    deserializeBook.closeJSON();
    
    
    
    
}

//End Basic Class Tests

//Use Case Tests

//End USe Case Tests

int main(int argc, char** argv)
{
    clock_t time_add; // time add contact
    clock_t time_rem; // time remove contact
    clock_t time_ser; // time serializer
    clock_t time_addf; // time add field
    clock_t time_editf; // time clear field
    clock_t time_dser; // time deserializer
    clock_t time_remc; // time remove column
    clock_t time_addc; // time add column
    FILE* outputfile = fopen("TestingOutput" "w");
    AddressBook* ab = new AddressBook();
    Entry e1 = new Entry();
    
    // Basic Functionality Tests
    testEntryClass(outputfile);
    testAddressBookClass(outputfile);
    
   //Timing Tests
    
    time_add =
    time_rem =
    time_ser =
    time_addf =
    time_editf =
    time_dser =
    time_remc =
    time_addc =
    
    //End Timing Tests
    
    
    
    
    
    
    
    // write timings to the output file.
    delete ab;
    delete e1;
    flose(outputfile);
    return 0;
}
