# Description #
Very Snazzy Address Book is an Address Book application that stores contacts and associated their associated user-inputted data. It is written in C++: the backend being a serializer / deserializer combo to store data, the core application being AddressBook and Entry classes, and the UI being done in QT.

# Installation #

### Minimum Requirements ###

Linux-based distro / macOS

Intel Core 2 Duo Processor

2GB RAM

200 GB Disk Space

### Installation ###
NOTE: If you have previously installed Very Snazzy Address Book, you must run the uninstall script (at the bottom of this readme) before re-installing.

Download the compressed application file
Move the compressed application file to where you’d like to install the application; replacing “some/path/” with the desired installation path (all commands will assume a bash-like terminal emulator):

` mv Really-Snazzy-Address-Book-master.zip some/path/ `

Navigate to the directory containing the compressed application file; replacing “some/path/” with the path to the directory containing the cloned repo file:

` cd some/path/ `

Decompress the file using zip (or your preferred decompression method):

` unzip Really-Snazzy-Address-Book-master.zip `

Navigate into the application directory:

` cd Really-Snazzy-Address-Book-master `

Run the installation script; when prompted for a password, enter your user password:

` ./Install.sh `

Run the application by running the “AddressBook” executable; this can be done graphically through a file browser or through the command line:

` ./AddressBook `

### Uninstalling ###
Navigate to the application directory; replacing “some/path/” with the path of the installation directory:

` cd some/path/ `

Run the uninstall script; if prompted to confirm deletion of the AddressBook executable, type “y” then hit enter:

` ./Uninstall.sh `
