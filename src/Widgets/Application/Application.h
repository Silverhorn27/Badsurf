#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QTabWidget>
#include <QSettings>
#include "Logger/Logger.h"
#include <badsurflib/objects_def.hpp>
#include <badsurflib/badsurflib.hpp>
#include <badsurflib/device.hpp>

class GeneralTab;
class SmartTab;
class TestingTab;
class SettingsTab;
class LoggerWidget;

namespace Ui {
class Application;
}

class Application : public QMainWindow
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = nullptr);
    ~Application();

public slots:
    void currentDevChanged(DC_Dev *dev);

private:
    Ui::Application *ui;
    Logger _logger;
    LoggerWidget *_loggerWidget;
    GeneralTab *_generalTab;
    SmartTab *_smartTab;
    TestingTab *_testingTab;
    SettingsTab *_settingsTab;
    DC_Dev *_currentDev;
};

#endif // APPLICATION_H
