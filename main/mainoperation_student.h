#ifndef MAINOPERATION_STUDENT_H
#define MAINOPERATION_STUDENT_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStandardItemModel>
#include "users_information.h"

namespace Ui {
class Mainoperation_student;
}

class Mainoperation_student : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mainoperation_student(QWidget *parent = nullptr);
    ~Mainoperation_student();
    users_information users;

    QStringListModel *Model;
    QStandardItemModel *ItemModel;

private slots:
    void on_mode_homepage_clicked();

    void on_mode_history_clicked();

    void on_mode_mine_clicked();

    void on_handout_clicked();

    void on_viewanswer_clicked();

private:
    Ui::Mainoperation_student *ui;
};

#endif // MAINOPERATION_STUDENT_H
