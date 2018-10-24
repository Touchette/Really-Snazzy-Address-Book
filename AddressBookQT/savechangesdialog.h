#ifndef SAVECHANGESDIALOG_H
#define SAVECHANGESDIALOG_H

#include <QDialog>

namespace Ui {
class SaveChangesDialog;
}

class SaveChangesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveChangesDialog(QWidget *parent = nullptr);
    ~SaveChangesDialog();

private slots:
    void on_SaveChangesNo_clicked();
    void on_SaveChangesCancel_clicked();
    void on_SaveChangesYes_clicked();

private:
    Ui::SaveChangesDialog *ui;
};

#endif // SAVECHANGESDIALOG_H
