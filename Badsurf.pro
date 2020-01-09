QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    src

SOURCES += \
    src/Logger/Logger.cpp \
    src/Utils/StringUtils.cpp \
    src/Widgets/Application/Application.cpp \
    src/Widgets/GeneralTab/GeneralTab.cpp \
    src/Widgets/LoggerWidget/LoggerWidget.cpp \
    src/Widgets/SettingsTab/SettingsTab.cpp \
    src/Widgets/SmartTab/SmartTab.cpp \
    src/Widgets/TestingTab/Test.cpp \
    src/Widgets/TestingTab/TestingTab.cpp \
    src/main.cpp


HEADERS += \
    src/Logger/Logger.h \
    src/Utils/StringUtils.h \
    src/Widgets/Application/Application.h \
    src/Widgets/GeneralTab/GeneralTab.h \
    src/Widgets/GeneralTab/HeaderModel.h \
    src/Widgets/LoggerWidget/LoggerWidget.h \
    src/Widgets/SettingsTab/SettingsTab.h \
    src/Widgets/SmartTab/SmartTab.h \
    src/Widgets/TestingTab/Test.h \
    src/Widgets/TestingTab/TestingTab.h


FORMS += \
    src/Widgets/Application/Application.ui \
    src/Widgets/GeneralTab/GeneralTab.ui \
    src/Widgets/LoggerWidget/LoggerWidget.ui \
    src/Widgets/SettingsTab/SettingsTab.ui \
    src/Widgets/SmartTab/SmartTab.ui \
    src/Widgets/TestingTab/TestingTab.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/lib/ -lbadsurf

INCLUDEPATH += $$PWD/lib/include
DEPENDPATH += $$PWD/lib/include
