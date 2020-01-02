#ifndef SMARTTAB_H
#define SMARTTAB_H

#include <QWidget>

namespace Ui {
class SmartTab;
}

class SmartTab : public QWidget
{
    Q_OBJECT

public:
    explicit SmartTab(QWidget *parent = nullptr);
    ~SmartTab();

private:
    Ui::SmartTab *ui;
};

#endif // SMARTTAB_H
