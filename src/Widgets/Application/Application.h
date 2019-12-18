#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QTabWidget>
#include <QSettings>
#include "Logger/Logger.h"

class TestingTab;
class LoggerWidget;
class GeneralTab;
class SettingsTab;

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
    GeneralTab *_generalTab;
    TestingTab *_testingTab;
    LoggerWidget *_loggerWidget;
    SettingsTab *_settingsTab;
    Logger _logger;
};

#endif // APPLICATION_H
