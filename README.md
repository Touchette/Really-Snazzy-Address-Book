# Description #
Very Snazzy Address Book is an Address Book application that stores contacts and associated user data.

# Installation #

1.	Minimum Requirements
Linux/macOS
Intel Core 2 Duo Processor
2GB RAM
200 GB Disk Space

2.	Installation
NOTE: If you have previously installed VerySnazzyAddressBook, you must run the uninstall script (section 3 of this document) before re-installing

Download the compressed application file
Move the compressed application file to where you’d like to install the application; replacing “some/path/” with the desired installation path
- mv ClonedRepo some/path/
Navigate to the directory containing the compressed application file; replacing “some/path/” with the path to the directory containing the cloned repo file
- cd some/path/
Decompress the file using tar (or your preferred decompression method)
- tar -xvzf TeamA.tar
Navigate into the application directory
- cd 
Run the installation script; when prompted for a password, enter your user password
- ./Install.sh
Run the application by running the “AddressBook” executable; this can be done graphically through a file browser or through the command line
- ./AddressBook

3.	Uninstalling
Navigate to the application directory; replacing “some/path/” with the path of the installation directory
- cd some/path/
Run the uninstall script; if prompted to confirm deletion of the AddressBook executable, type “y” then hit enter
- ./Uninstall.sh


