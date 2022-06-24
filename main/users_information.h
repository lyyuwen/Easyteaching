#ifndef USERS_INFORMATION_H
#define USERS_INFORMATION_H
#include <QString>

class users_information
{
public:
    QString User_getstate();
    void User_setstate(QString);

    QString User_getID();
    void User_setID(QString);

    QString User_getkeycode();
    void User_setkeycode(QString);

    QString User_getTorS();
    void User_setTorS(QString);

    QString Other_getname(int);
    void Other_setname(QString);

    QString Other_getnumber(int);
    void Other_setnumber(QString);

    QString Other_getisFinish(int);
    void Other_setisFinish(QString,QString);

    void Other_add(QString,QString,QString);
    void Other_del(QString,QString);

    void user_init();
    void other_init();

    struct User{
        QString state;
        QString TorS;
        QString ID;
        QString keycode;
    }user;

    struct Other{
        QString name;
        QString number;
        QString isFinish;
    }others[1000];

    int othernum;
};

#endif // USERS_INFORMATION_H
