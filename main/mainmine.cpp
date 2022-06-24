#include "mainmine.h"
#include "ui_mainmine.h"
#include "mainwindow.h"
#include "mainoperation.h"
#include "mainhistory.h"
#include "users_information.h"
#include "mainoperation_student.h"
#include "tool.h"

Mainmine::Mainmine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainmine)
{
    ui->setupUi(this);
    users.user_init();
    QString id = users.User_getID();
    QString tors = users.User_getTorS();
    ui->label_name->setText("?");
    ui->label_ID->setText(id);
    if(tors == "t"){
        ui->label_comment->setText("teacher");
    }
    else{
        ui->label_comment->setText("student");
    }
}

Mainmine::~Mainmine()
{
    delete ui;
}

void Mainmine::on_mode_homepage_clicked()
{

    MainWindow *mainwin = new MainWindow();
    mainwin->show();
    this->close();
}

void Mainmine::on_mode_operation_clicked()
{
    users.user_init();
    this->close();
    if(users.User_getTorS() == "s"){
        Mainoperation_student *oper = new Mainoperation_student();
        oper->show();
    }
    else {
        Mainoperation *oper = new Mainoperation();
        oper->show();
    }
}

void Mainmine::on_mode_history_clicked()
{
    this->close();
    mainhistory *his = new mainhistory();
    his->show();
}

void Mainmine::on_loginagain_clicked()
{
    Login *t = new Login();
    t->show();
}
