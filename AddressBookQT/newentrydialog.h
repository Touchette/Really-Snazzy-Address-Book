#ifndef NewEntryDialog_H
#define NewEntryDialog_H

#include <QDialog>

namespace Ui {
class NewEntryDialog;
}

class NewEntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewEntryDialog(QWidget *parent = nullptr);
    QString getFirstName();
    QString getLastName();
    QString getStAddress();
    QString getPostalCode();
    ~NewEntryDialog();

private:
    Ui::NewEntryDialog *ui;
};

#endif // NewEntryDialog_H
