#include "SettingsTab.h"
#include "ui_SettingsTab.h"
#include "Logger/Logger.h"
#include <QDir>
#include <QDebug>
#include <QFileDialog>

const static QString configPath = QDir::homePath() + "/.config/Andrey and Stas/Badsurf.ini";
const static QString logPath = QDir::currentPath() + "/log.txt";

SettingsTab::SettingsTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsTab)
    , m_setttings(new QSettings(QSettings::IniFormat, QSettings::UserScope,
                                "Andrey and Stas", "Badsurf", this))
{
    ui->setupUi(this);
    ui->logBox->setFlat(true);
    ui->behaviorBox->setFlat(true);
    ui->configBox->setFlat(true);
    ui->ioBox->setFlat(true);
    ui->comboBox->addItems(Logger::getAllLevels());


    if (!m_setttings->value("/settingsExists", false).toBool()) {
        on_defaultButton_clicked();
        on_applyButton_clicked();
        m_setttings->setValue("/settingsExists", true);
    } else {
        setSettings();
    }
}

void SettingsTab::setDefaultSettings()
{
    delete m_setttings;
    m_setttings = new QSettings(configPath, QSettings::IniFormat, this);
    setSettings();
    ui->configLineEdit->setText(configPath);
    ui->logLineEdit->setText(logPath);
    ui->rbAta->setChecked(true);
    ui->rbPosix->setChecked(false);
    ui->comboBox->setCurrentIndex(2);
    ui->cbEnableLogging->setChecked(true);
    ui->cbShowEDr->setChecked(false);
}

void SettingsTab::setSettings()
{
    ui->configLineEdit->setText(m_setttings->value("/configPath", ui->configLineEdit->text()).toString());
    ui->logLineEdit->setText(m_setttings->value("/logPath", ui->logLineEdit->text()).toString());
    ui->rbAta->setChecked(m_setttings->value("/ioATA", ui->rbAta->isChecked()).toBool());
    ui->rbPosix->setChecked(m_setttings->value("/ioPOSIX", ui->rbPosix->isChecked()).toBool());
    ui->comboBox->setCurrentIndex(m_setttings->value("/logLevel", ui->comboBox->currentIndex()).toInt());
    ui->cbEnableLogging->setChecked(m_setttings->value("/enableLogging", ui->cbEnableLogging->isChecked()).toBool());
    ui->cbShowEDr->setChecked(m_setttings->value("/showEDr", ui->cbShowEDr->isChecked()).toBool());
}

void SettingsTab::setSettings(const QSettings &settings)
{
    ui->configLineEdit->setText(settings.value("/configPath", ui->configLineEdit->text()).toString());
    ui->logLineEdit->setText(settings.value("/logPath", ui->logLineEdit->text()).toString());
    ui->rbAta->setChecked(settings.value("/ioATA", ui->rbAta->isChecked()).toBool());
    ui->rbPosix->setChecked(settings.value("/ioPOSIX", ui->rbPosix->isChecked()).toBool());
    ui->comboBox->setCurrentIndex(settings.value("/logLevel", ui->comboBox->currentIndex()).toInt());
    ui->cbEnableLogging->setChecked(settings.value("/enableLogging", ui->cbEnableLogging->isChecked()).toBool());
    ui->cbShowEDr->setChecked(settings.value("/showEDr", ui->cbShowEDr->isChecked()).toBool());
}

QSettings *SettingsTab::settings()
{
    return m_setttings;
}

SettingsTab::~SettingsTab()
{
    delete ui;
}

void SettingsTab::on_applyButton_clicked()
{
    m_setttings->setValue("/configPath", ui->configLineEdit->text());
    m_setttings->setValue("/logPath", ui->logLineEdit->text());
    m_setttings->setValue("/ioATA", ui->rbAta->isChecked());
    m_setttings->setValue("/ioPOSIX", ui->rbPosix->isChecked());
    m_setttings->setValue("/logLevel", ui->comboBox->currentIndex());
    m_setttings->setValue("/enableLogging", ui->cbEnableLogging->isChecked());
    m_setttings->setValue("/showEDr", ui->cbShowEDr->isChecked());
}

void SettingsTab::on_resetConfigButton_clicked()
{
    ui->configLineEdit->setText(configPath);
}

void SettingsTab::on_resetLogButton_clicked()
{
    ui->logLineEdit->setText(logPath);
}

void SettingsTab::on_cancelButton_clicked()
{
    setSettings();
}

void SettingsTab::on_defaultButton_clicked()
{
    ui->configLineEdit->setText(configPath);
    ui->logLineEdit->setText(logPath);
    ui->rbAta->setChecked(true);
    ui->rbPosix->setChecked(false);
    ui->comboBox->setCurrentIndex(2);
    ui->cbEnableLogging->setChecked(true);
    ui->cbShowEDr->setChecked(false);
}

void SettingsTab::on_selectConfigButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select config file");

    if (fileName != "") {
        delete m_setttings;
        m_setttings = new QSettings(fileName, QSettings::IniFormat, this);
        setSettings();
        ui->configLineEdit->setText(fileName);
    }
}
