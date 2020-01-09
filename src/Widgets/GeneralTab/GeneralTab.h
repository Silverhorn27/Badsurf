#ifndef GENERALTAB_H
#define GENERALTAB_H

#include <QWidget>
#include "Logger/Logger.h"
#include <badsurflib/objects_def.hpp>
#include <badsurflib/badsurflib.hpp>
#include <badsurflib/device.hpp>

namespace Ui {
class GeneralTab;
}

class GeneralTab : public QWidget
{
    Q_OBJECT
public:
    explicit GeneralTab(QWidget *parent = nullptr);
    ~GeneralTab();

    void init();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GeneralTab *ui;
    Logger _logger;
    DC_DevList *_devlist;
    DC_Dev *_currentDev;
};

#endif // GENERALTAB_H
