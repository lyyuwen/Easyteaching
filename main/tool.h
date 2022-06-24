#ifndef TOOL_H
#define TOOL_H
#include <QString>
#include <QWidget>
#include <map>
#include "users_information.h"

int ACforString(char*,char*,char*,char*,char*,char*,char*);

namespace Ui {
class Login;
class chooseword;
class handoutwork;
class add_student;
class view_student;
class all_push_work;
class del_student;
class edit_student;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    users_information users;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;
};

//---------------------------------------------------------------------

class chooseword : public QWidget
{
    Q_OBJECT

public:
    explicit chooseword(QWidget *parent = nullptr);
    ~chooseword();

    void setText1(QString);
    void setText2(QString);
    void setText3(QString);
    void setText4(QString);
    void setText5(QString);
    void setText6(QString);
    void setOldText(QString);

private slots:
    void on_pushButton_clicked();

private:
    Ui::chooseword *ui;
};

//---------------------------------------------------------------------

class handoutwork : public QWidget
{
    Q_OBJECT

public:
    explicit handoutwork(QWidget *parent = nullptr);
    ~handoutwork();

private slots:
    void on_Button_esc_clicked();

    void on_Button_enter_clicked();

private:
    Ui::handoutwork *ui;
};

//---------------------------------------------------------------------

class add_student : public QWidget
{
    Q_OBJECT

public:
    explicit add_student(QWidget *parent = nullptr);
    ~add_student();
    users_information users;

private slots:
    void on_true_button_clicked();

    void on_pushButton_2_clicked();

    void on_excel_push_clicked();

private:
    Ui::add_student *ui;
};

//---------------------------------------------------------------------

class view_student : public QWidget
{
    Q_OBJECT

public:
    explicit view_student(QWidget *parent = nullptr);
    ~view_student();
    users_information users;

private:
    Ui::view_student *ui;
};

//---------------------------------------------------------------------

class all_push_work : public QWidget
{
    Q_OBJECT

public:
    explicit all_push_work(QWidget *parent = nullptr);
    ~all_push_work();
    users_information users;

private slots:

    void on_true_button_clicked();

    void on_false_button_clicked();

private:
    Ui::all_push_work *ui;
};

//---------------------------------------------------------------------

class del_student : public QWidget
{
    Q_OBJECT

public:
    explicit del_student(QWidget *parent = nullptr);
    ~del_student();
    users_information users;

private slots:
    void on_flase_button_clicked();

    void on_true_button_clicked();

private:
    Ui::del_student *ui;
};

//---------------------------------------------------------------------

class edit_student : public QWidget
{
    Q_OBJECT

public:
    explicit edit_student(QWidget *parent = nullptr);
    ~edit_student();
    users_information users;

private slots:
    void on_flase_button_clicked();

    void on_true_button_clicked();

private:
    Ui::edit_student *ui;
};

//---------------------------------------------------------------------

class Tool
{

public:
    void isFileExist();
    void keyword_extraction(QString);
    void clear(QString);
    QString text_recognize(QString);

};

#endif // TOOL_H
