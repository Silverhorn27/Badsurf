#ifndef SMARTTAB_H
#define SMARTTAB_H

#include <QWidget>
#include "Logger/Logger.h"
#include <badsurflib/objects_def.hpp>
#include <badsurflib/badsurflib.hpp>
#include <badsurflib/device.hpp>
#include <badsurflib/procedure.hpp>



namespace Ui {
class SmartTab;
}

class SmartTab : public QWidget
{
    Q_OBJECT

public:
    explicit SmartTab(QWidget *parent = nullptr);
    ~SmartTab();

    void setCurrentDev(DC_Dev *dev);

private slots:
    void on_pushButton_clicked();

private:
    Ui::SmartTab *ui;
    Logger _logger;
    DC_Dev *_currentDev;
};

#endif // SMARTTAB_H
