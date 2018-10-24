#include <QTableWidget>
#include <QCloseEvent>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QString>
#include <QSet>
#include <string>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newentrydialog.h"
#include "newfielddialog.h"
#include "savechangesdialog.h"
#include "backend/AddressBook.h"
#include "backend/Entry.h"
#include "backend/Serializer.h"
#include "backend/Deserializer.h"

static QSet<QString> headers;
static std::map<std::string, int> indexes;
static QString g_open_file_name = nullptr;
static bool changes_made = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    headers << "First Name" << "Last Name" << "St. Address" << "Postal Code";
    ui->setupUi(this);
    connect(ui->AddressTable,SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(on_EntryChanged(QTableWidgetItem *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Overrides the standard closeEvent(), called when window is told to close.
// Checks if changes were made, if so, prompts user to save.
void MainWindow::closeEvent (QCloseEvent *event)
{
    if(changes_made){
        QMessageBox::StandardButton confirm;
        confirm = QMessageBox::warning(this,"You have unsaved changes", "Would you like to save first?",
                QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(confirm == QMessageBox::Yes){
            if(g_open_file_name != nullptr){
                saveBook(g_open_file_name, 0);
            } else {
                on_ActionSaveAs_triggered();
            }
        } else if (confirm == QMessageBox::No){
            event->accept();
        } else if (confirm == QMessageBox::Cancel){
            event->ignore();
        }
    }
}

// Searches table and highlights items matching 'text'. Column to search based on 'col'.
// col = 0 - First Name
// col = 1 - Last Name
// col = 2 - St. Address
// col = 3 - Postal Code
void MainWindow::searchBook(int col, QString text){
    int num_rows = ui->AddressTable->rowCount();
    ui->AddressTable->setSelectionMode(QAbstractItemView::MultiSelection);
    for(int i = 0; i < num_rows; i++){
        if(ui->AddressTable->item(i, col)->text() == text){
            ui->AddressTable->setCurrentCell(i, col);
        }
    }
    ui->AddressTable->setSelectionMode(QAbstractItemView::SingleSelection);
}

// Saves book based on inputted file_name, and saves based on file_type input
// file_type = 0 - Save to JSON
// file_type = 1 - Save to TSV
void MainWindow::saveBook(QString file_name, int file_type){
      AddressBook *book = new AddressBook();
      int col_count = ui->AddressTable->columnCount();
      int row_count = ui->AddressTable->rowCount();
      for(int i = 0; i < col_count; i++){
          QString colname = ui->AddressTable->horizontalHeaderItem(i)->text();
          book->addColumn(colname.toUtf8().constData());
      }
        for(int x = 0; x < row_count; x++){
             Entry *temp_entry = new Entry();

             for(int j = 0; j < 4; j++){
               QString colname = ui->AddressTable->horizontalHeaderItem(j)->text();
               temp_entry->changeField(colname.toUtf8().constData(), ui->AddressTable->item(x,j)->text().toUtf8().constData());
             }
             for(int j = 4; j < col_count; j++){
                 QString colname = ui->AddressTable->horizontalHeaderItem(j)->text();
                 temp_entry->addField(colname.toUtf8().constData(),ui->AddressTable->item(x,j)->text().toUtf8().constData());
             }
             book->add(temp_entry);
        }
      Serializer *ser = new Serializer();
      ser->openFile(file_name.toUtf8().constData());
      if(file_type == 0){
          ser->serializeBook(book);
      } else {
          ser->serializeToTabbedValues(book);
      }
      ser->closeFile();
      changes_made = false;
      delete book;
}

// Loads book based on inputted file_name, and attempts to load based on file_type input
// file_type = 0 - Load from JSON
// file_type = 1 - Load from TSV
void MainWindow::loadBook(QString file_name, int file_type)
{
        Deserializer *d = new Deserializer();
        AddressBook *a = new AddressBook(); // empty AddressBook to start with

        d->openFile(file_name.toUtf8().constData() );
        if(file_type == 0){
            a = d->deserializeToBook(a); // deserialize the file to the empty book
        } else {
            a = d->deserializeTabbedValues(a);
        }
        d->closeFile();

        std::list<Entry*> entries = a->retEntries(); // the address book's entries list
        std::list<Entry*>::iterator it; // the iterator for the entries
        std::vector<std::string> fields; // the vector that will hold each entry's fields

        indexes.clear();
        indexes["First Name"] = 0;
        indexes["Last Name"] = 1;
        indexes["St. Address"] = 2;
        indexes["Postal Code"] = 3;

        it = entries.begin();
        if(it == entries.end()){
            QMessageBox::critical(this,"Invalid File","Selected file is empty.");
            return;
        }

        if(file_type == 0){
            int col_count_2 = ui->AddressTable->columnCount()-4;
            for(int i = 0; i < col_count_2; i++){
                headers.remove(ui->AddressTable->horizontalHeaderItem(4)->text());
                ui->AddressTable->removeColumn(4);
            }
            ui->AddressTable->setRowCount(0);
            ui->AddressTable->setColumnCount(4);
        }

        fields = (*it)->getKeys();

        std::vector<std::string>::iterator jt;

        for(int i = 4; i < ui->AddressTable->columnCount(); i++){
            indexes[(ui->AddressTable->horizontalHeaderItem(i)->text()).toUtf8().constData()] = i;
        }

        for(jt = fields.begin(); jt != fields.end(); ++jt){
            QString temp_qstring = QString::fromStdString((*jt));
            if(!headers.contains(temp_qstring.trimmed()) && !temp_qstring.isEmpty() && !temp_qstring.isNull()){
                int column_count = ui->AddressTable->columnCount();
                ui->AddressTable->setColumnCount(column_count+1);
                ui->AddressTable->setHorizontalHeaderItem(column_count, new QTableWidgetItem(temp_qstring));
                headers << temp_qstring;
                indexes[(*jt)] = column_count;
            }
        }

        for (it = entries.begin(); it != entries.end(); ++it) {
            QSet<QString>::iterator fi;
            ui->AddressTable->insertRow(0);
            for(fi = headers.begin(); fi != headers.end(); ++fi){
                std::string colname = (*fi).toUtf8().constData();
                std::string value = (*it)->getFieldValue(colname);
                ui->AddressTable->setItem(0,indexes[colname], new QTableWidgetItem(QString::fromStdString(value)));
            }
        }
        delete a;
        delete d;
        if(file_type == 0){
            g_open_file_name = file_name;
            QWidget::setWindowTitle("VSAB @ " + file_name);
        }
}

// Funciton that is called when closing and entries are changed.
void MainWindow::saveChanges(){
    if(g_open_file_name != nullptr){
        saveBook(g_open_file_name, 0);
    } else {
        on_ActionSaveAs_triggered();
    }
    QCoreApplication::quit();
}

// Signal slot to handle adding a contact.
void MainWindow::on_ActionAddContact_triggered()
{
    NewEntryDialog *NEDW = new NewEntryDialog();
    if(NEDW->exec())
    {
        QString first_name = NEDW->getFirstName();
        QString last_name = NEDW->getLastName();
        QString postal_code = NEDW->getPostalCode();
        QString st_address = NEDW->getStAddress();
        ui->AddressTable->insertRow(0);
        ui->AddressTable->setItem(0,0, new QTableWidgetItem(first_name));
        ui->AddressTable->setItem(0,1, new QTableWidgetItem(last_name));
        ui->AddressTable->setItem(0,2, new QTableWidgetItem(st_address));
        ui->AddressTable->setItem(0,3, new QTableWidgetItem(postal_code));
    }
    changes_made = true;
}

// Signal slot to handle removing a contact.
void MainWindow::on_ActionRemoveContact_triggered()
{
    ui->AddressTable->removeRow(ui->AddressTable->currentRow());
    changes_made = true;
}

// Signal slot to handle adding a field.
void MainWindow::on_ActionAddField_triggered()
{
    NewFieldDialog *NFDW = new NewFieldDialog();
    if(NFDW->exec())
    {
        QString field_name = NFDW->getFieldName();
        if(headers.contains(field_name.trimmed())){
            QMessageBox::warning(this,"Warning","A field of that name already exists!");
        } else if(!field_name.trimmed().isEmpty())
        {
            int column_count = ui->AddressTable->columnCount();
            ui->AddressTable->setColumnCount(column_count+1);
            ui->AddressTable->setHorizontalHeaderItem(column_count, new QTableWidgetItem(NFDW->getFieldName()));
            headers << field_name;
            changes_made = true;
        } else {
            QMessageBox::warning(this,"Warning","New field is empty.");
        }
    };
}

// Signal slot to handle removing a field.
void MainWindow::on_ActionRemoveField_triggered()
{
    if(ui->AddressTable->currentColumn() > 3)
    {
        QMessageBox::StandardButton confirm;
        QString message = "Are you sure you want to remove field: " + ui->AddressTable->horizontalHeaderItem(ui->AddressTable->currentColumn())->text() + "?";
        confirm = QMessageBox::question(this,"Remove Column", message,
                QMessageBox::Yes|QMessageBox::No);

        if(confirm == QMessageBox::Yes)
        {
            headers.remove(ui->AddressTable->horizontalHeaderItem(ui->AddressTable->currentColumn())->text());
            ui->AddressTable->removeColumn(ui->AddressTable->currentColumn());
            ui->AddressTable->setCurrentCell(ui->AddressTable->currentRow(), 0);
        }
    }
    else
    {
        QMessageBox::information(this,"Information","Cannot delete first four fields.");
    }
    changes_made = true;
}

// Signal slot to search by First Name
void MainWindow::on_ActionByFirstName_triggered(){
    bool ok;
    QString search = QInputDialog::getText(this, tr("Search by First Name"),
                                         tr("First Name:"), QLineEdit::Normal,
                                         "", &ok);
    if(ok && !search.isEmpty() && !search.isNull()){
        searchBook(0, search);
    }
}

// Signal slot to search by Last Name
void MainWindow::on_ActionByLastName_triggered(){
    bool ok;
    QString search = QInputDialog::getText(this, tr("Search by Last Name"),
                                         tr("Last Name:"), QLineEdit::Normal,
                                         "", &ok);
    if(ok && !search.isEmpty() && !search.isNull()){
        searchBook(1, search);
    }
}

// Signal slot to search by Address
void MainWindow::on_ActionByAddress_triggered(){
    bool ok;
    QString search = QInputDialog::getText(this, tr("Search by Address"),
                                         tr("Address:"), QLineEdit::Normal,
                                         "", &ok);
    if(ok && !search.isEmpty() && !search.isNull()){
        searchBook(2, search);
    }
}

// Signal slot to search by Postal Code
void MainWindow::on_ActionByPostalCode_triggered(){
    bool ok;
    QString search = QInputDialog::getText(this, tr("Search by Postal Code"),
                                         tr("Postal Code:"), QLineEdit::Normal,
                                         "", &ok);
    if(ok && !search.isEmpty() && !search.isNull()){
        searchBook(3, search);
    }
}

// Signal slot to handle importing from a TSV
void MainWindow::on_ActionImport_triggered(){
    QString temp_import_string = QFileDialog::getOpenFileName(this,
        tr("Open Address Book"), "", tr("Address Book (*.tsv)"));
    if(!temp_import_string.isNull() && !temp_import_string.isEmpty()){
        loadBook(temp_import_string, 1);
    }
}

// Signal slot to handle exporting to a TSV
void MainWindow::on_ActionExport_triggered()
{
    if(ui->AddressTable->rowCount() > 0){
        QString export_file_name = QFileDialog::getSaveFileName(this,
            tr("Save Address Book"), "addressbook.tsv", tr("Address Book (*.tsv)"));

        if(!export_file_name.isNull() && !export_file_name.isEmpty()){
            saveBook(export_file_name, 1);
        }
    }
}

// Signal slot to handle saving to an open JSON file, calls saveBook().
void MainWindow::on_ActionSave_triggered()
{
    if(g_open_file_name == nullptr){
        on_ActionSaveAs_triggered();
    } else if(ui->AddressTable->rowCount() > 0){
        QString file_name;
        if(g_open_file_name == nullptr){
            file_name = QFileDialog::getSaveFileName(this,
                tr("Save Address Book"), "addressbook.json", tr("Address Book (*.json)"));
            if(!file_name.isEmpty() && !file_name.isNull()){
                g_open_file_name = file_name;
                saveBook(file_name, 0);
                QWidget::setWindowTitle("VSAB @ " + file_name);
            }
        } else {
            saveBook(g_open_file_name, 0);
        }
    }
    changes_made = false;
}

// Signal slot to handle saving to a new JSON file, calls saveBook().
void MainWindow::on_ActionSaveAs_triggered(){
    if(ui->AddressTable->rowCount() > 0){
        QString file_name;
        file_name = QFileDialog::getSaveFileName(this,
            tr("Save Address Book"), "addressbook.json", tr("Address Book (*.json)"));
        if(!file_name.isEmpty() && !file_name.isNull()){
                saveBook(file_name, 0);
        }
    }
}

// Close.
void MainWindow::on_ActionQuit_triggered(){
    this->close();
}

// Signal slot to handle loading from JSON file, calls loadBook() if good input.
void MainWindow::on_ActionLoad_triggered(){
    QString temp_load_filename = QFileDialog::getOpenFileName(this,
        tr("Open Address Book"), "", tr("Address Book (*.json)"));

    if(temp_load_filename == g_open_file_name){
        QMessageBox::warning(this,"Warning","File is already open.");
    }  else if(!temp_load_filename.isNull() && !temp_load_filename.isEmpty()){
        loadBook(temp_load_filename, 0);
        g_open_file_name = temp_load_filename;
    }
}

// Signal slot to set changes_made to true if an item is changed.
void MainWindow::on_EntryChanged(QTableWidgetItem *UNUSED){
    UNUSED->column();
    changes_made = true;
}
