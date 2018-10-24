#include <QApplication>
#include "mainwindow.h"
#include "newentrydialog.h"
#include "newfielddialog.h"
#include "savechangesdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow main_w;
    main_w.setAttribute( Qt::WA_DeleteOnClose, false );
    main_w.show();
    return app.exec();
}
