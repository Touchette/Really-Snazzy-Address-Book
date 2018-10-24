#include "savechangesdialog.h"
#include "ui_savechangesdialog.h"
#include "QMessageBox"

SaveChangesDialog::SaveChangesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveChangesDialog)
{
    ui->setupUi(this);
}

SaveChangesDialog::~SaveChangesDialog()
{
    delete ui;
}

void SaveChangesDialog::on_SaveChangesCancel_clicked()
{
    this->close();
}

void SaveChangesDialog::on_SaveChangesNo_clicked()
{
    QCoreApplication::quit();
}

void SaveChangesDialog::on_SaveChangesYes_clicked()
{
    QCoreApplication::quit();
}
