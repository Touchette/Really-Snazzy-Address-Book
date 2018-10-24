#ifndef NewFieldDialog_H
#define NewFieldDialog_H

#include <QDialog>

namespace Ui {
class NewFieldDialog;
}

class NewFieldDialog : public QDialog
{
    Q_OBJECT

public:
    QString getFieldName();
    explicit NewFieldDialog(QWidget *parent = nullptr);
    ~NewFieldDialog();

private:
    Ui::NewFieldDialog *ui;
};

#endif // NewFieldDialog_H
