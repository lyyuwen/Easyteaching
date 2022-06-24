#include "mainwindow.h"
#include "tool.h"
#include "users_information.h"
#include <QApplication>
#include <QCoreApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Tool tool;
    Login login;
    tool.isFileExist();
    w.show();
    login.show();
    return a.exec();
}



