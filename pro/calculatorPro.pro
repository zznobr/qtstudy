QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addratedialog.cpp \
    baseinputwidget.cpp \
    binaryconversionmodule.cpp \
    bitwise.cpp \
    capacityconversionmodule.cpp \
    datawidget.cpp \
    exchangerateconversionmodule.cpp \
    historywidget.cpp \
    inputwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    mylineedit.cpp \
    sciinputwidget.cpp

HEADERS += \
    addratedialog.h \
    baseinputwidget.h \
    binaryconversionmodule.h \
    bitwise.h \
    capacityconversionmodule.h \
    datawidget.h \
    exchangerateconversionmodule.h \
    historywidget.h \
    inputwidget.h \
    mainwindow.h \
    mylineedit.h \
    sciinputwidget.h

FORMS += \
    addratedialog.ui \
    baseinputwidget.ui \
    binaryconversionmodule.ui \
    bitwise.ui \
    capacityconversionmodule.ui \
    datawidget.ui \
    exchangerateconversionmodule.ui \
    historywidget.ui \
    inputwidget.ui \
    mainwindow.ui \
    sciinputwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
