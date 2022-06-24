#ifndef MAINHISTORY_H
#define MAINHISTORY_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStandardItemModel>
#include "users_information.h"

namespace Ui {
class mainhistory;
}

class mainhistory : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainhistory(QWidget *parent = nullptr);
    ~mainhistory();
    users_information users;

    QStringListModel *Model;
    QStandardItemModel *ItemModel;

private slots:
    void on_mode_homepage_clicked();

    void on_mode_operation_clicked();

    void on_mode_mine_clicked();

private:
    Ui::mainhistory *ui;
};

#endif // MAINHISTORY_H
