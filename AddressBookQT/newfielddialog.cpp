#include "newfielddialog.h"
#include "ui_newfielddialog.h"
#include "QMessageBox"

NewFieldDialog::NewFieldDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFieldDialog)
{
    ui->setupUi(this);
}

NewFieldDialog::~NewFieldDialog()
{
    delete ui;
}

QString NewFieldDialog::getFieldName(){
    return ui->FieldNameEntry->text();
}
