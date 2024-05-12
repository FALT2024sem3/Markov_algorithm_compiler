#include "Qt_GUI/mainwindow.h"

#include <QApplication>
#include <QStandardItemModel>

int main(int argc, char *argv[])
{
    QStandardItemModel table = QStandardItemModel();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
