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
    void setSettings();
    QSettings *settings();
    ~SettingsTab();

private slots:
    void on_applyButton_clicked();

    void on_resetConfigButton_clicked();

    void on_resetLogButton_clicked();

    void on_cancelButton_clicked();

    void on_defaultButton_clicked();

    void on_selectConfigButton_clicked();

signals:
    void enabledLogInFile(bool);
    void enabledShowEDr(bool);
    void logPathChanged(const std::string &);
    void levelChanged(int);

private:
    Ui::SettingsTab *ui;
    QSettings *m_setttings;
};

#endif // SETTINGSTAB_H
