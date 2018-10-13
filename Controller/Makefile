CC = g++ -Wall -Wextra -pedantic

default: AddressBook

%.o: %.c %.h
	$(CC) -c

AddressBook: main.o AddressBook.o Entry.o
	$(CC) -o $@ $^

clean:
	rm -f *.o
	rm AddressBook