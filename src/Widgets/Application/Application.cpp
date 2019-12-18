#include "Application.h"
#include "ui_Application.h"
#include "Widgets/GeneralTab/GeneralTab.h"
#include "Widgets/TestingTab/TestingTab.h"
#include "Widgets/LoggerWidget/LoggerWidget.h"
#include "Widgets/SettingsTab/SettingsTab.h"

#include <QSplitter>
#include <QBoxLayout>
#include <QStyle>
#include <QDebug>

Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Application)
    , _logger("Application")
    , _loggerWidget(new LoggerWidget("Logger:", 100, this))
    , _generalTab(new GeneralTab(this))
    , _testingTab(new TestingTab(this))
    , _settingsTab(new SettingsTab(this))
{
    ui->setupUi(this);
    setWindowTitle("Badsurf");
    QObject::connect(&_logger, &Logger::logging, _loggerWidget, &LoggerWidget::log);
    QObject::connect(_settingsTab, &SettingsTab::enabledLogInFile, &_logger, &Logger::setLogInFile);
    QObject::connect(_settingsTab, &SettingsTab::logPathChanged, &_logger, &Logger::setLogPath);
    QObject::connect(_settingsTab, &SettingsTab::levelChanged, &_logger, &Logger::setLevel);

    _logger.setLogInFile(_settingsTab->settings()->value("/enableLogging").toBool());
    _logger.setLogPath(_settingsTab->settings()->value("/logPath").toString().toStdString());
    _logger.setLevel(_settingsTab->settings()->value("/logLevel").toInt());

    LOG_TRACE(_logger)



    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->insertTab(0, _generalTab, "General");
    tabWidget->insertTab(1, _testingTab, "Test");
    tabWidget->insertTab(2, _settingsTab, "Settings");

    ui->verticalLayout->addWidget(tabWidget);
    ui->verticalLayout->addWidget(_loggerWidget);
}

Application::~Application()
{
    delete ui;
}
