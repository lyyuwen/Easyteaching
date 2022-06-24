QT += core gui
QT += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ACforString.cpp \
    main.cpp \
    mainhistory.cpp \
    mainmine.cpp \
    mainoperation.cpp \
    mainoperation_student.cpp \
    mainwindow.cpp \
    tool.cpp \
    users_information.cpp

HEADERS += \
    mainhistory.h \
    mainmine.h \
    mainoperation.h \
    mainoperation_student.h \
    mainwindow.h \
    tool.h \
    users_information.h

FORMS += \
    add_student.ui \
    all_push_work.ui \
    chooseword.ui \
    del_student.ui \
    edit_student.ui \
    handoutwork.ui \
    login.ui \
    mainhistory.ui \
    mainmine.ui \
    mainoperation.ui \
    mainoperation_student.ui \
    mainwindow.ui \
    view_student.ui

TRANSLATIONS += \
    easyteaching_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = icon.ico

# 以下为python配置
INCLUDEPATH += -I D:\python3\39\include
LIBS += -L D:\python3\39\libs -lpython39	
