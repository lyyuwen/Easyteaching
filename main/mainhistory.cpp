#include "mainhistory.h"
#include "ui_mainhistory.h"
#include "mainmine.h"
#include "mainoperation.h"
#include "mainwindow.h"
#include "mainoperation_student.h"
#include <QStandardItem>
#include <QFile>

mainhistory::mainhistory(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainhistory)
{
    ui->setupUi(this);
    users.user_init();
    QFile historyfile(QCoreApplication::applicationDirPath() + "/handoutwork.txt");
    if(historyfile.exists()){
        ItemModel = new QStandardItemModel(this);
        QStringList strList;
        historyfile.open(QIODevice::ReadWrite);
        while (!historyfile.atEnd()) {
            QString history = historyfile.readLine();
            strList.append(history.toUtf8());
        }

        int nCount = strList.size();
        for(int i = 0; i < nCount; i++)
        {
            QString string = static_cast<QString>(strList.at(i));
            QStandardItem *item = new QStandardItem(string);
            ItemModel->appendRow(item);
        }
        ui->listView->setModel(ItemModel);
    }
}

mainhistory::~mainhistory()
{
    delete ui;
}

void mainhistory::on_mode_homepage_clicked()
{
    MainWindow *mainwin = new MainWindow();
    mainwin->show();
    this->close();
}

void mainhistory::on_mode_operation_clicked()
{
    if(users.User_getTorS() == "s"){
        Mainoperation_student *oper = new Mainoperation_student();
        oper->show();
    }
    else {
        Mainoperation *oper = new Mainoperation();
        oper->show();
    }
    this->close();
}

void mainhistory::on_mode_mine_clicked()
{
    Mainmine *mine = new Mainmine();
    mine->show();
    this->close();
}
