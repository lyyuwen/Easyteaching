#include "tool.h"
#include "ui_login.h"
#include "ui_chooseword.h"
#include "ui_handoutwork.h"
#include "ui_add_student.h"
#include "ui_view_student.h"
#include "ui_all_push_work.h"
#include "ui_del_student.h"
#include "ui_edit_student.h"
#include "users_information.h"
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QMessageBox>
#include <Python.h>
#include <QAxObject>
#include <QFileDialog>
#include <windows.h>
#include <QtCore>
#include <QString>
#include <QStandardItemModel>
#include<iostream>
#include <string.h>
#include <map>
#include <queue>

using namespace std;

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    users.user_init();
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QString Input_ID = ui->Input_ID->text();
    QString Input_Keyword = ui->Input_Keyword->text();
    QString Input_TorS = ui->comboBox->currentText();

    if(Input_ID.toUtf8() == users.User_getID()){
        if(Input_Keyword == users.User_getkeycode()){
            this->close();
            QMessageBox::about(this, tr("登陆成功"), tr("您已登陆成功！"));
            if(Input_TorS == "教师"){
                users.User_setTorS("t");
            }
            else{
                users.User_setTorS("s");
            }
        }
        else{
            QMessageBox::warning(this, "错误", "密码输入错误！");
        }
    }
    else{
        QMessageBox::warning(this, "错误", "ID输入错误！");
    }
}
//---------------------------------------------------------------------

chooseword::chooseword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chooseword)
{
    ui->setupUi(this);
    QString text;
    QFile answers(QApplication::applicationDirPath() + "/answer.txt");
    answers.open(QIODevice::ReadWrite);
    while (!answers.atEnd()) {
        QString a = answers.readLine();
        text.append(a);
    }
    answers.close();
    ui->text_answers->setText(text.toUtf8());
}

chooseword::~chooseword()
{
    delete ui;
}

void chooseword::setText1(QString what){
    ui->textkeyword1->setText(what.toUtf8());
}

void chooseword::setText2(QString what){
    ui->textkeyword2->setText(what.toUtf8());
}

void chooseword::setText3(QString what){
    ui->textkeyword3->setText(what.toUtf8());
}

void chooseword::setText4(QString what){
    ui->textkeyword4->setText(what.toUtf8());
}

void chooseword::setText5(QString what){
    ui->textkeyword5->setText(what.toUtf8());
}

void chooseword::setText6(QString what){
    ui->textkeyword6->setText(what.toUtf8());
}

void chooseword::setOldText(QString what){
    ui->text_answers->setText(what.toUtf8());
}

void chooseword::on_pushButton_clicked()
{
    QString key1 = ui->textkeyword1->text();
    QString key2 = ui->textkeyword2->text();
    QString key3 = ui->textkeyword3->text();
    QString key4 = ui->textkeyword4->text();
    QString key5 = ui->textkeyword5->text();
    QString key6 = ui->textkeyword6->text();

    QString path = QApplication::applicationDirPath();
    QFile file(path + "/answers.txt");
    if(file.exists()){
        file.open(QIODevice::WriteOnly|QIODevice::Truncate);
    }
    else {
        file.open(QIODevice::ReadWrite);
    }
    file.write(key1.toUtf8() + "\r\n");
    file.write(key2.toUtf8() + "\r\n");
    file.write(key3.toUtf8() + "\r\n");
    file.write(key4.toUtf8() + "\r\n");
    file.write(key5.toUtf8() + "\r\n");
    file.write(key6.toUtf8() + "\r\n");
    file.close();
    this->close();
}

//---------------------------------------------------------------------

handoutwork::handoutwork(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::handoutwork)
{
    ui->setupUi(this);
}

handoutwork::~handoutwork()
{
    delete ui;
}

void handoutwork::on_Button_enter_clicked()
{
    QString work = ui->textEdit->toPlainText();
    QString fileDir = QCoreApplication::applicationDirPath();
    QFile file(fileDir + "/handoutwork.txt");
    file.open(QIODevice::ReadWrite);
    file.write(work.toUtf8() + "\r\n");
    file.close();
    this->close();
}

