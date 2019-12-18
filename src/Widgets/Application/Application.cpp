#include "Application.h"
#include "ui_Application.h"
#include "Widgets/GeneralTab/GeneralTab.h"
#include "Widgets/TestingTab/TestingTab.h"
#include "Widgets/LoggerWidget/LoggerWidget.h"
#include "Widgets/SettingsTab/SettingsTab.h"

#include <QSplitter>
#include <QBoxLayout>
#include <QStyle>

Application::Application(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Application)
    , _generalTab(new GeneralTab(this))
    , _testingTab(new TestingTab(this))
    , _loggerWidget(new LoggerWidget("Logger:", 100, this))
    , _settingsTab(new SettingsTab(this))
    , _logger("Application")
{
    ui->setupUi(this);
    setWindowTitle("Badsurf");
    QObject::connect(&_logger, &Logger::logging, _loggerWidget, &LoggerWidget::log);
    _logger.setLevel(Logger::TRACE);
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
