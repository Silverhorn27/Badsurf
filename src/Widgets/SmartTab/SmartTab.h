#ifndef SMARTTAB_H
#define SMARTTAB_H

#include <QWidget>
#include <badsurflib/objects_def.hpp>
#include <badsurflib/badsurflib.hpp>
#include <badsurflib/device.hpp>

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

private:
    Ui::SmartTab *ui;
    DC_Dev *_currentDev;
};

#endif // SMARTTAB_H