void handoutwork::on_Button_esc_clicked()
{
    this->close();
}

//---------------------------------------------------------------------

add_student::add_student(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_student)
{
    ui->setupUi(this);
    users.other_init();
}

add_student::~add_student()
{
    delete ui;
}

void add_student::on_true_button_clicked()
{
    QString name = ui->input_name->text();
    QString number = ui->input_number->text();
    this->close();
    users.Other_add(name,number,"n");
}

void add_student::on_pushButton_2_clicked()
{
    this->close();
}

void add_student::on_excel_push_clicked()
{
    QAxObject *excel = new QAxObject(this);
    excel->setControl("Excel.Application");
    excel->setProperty("Visible", false);
    excel->setProperty("DisplayAlerts", true);
    QAxObject *workbooks = excel->querySubObject("WorkBooks");
    QString str = QFileDialog::getOpenFileName(this,"打开",
                         QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),"Excel文件(*.xls *.xlsx)");
    workbooks->dynamicCall("Open(const QString&)", str);
    QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
    QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)",1);
    QAxObject *usedRange = worksheet->querySubObject("UsedRange");
    QVariant var = usedRange->dynamicCall("Value");
    QList<QList<QVariant>> excel_list;
    QVariantList varRows =var.toList();
    if(varRows.isEmpty()){
         return;
     }
    const int row_count = varRows.size();
    QVariantList rowData;
    for(int i=0;i<row_count;++i)
    {

        rowData = varRows[i].toList();
        excel_list.push_back(rowData);
    }
    for (int j = 0;j < excel_list.count();j++) {
        QString name = excel_list.at(j).at(0).toString();
        QString number = excel_list.at(j).at(1).toString();
        users.Other_add(name,number,"n");
    }

    workbook->dynamicCall( "Close(Boolean)", false );
    excel->dynamicCall( "Quit(void)" );
    delete excel;
    this->close();
}

//---------------------------------------------------------------------

view_student::view_student(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::view_student)
{
    ui->setupUi(this);
    users.other_init();
    qDebug()<<users.othernum;
    if(users.othernum == 0){}
    else{
        QStandardItemModel* model = new QStandardItemModel(this);
        for (int i = 0;i <= users.othernum;i++) {
            model->setItem(i, 0, new QStandardItem(users.Other_getname(i)));
            model->setItem(i, 1, new QStandardItem(users.Other_getnumber(i)));
            model->setItem(i, 2, new QStandardItem(users.Other_getisFinish(i)));
        }
        ui->tableView->setModel(model);
    }
}

view_student::~view_student()
{
    delete ui;
}

//---------------------------------------------------------------------

all_push_work::all_push_work(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::all_push_work)
{
    ui->setupUi(this);
    users.other_init();
}

all_push_work::~all_push_work()
{
    delete ui;
}

void all_push_work::on_true_button_clicked()
{
    QString path = ui->input_path->text();
    //获取文件夹下的文件名称
    QDir dir(path);
    if (!dir.exists()) {
        QMessageBox::warning(this, "错误", "文件夹不存在！");
    }
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList filters;
    filters << "*.jpg";
    dir.setNameFilters(filters);
    QStringList notlist = dir.entryList();
    if (notlist.count() <= 0)
    {
        QMessageBox::warning(this, "错误", "错误！");
    }
    QStringList list;
    for (int i = 0;i < notlist.count();i++) {
        for (int j = 0;j < users.othernum;j++) {
            if(notlist[i] == (users.Other_getnumber(j) + ".jpg")){
                list.append(notlist[i]);
            }
        }
    }
    if (list.count() <= 0)
    {
        QMessageBox::warning(this, "错误", "错误！");
    }
    qDebug()<<list;

    QString fileDir = QCoreApplication::applicationDirPath();
    QFile jpg_list(fileDir + "/list_jpg.txt");
    if(!jpg_list.exists()){
        jpg_list.open(QIODevice::ReadWrite);
        for(int i = 0;i < list.count();i++){
            jpg_list.write(list[i].toUtf8() + "\r\n");
        }
        jpg_list.close();
    }
    else{
        jpg_list.open(QIODevice::ReadWrite|QIODevice::Append);
        for(int i = 0;i < list.count();i++){
            jpg_list.write(list[i].toUtf8() + "\r\n");
        }
        jpg_list.close();
    }

    fileDir.append("/ocr/");
    for (int i = 0;i < list.count();i++) {
        QFile copyimg(path + "/" + list[i].toUtf8());
        QFile img(fileDir + list[i].toUtf8());
        if(img.exists()){
            img.remove();
        }
        copyimg.copy(fileDir + list[i].toUtf8());
    }

    this->close();

    Tool t;
    for (int i = 0;i < list.count();i++) {
        list[i].replace(".jpg","");
        QFile file(fileDir + list[i].toUtf8() + ".txt");
        QString result = t.text_recognize(list[i]);
        qDebug()<<result.toUtf8();
        file.open(QIODevice::ReadWrite);
        file.write(result.toUtf8());
        file.close();
        t.clear(list[i] + ".jpg");
    }
}

