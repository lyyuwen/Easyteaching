#include "mainoperation_student.h"
#include "ui_mainoperation_student.h"
#include "mainwindow.h"
#include "mainmine.h"
#include "mainhistory.h"
#include "tool.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItem>
#include <QDebug>

Mainoperation_student::Mainoperation_student(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainoperation_student)
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

Mainoperation_student::~Mainoperation_student()
{
    delete ui;
}

void Mainoperation_student::on_mode_homepage_clicked()
{
    this->close();
    MainWindow *mainwin = new MainWindow();
    mainwin->show();
}

void Mainoperation_student::on_mode_history_clicked()
{
    this->close();
    mainhistory *his = new mainhistory();
    his->show();
}

void Mainoperation_student::on_mode_mine_clicked()
{
    this->close();
    Mainmine *mine = new Mainmine();
    mine->show();
}

void Mainoperation_student::on_handout_clicked()
{
    Tool t;
    t.clear(users.User_getID());
    QString fileNew = QFileDialog::getOpenFileName(
            this,
            tr("打开文件"),
            "C:/",
            tr("picture(*.jpg)"));
    if (fileNew.isEmpty()) {
        QMessageBox::warning(this, "错误", "请重新选择");
    }
    else {
        QString fileDir = QCoreApplication::applicationDirPath();
        QFile copyfile(fileNew);
        copyfile.copy(fileDir + "/ocr/" + users.User_getID() + ".jpg");
        QString result = t.text_recognize(users.User_getID());
        qDebug()<<result.toUtf8();
        QFile file(fileDir.toUtf8() + "/" + users.user.ID + "work.txt");
        file.open(QIODevice::Truncate|QIODevice::ReadWrite);
        file.write(result.toUtf8());
        file.close();
        QMessageBox::about(this, "错误", "请重新选择");
    }
}

void Mainoperation_student::on_viewanswer_clicked()
{
    QString dir = QApplication::applicationDirPath();
    QFile file(dir + "/answer.txt");
    if(file.exists()){
        QString answer;
        file.open(QIODevice::ReadWrite);
        while (!file.atEnd()) {
            answer.append(file.readLine());
        }
        file.close();
        QMessageBox::about(this,"简·教·学",answer.toUtf8());
    }
    else{
        QMessageBox::about(this,"简·教·学","老师未上传答案！");
    }
}
