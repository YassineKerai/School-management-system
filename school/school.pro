QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutapp.cpp \
    addcourse.cpp \
    addstudent.cpp \
    addteacher.cpp \
    courseview.cpp \
    coursewindow.cpp \
    date.cpp \
    editexam.cpp \
    main.cpp \
    mainclasses.cpp \
    mainwindow.cpp \
    studentview.cpp \
    studentwindow.cpp \
    teacherview.cpp \
    teacherwindow.cpp

HEADERS += \
    aboutapp.h \
    addcourse.h \
    addstudent.h \
    addteacher.h \
    courseview.h \
    coursewindow.h \
    date.h \
    editexam.h \
    mainclasses.h \
    mainwindow.h \
    studentview.h \
    studentwindow.h \
    teacherview.h \
    teacherwindow.h

FORMS += \
    aboutapp.ui \
    addcourse.ui \
    addstudent.ui \
    addteacher.ui \
    courseview.ui \
    coursewindow.ui \
    editexam.ui \
    mainwindow.ui \
    studentview.ui \
    studentwindow.ui \
    teacherview.ui \
    teacherwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
