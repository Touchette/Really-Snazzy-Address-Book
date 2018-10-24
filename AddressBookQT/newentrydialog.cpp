#include "newentrydialog.h"
#include "ui_newentrydialog.h"
#include "QMessageBox"

NewEntryDialog::NewEntryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewEntryDialog)
{
    ui->setupUi(this);
}

NewEntryDialog::~NewEntryDialog()
{
    delete ui;
}

QString NewEntryDialog::getFirstName(){
    return ui->FirstNameEntry->text();
}

QString NewEntryDialog::getLastName(){
    return ui->LastNameEntry->text();
}

QString NewEntryDialog::getStAddress(){
    return ui->stAddresField->text();
}

QString NewEntryDialog::getPostalCode(){
    return ui->ZipCodeEntry->text();
}
