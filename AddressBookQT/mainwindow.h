#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "ui_mainwindow.h"
#include "newentrydialog.h"
#include "newfielddialog.h"
#include "savechangesdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void openNewFieldDialog();
    void openNewEntryDialog();
    void openSaveChangesDialog();
    ~MainWindow();

private slots:
    void closeEvent(QCloseEvent *event);
    void saveChanges();
    void on_ActionQuit_triggered();
    void on_ActionSave_triggered();
    void on_ActionSaveAs_triggered();
    void on_ActionLoad_triggered();
    void on_ActionAddContact_triggered();
    void on_ActionRemoveContact_triggered();
    void on_ActionAddField_triggered();
    void on_ActionRemoveField_triggered();
    void on_ActionImport_triggered();
    void on_ActionExport_triggered();
    void on_ActionByFirstName_triggered();
    void on_ActionByLastName_triggered();
    void on_ActionByAddress_triggered();
    void on_ActionByPostalCode_triggered();
    void on_EntryChanged(QTableWidgetItem*UNUSED);

private:
    void searchBook(int col, QString text);
    void saveBook(QString file_name, int type);
    void loadBook(QString file_name, int type);
    QTableWidget *AddressTable;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
