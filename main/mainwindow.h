#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "users_information.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    users_information users;

private slots:

    void on_mode_operation_clicked();

    void on_mode_mine_clicked();

    void on_mode_history_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