void all_push_work::on_false_button_clicked()
{
    this->close();
}

//---------------------------------------------------------------------
del_student::del_student(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::del_student)
{
    ui->setupUi(this);
    users.other_init();
}

del_student::~del_student()
{
    delete ui;
}

void del_student::on_true_button_clicked()
{
    QString del_name = ui->name_input->text();
    QString del_number = ui->number_input->text();
    users.Other_del(del_name,del_number);
    this->close();
}

void del_student::on_flase_button_clicked()
{
    this->close();
}


//---------------------------------------------------------------------

edit_student::edit_student(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit_student)
{
    ui->setupUi(this);
    users.other_init();
}

edit_student::~edit_student()
{
    delete ui;
}

void edit_student::on_true_button_clicked()
{
    QString oldname = ui->name_input->text();
    QString oldnumber = ui->number_input->text();
    QString newname = ui->name_input_new->text();
    QString newnumber = ui->number_input_new->text();
    users.Other_del(oldname,oldnumber);
    users.Other_add(newname,newnumber,"n");
    this->close();
}

void edit_student::on_flase_button_clicked()
{
    this->close();
}

//---------------------------------------------------------------------

void Tool::isFileExist()
{
    QString fileDir = QCoreApplication::applicationDirPath();
    QFile file(fileDir + "/config.txt");
    QFile other_file(fileDir + "/other_config.txt");
    if(!file.exists())
    {
      file.open(QIODevice::ReadWrite);
      QString state,TorS,ID,keycode;
      state = "none";
      TorS = "t";
      ID = "";
      keycode = "";
      file.write("state=" + state.toUtf8() + "\r\n");
      file.write("TorS=" + TorS.toUtf8() + "\r\n");
      file.write("ID=" + ID.toUtf8() + "\r\n");
      file.write("keycode=" + keycode.toUtf8() + "\r\n");
      file.close();
    }
    if(!other_file.exists()){
        other_file.open(QIODevice::ReadWrite);
        QString a = "0";
        other_file.write(a.toUtf8() + "\r\n");
        other_file.close();
    }
}

