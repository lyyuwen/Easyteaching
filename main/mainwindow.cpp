#include "mainwindow.h"
#include "mainoperation.h"
#include "ui_mainwindow.h"
#include "mainmine.h"
#include "mainhistory.h"
#include "mainoperation_student.h"
#include "users_information.h"
#include <QStandardItemModel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    users.user_init();
    users.other_init();
    if(!(users.othernum == 0)){
        QStandardItemModel* model = new QStandardItemModel(this);
        for (int i = 0;i <= users.othernum;i++) {
            model->setItem(i, 0, new QStandardItem(users.Other_getname(i)));
            model->setItem(i, 1, new QStandardItem(users.Other_getnumber(i)));
            model->setItem(i, 2, new QStandardItem(users.Other_getisFinish(i)));
        }
        ui->tableView->setModel(model);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mode_operation_clicked()
{
    if(users.user.TorS == "s"){
        Mainoperation_student *oper = new Mainoperation_student();
        oper->show();
    }
    else {
        Mainoperation *oper = new Mainoperation();
        oper->show();
    }
    this->close();
}

void MainWindow::on_mode_mine_clicked()
{
    Mainmine *mine = new Mainmine();
    mine->show();
    this->close();
}

void MainWindow::on_mode_history_clicked()
{
    mainhistory *his = new mainhistory();
    his->show();
    this->close();
}
