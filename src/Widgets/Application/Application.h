#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QTabWidget>
#include <QSettings>
#include "Logger/Logger.h"

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

private:
    Ui::Application *ui;
    Logger _logger;
    LoggerWidget *_loggerWidget;
    GeneralTab *_generalTab;
    SmartTab *_smartTab;
    TestingTab *_testingTab;
    SettingsTab *_settingsTab;
};

#endif // APPLICATION_H