void Tool::keyword_extraction(QString intext)
{
    QString fileDir = QCoreApplication::applicationDirPath();
    QString pythonhome = fileDir;
    pythonhome.append("/39/");
    std::wstring wstr = pythonhome.toStdWString();
    const wchar_t* cPath = wstr.c_str();
    Py_SetPythonHome(cPath);
    Py_Initialize();
    if( !Py_IsInitialized() ){
        qDebug()<<"123";
    }

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(" + fileDir.toUtf8() + ")");

    PyObject* pModule = PyImport_ImportModule("keyword_extraction");
    if (! pModule){
       qDebug()<<QObject::tr("Can't open python file\n");

    }
    PyObject *pArgs = PyTuple_New(2);
    std::string str1 = intext.toStdString();
    std::string str2 = fileDir.toStdString();
    char* text = (char*)str1.data();
    char* path = (char*)str2.data();
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", text));
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("s", path));    
    PyObject* pFun = PyObject_GetAttrString(pModule,"keyword_extraction");
    PyObject* run = PyObject_CallObject(pFun,pArgs);

    Py_DECREF(pModule);
    Py_DECREF(pArgs);
    Py_DECREF(pFun);
    Py_DECREF(run);

    Py_Finalize();

    QString st1 = "";
    QString st2 = "";
    QString st3 = "";
    QString st4 = "";
    QString st5 = "";
    QString st6 = "";

    QFile file(fileDir + "/answers.txt");
    file.open(QIODevice::ReadOnly);
    QString line = file.readLine();
    st1.append(line);
    line = file.readLine();
    st2.append(line);
    line = file.readLine();
    st3.append(line);
    line = file.readLine();
    st4.append(line);
    line = file.readLine();
    st5.append(line);
    line = file.readLine();
    st6.append(line);
    file.close();

    QFile oldanswer(fileDir + "/answer.txt");
    oldanswer.open(QIODevice::ReadOnly);
    QString pastanswer;
    while (!oldanswer.atEnd()) {
        pastanswer.append(oldanswer.readLine());
    }
    oldanswer.close();

    chooseword *choose = new chooseword();
    choose->setText1(st1.toUtf8());
    choose->setText2(st2.toUtf8());
    choose->setText3(st3.toUtf8());
    choose->setText4(st4.toUtf8());
    choose->setText5(st5.toUtf8());
    choose->setText6(st6.toUtf8());
    choose->setOldText(pastanswer.toUtf8());
    choose->show();
}

QString Tool::text_recognize(QString file){

    QString result = "";
    QString path = QCoreApplication::applicationDirPath();
    QString filename = path + "/ocr/" + file.toUtf8();
    QString pythonhome = path;
    pythonhome.append("/39/");
    std::wstring wstr = pythonhome.toStdWString();
    const wchar_t* cPath = wstr.c_str();
    Py_SetPythonHome(cPath);

    Py_Initialize();
    if( !Py_IsInitialized() ){
        qDebug()<<"123";
    }

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(" + path.toUtf8() + ")");

    PyObject* pModule = PyImport_ImportModule("text_recognize");
    if (! pModule){
       qDebug()<<QObject::tr("Can't open python file\n");

    }
    PyObject *pArgs = PyTuple_New(1);
    std::string str1 = filename.toStdString();
    char* filenamec = (char*)str1.data();
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", filenamec));
    PyObject* pFun = PyObject_GetAttrString(pModule,"text_recognize");
    PyObject_CallObject(pFun,pArgs);

    Py_DECREF(pModule);
    Py_DECREF(pArgs);
    Py_DECREF(pFun);

    Py_Finalize();

    QFile resultfile(path + "/ocr/" + filename + ".txt");
    resultfile.open(QIODevice::ReadOnly);
    while(!resultfile.atEnd()){
        result.append(resultfile.readLine());
    }

    /*
    QProcess p1(nullptr),p2(nullptr);
    QString curPath = QCoreApplication::applicationDirPath();//获取当前应用程序目录
    curPath.append("/ocr");
    p1.setWorkingDirectory(curPath); //设置工作目录
    p1.start(curPath + "/run-test.bat");  //运行脚本文件

    if(p1.waitForFinished(1000000)){
        QFile answersfile(curPath + "/result.txt");
        answersfile.open(QIODevice::ReadWrite);
        QString n;
        while (!answersfile.atEnd())
        {
            QByteArray line = answersfile.readLine();
            QString str(line);
            n.append(line);
            if(n.contains("FullDetectTime")){
                while (!answersfile.atEnd()) {
                    line = answersfile.readLine();
                    QString str(line);
                    result.append(line);
                }
                break;
            }
            n = "";
        }
    }
    */

    return result;
}

void Tool::clear(QString removefile){
    QString curPath = QCoreApplication::applicationDirPath();
    curPath.append("/ocr/");

    /*
    QProcess p(nullptr);
    p.setWorkingDirectory(curPath);
    p.start(curPath + "/clear.bat");
    if(p.waitForFinished(10000)){
        return true;
    }
    else{
        return false;
    }
    */

    QFile::remove(curPath + removefile);
}
