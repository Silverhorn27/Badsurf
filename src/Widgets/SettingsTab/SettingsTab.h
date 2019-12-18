#ifndef SETTINGSTAB_H
#define SETTINGSTAB_H

#include <QWidget>
#include <QSettings>

namespace Ui {
class SettingsTab;
}

class SettingsTab : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsTab(QWidget *parent = nullptr);
    void setDefaultSettings();
    void setSettings();
    void setSettings(const QSettings &settings);
    QSettings *settings();
    ~SettingsTab();

private slots:
    void on_applyButton_clicked();

    void on_resetConfigButton_clicked();

    void on_resetLogButton_clicked();

    void on_cancelButton_clicked();

    void on_defaultButton_clicked();

    void on_selectConfigButton_clicked();

private:
    Ui::SettingsTab *ui;
    QSettings *m_setttings;
};

#endif // SETTINGSTAB_H
