#include "mainoperation.h"
#include "ui_mainoperation.h"
#include "mainwindow.h"
#include "mainmine.h"
#include "mainhistory.h"
#include "users_information.h"
#include "tool.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QAxObject>
#include <math.h>

Mainoperation::Mainoperation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainoperation)
{
    ui->setupUi(this);
    users.other_init();
    QString fileDir = QCoreApplication::applicationDirPath();
    QFile file(fileDir + "/answers.txt");
    file.open(QIODevice::ReadWrite);
    QByteArray line = file.readLine();
    QString a = line;
    ui->label_1->setText(a.remove("\r\n",Qt::CaseInsensitive));

    file.readLine();
    line = file.readLine();
    a = line;
    ui->label_2->setText(a.remove("\r\n",Qt::CaseInsensitive));

    file.readLine();
    line = file.readLine();
    a = line;
    ui->label_3->setText(a.remove("\r\n",Qt::CaseInsensitive));

    file.readLine();
    line = file.readLine();
    a = line;
    ui->label_4->setText(a.remove("\r\n",Qt::CaseInsensitive));

    file.readLine();
    line = file.readLine();
    a = line;
    ui->label_5->setText(a.remove("\r\n",Qt::CaseInsensitive));

    file.readLine();
    line = file.readLine();
    a = line;
    ui->label_6->setText(a.remove("\r\n",Qt::CaseInsensitive));
    file.close();
    ui->label_student_number->setText(QString::number(users.othernum));
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);
}

Mainoperation::~Mainoperation()
{
    delete ui;
}

void Mainoperation::on_mode_homepage_clicked()
{
    MainWindow *mainwin = new MainWindow();
    mainwin->show();
    this->close();
}

void Mainoperation::on_upload_answer_clicked()
{
    QString fileNew = QFileDialog::getOpenFileName(
            this,
            tr("打开文件"),
            "C:/",
            tr("text files(*.txt)"));
    if (fileNew.isEmpty()) {
        QMessageBox::warning(this, "错误", "请重新选择");
    }
    else {
        QString fileDir = QCoreApplication::applicationDirPath();
        QFile file(fileDir + "/answer.txt");
        QString n = "";
        if(file.exists()){
            QFile::remove(fileDir + "/answer.txt");
        }

        QFile copyfile(fileNew);
        copyfile.copy(fileDir + "/answer.txt");
        file.open(QIODevice::ReadWrite);
        while (!file.atEnd()) {
            QString line = file.readLine();
            n.append(line);
        }
        file.close();
        Tool t;
        t.keyword_extraction(n);
    }
}

void Mainoperation::on_mode_mine_clicked()
{
    Mainmine *mine = new Mainmine();
    mine->show();
    this->close();
}

void Mainoperation::on_handout_clicked()
{
    handoutwork *handout = new handoutwork();
    handout->show();
}

void Mainoperation::on_mode_history_clicked()
{
    mainhistory *his = new mainhistory();
    his->show();
    this->close();
}

void Mainoperation::on_start_correct_clicked()
{
    QMessageBox::about(this,"注意！！！","批改时请勿离开此界面！！！\r\n批改时请勿离开此界面！！！\r\n批改时请勿离开此界面！！！");
    QString path = QCoreApplication::applicationDirPath();
    QFile answers_file(path.toUtf8() + "/answers.txt");
    QStringList key;
    if(!answers_file.exists()){
        answers_file.close();
    }
    else{
        answers_file.open(QIODevice::ReadWrite);
        int i = 0;
        while(!answers_file.atEnd()){
            key.append(answers_file.readLine());
            key[i] = key[i].replace("\r\n","");
            i++;
        }
        answers_file.close();
        QFile list(path + "/list_jpg.txt");
        if(!list.exists()){
            QMessageBox::warning(this, "错误", "学生作业图片未上传！");
        }
        else{
            list.open(QIODevice::ReadWrite);
            int now = 0;
            int will = 0;
            while (!list.atEnd()) {
                list.readLine();
                will++;
            }
            list.close();
            list.open(QIODevice::ReadWrite);
            while(!list.atEnd()){
                QString jpg = list.readLine();
                jpg.replace("\r\n","");
                jpg.replace("jpg","txt");
                QFile file(path.toUtf8() + "/ocr/" + jpg.toUtf8());
                if(!file.exists()){
                    QMessageBox::warning(this, "错误", "学生作业图片错误！");
                }
                else{
                    file.open(QIODevice::ReadWrite);
                    QString text;
                    while(!file.atEnd()){
                        text.append(file.readLine());
                    }
                    file.close();
                    jpg.replace(".txt","");
                    int percent_true = correct(key,text);
                    if(percent_true >= 100){
                        percent_true = 100;
                    }
                    QString percent = QString::number(percent_true);
                    users.Other_setisFinish(jpg,percent);
                    now++;
                    ui->progressBar->setValue(((int)floor(now/will)) * 100);
                }
            }
            list.close();
            /*
            QFile progressBar(path + "/progressbar.txt");
            int progress = (int)floor(now/will) * 100;
            QString progresspercent = QString::number(progress);
            if(!progressBar.exists()){
                progressBar.open(QIODevice::ReadWrite);
                progressBar.write(progresspercent.toUtf8());
                progressBar.close();
            }
            else{
                progressBar.open(QIODevice::WriteOnly|QIODevice::Truncate);
                progressBar.write(progresspercent.toUtf8());
                progressBar.close();
            }
            */
        }
    }
}

void Mainoperation::on_add_student_clicked()
{
    add_student *add = new add_student();
    add->show();

}

void Mainoperation::on_view_student_clicked()
{
    view_student *view = new view_student();
    view->show();
}

void Mainoperation::on_all_push_work_clicked()
{
    all_push_work *push = new all_push_work();
    push->show();
}

int Mainoperation::correct(QStringList key,QString text){
    std::string s1 = key[0].toStdString();
    std::string s2 = key[1].toStdString();
    std::string s3 = key[2].toStdString();
    std::string s4 = key[3].toStdString();
    std::string s5 = key[4].toStdString();
    std::string s6 = key[5].toStdString();
    std::string str = text.toStdString();
    char* key1 = (char*)s1.data();
    char* key2 = (char*)s2.data();
    char* key3 = (char*)s3.data();
    char* key4 = (char*)s4.data();
    char* key5 = (char*)s5.data();
    char* key6 = (char*)s6.data();
    char* the_text = (char*)str.data();

    int truenum = ACforString(key1,key2,key3,key4,key5,key6,the_text);
    truenum = truenum*16.6;
    return truenum;
}

void Mainoperation::on_remove_student_clicked()
{
    del_student *del = new del_student();
    del->show();
}

void Mainoperation::on_edit_student_clicked()
{
    edit_student *edit = new edit_student();
    edit->show();
}
