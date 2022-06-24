#ifndef MAINOPERATION_H
#define MAINOPERATION_H

#include <QMainWindow>
#include "users_information.h"

namespace Ui {
class Mainoperation;
}

class Mainoperation : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mainoperation(QWidget *parent = nullptr);
    ~Mainoperation();
    users_information users;

    int correct(QStringList,QString);

private slots:
    void on_mode_homepage_clicked();

    void on_upload_answer_clicked();

    void on_mode_mine_clicked();

    void on_handout_clicked();

    void on_mode_history_clicked();

    void on_start_correct_clicked();

    void on_add_student_clicked();

    void on_view_student_clicked();

    void on_all_push_work_clicked();

    void on_remove_student_clicked();

    void on_edit_student_clicked();

private:
    Ui::Mainoperation *ui;
};

#endif // MAINOPERATION_H
