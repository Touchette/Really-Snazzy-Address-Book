cd AddressBookQT
sudo qmake AddressBookQT.pro -spec linux-g++ CONFIG+=qtquickcompiler
sudo make
mv AddressBookQT ../AddressBook
cd ..
clear
