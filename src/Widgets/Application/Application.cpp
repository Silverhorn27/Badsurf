#include "Application.h"
#include "ui_Application.h"
#include "Widgets/GeneralTab/GeneralTab.h"
#include "Widgets/SmartTab/SmartTab.h"
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
    , _smartTab(new SmartTab(this))
    , _testingTab(new TestingTab(this))
    , _settingsTab(new SettingsTab(this))
    , _currentDev(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Badsurf");

    QObject::connect(_generalTab, &GeneralTab::devChanged, this, &Application::currentDevChanged);
    QObject::connect(&_logger, &Logger::logging, _loggerWidget, &LoggerWidget::log);
    QObject::connect(_settingsTab, &SettingsTab::enabledLogInFile, &_logger, &Logger::setLogInFile);
    QObject::connect(_settingsTab, &SettingsTab::logPathChanged, &_logger, &Logger::setLogPath);
    QObject::connect(_settingsTab, &SettingsTab::levelChanged, &_logger, &Logger::setLevel);

    _logger.setLogInFile(_settingsTab->settings()->value("/enableLogging").toBool());
    _logger.setLogPath(_settingsTab->settings()->value("/logPath").toString().toStdString());
    _logger.setLevel(_settingsTab->settings()->value("/logLevel").toInt());
    _currentDev = _generalTab->currentDev();
    currentDevChanged(_currentDev);

    LOG_TRACE(_logger)

    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->insertTab(0, _generalTab, "General");
    tabWidget->insertTab(1, _smartTab, "S.M.A.R.T");
    tabWidget->insertTab(2, _testingTab, "Test");
    tabWidget->insertTab(3, _settingsTab, "Settings");

    ui->verticalLayout->addWidget(tabWidget);
    ui->verticalLayout->addWidget(_loggerWidget);
}

Application::~Application()
{
    delete ui;
}

void Application::currentDevChanged(DC_Dev *dev)
{
    _logger.log(Logger::INFO, QString("Selected disk: ").toStdString()
                + QString::fromLatin1(dev->model_str).toStdString());
    _smartTab->setCurrentDev(dev);
    _testingTab->setCurrentDev(dev);
}

