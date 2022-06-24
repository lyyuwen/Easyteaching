#ifndef MAINMINE_H
#define MAINMINE_H

#include <QMainWindow>
#include "users_information.h"

namespace Ui {
class Mainmine;
}

class Mainmine : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mainmine(QWidget *parent = nullptr);
    ~Mainmine();

    users_information users;

private slots:
    void on_mode_homepage_clicked();

    void on_mode_operation_clicked();

    void on_mode_history_clicked();

    void on_loginagain_clicked();

private:
    Ui::Mainmine *ui;
};

#endif // MAINMINE_H
