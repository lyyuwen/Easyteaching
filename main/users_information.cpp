#include "users_information.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QCoreApplication>

QString users_information::User_getID()
{
    user.ID.replace("\r\n","");
    return user.ID;
}

void users_information::User_setID(QString value)
{
    user.ID = value;
}

QString users_information::User_getkeycode()
{
    user.keycode.replace("\r\n","");
    return user.keycode;
}

void users_information::User_setkeycode(QString value)
{
    user.keycode = value;
}

QString users_information::User_getTorS()
{
    user.TorS.replace("\r\n","");
    return user.TorS;
}

void users_information::User_setTorS(QString value)
{
    user.TorS = value;
    QFile file(QCoreApplication::applicationDirPath() + "/config.txt");
    file.open(QIODevice::ReadWrite);
    QString newword;
    while(!file.atEnd()){
        QString a = file.readLine();
        if(a.startsWith("TorS=")){
            newword.append("TorS=" + value + "\r\n");
        }
        else{
            newword.append(a);
        }
    }
    file.close();
    file.open(QIODevice::Truncate|QIODevice::ReadWrite);
    file.write(newword.toUtf8());
    file.close();
}

QString users_information::User_getstate()
{
    user.state.replace("\r\n","");
    return user.state;
}

void users_information::User_setstate(QString value)
{
    user.state = value;
}

//--------------------------------------------------------------------

QString users_information::Other_getname(int num){
    others[num].name.replace("\r\n","");
    return others[num].name;
}

void users_information::Other_setname(QString){

}

QString users_information::Other_getnumber(int num){
    others[num].number.replace("\r\n","");
    return others[num].number;
}

void users_information::Other_setnumber(QString){

}

QString users_information::Other_getisFinish(int num){
    others[num].isFinish.replace("\r\n","");
    return others[num].isFinish;
}

void users_information::Other_setisFinish(QString number,QString percent){
    QFile file(QCoreApplication::applicationDirPath() + "/other_config.txt");
    file.open(QIODevice::ReadWrite);
    QString newword;
    while(!file.atEnd()){
        QString a = file.readLine();
        if(a.startsWith("name=")){
            QString b = file.readLine();
            if(b.startsWith("number=" + number.toUtf8())){
                newword.append(a);
                newword.append(b);
                qDebug()<<percent;
                newword.append("isFinish=" + percent.toUtf8() + "\r\n");

                file.readLine();
            }
            else{
                newword.append(a);
                newword.append(b);
            }
        }
        else {
            newword.append(a);
        }
    }
    file.close();
    file.open(QIODevice::Truncate|QIODevice::ReadWrite);
    file.write(newword.toUtf8());
    file.close();
}

void users_information::Other_add(QString name,QString number,QString isFinish){
    if(othernum < 1000){
        QFile file(QCoreApplication::applicationDirPath() + "/other_config.txt");
        file.open(QIODevice::ReadWrite);
        othernum = othernum + 1;
        QString newword;
        file.readLine();
        newword.append(QString::number(othernum) + "\r\n");
        while(!file.atEnd()){
            QString a = file.readLine();
            newword.append(a);
        }
        file.close();
        newword.append("name=" + name.toUtf8() + "\r\n");
        newword.append("number=" + number.toUtf8() + "\r\n");
        newword.append("isFinish=" + isFinish.toUtf8() + "\r\n");
        file.open(QIODevice::Truncate|QIODevice::ReadWrite);
        file.write(newword.toUtf8());
        file.close();
    }
}

void users_information::Other_del(QString name, QString number){
    QFile file(QCoreApplication::applicationDirPath() + "/other_config.txt");
    file.open(QIODevice::ReadWrite);
    othernum = othernum - 1;
    QString newword;
    file.readLine();
    newword.append(QString::number(othernum) + "\r\n");
    while(!file.atEnd()){
        QString a = file.readLine();
        if(a.startsWith("name=" + name.toUtf8())){
            QString b = file.readLine();
            if(b.startsWith("number=" + number.toUtf8())){
                b = file.readLine();
            }
            else{
                newword.append(a);
                newword.append(b);
            }
        }
        else {
            newword.append(a);
        }
    }
    file.close();
    file.open(QIODevice::Truncate|QIODevice::ReadWrite);
    file.write(newword.toUtf8());
    file.close();
}

//--------------------------------------------------------------------

void users_information::user_init(){
    QFile file(QCoreApplication::applicationDirPath() + "/config.txt");
    file.open(QIODevice::ReadOnly);
    while(!file.atEnd()){
        QString a = file.readLine();
        if(a.startsWith("state=")){
            user.state = a.replace("state=","");
        }
        if(a.startsWith("TorS=")){
            user.TorS = a.replace("TorS=","");
        }
        if(a.startsWith("ID=")){
            user.ID = a.replace("ID=","");
        }
        if(a.startsWith("keycode=")){
            user.keycode = a.replace("keycode=","");
        }
    }
    file.close();
}

void users_information::other_init(){
    QFile file(QCoreApplication::applicationDirPath() + "/other_config.txt");
    file.open(QIODevice::ReadOnly);
    QString num = file.readLine();
    othernum = num.toUtf8().toInt();
    if(!(othernum == 0)){
        for(int i = 0;i <= othernum;i++){
            for(int j = 3;j > 0;j--){
                QString a = file.readLine();
                if(a.startsWith("name=")){
                    others[i].name = a.replace("name=","");
                }
                if(a.startsWith("number=")){
                    others[i].number = a.replace("number=","");
                }
                if(a.startsWith("isFinish=")){
                    others[i].isFinish = a.replace("isFinish=","");
                }
            }
        }
    }
    file.close();
}
