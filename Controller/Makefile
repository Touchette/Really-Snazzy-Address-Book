CC = g++ -std=c++11 -g
CCOPTS = -L /usr/local/lib

default: AddressBook

%.o: %.c %.h
	$(CC) $(CCOPTS) -c

AddressBook: main.o AddressBook.o Entry.o
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -f *.o
	rm AddressBook
