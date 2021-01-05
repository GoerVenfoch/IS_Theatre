#include "mainwidget.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.resize(400, 400);
    w.setWindowIcon(QIcon(":/icon/icon.png"));
    w.show();
    return a.exec();
}
