#ifndef GENERALTAB_H
#define GENERALTAB_H

#include <QWidget>

namespace Ui {
class GeneralTab;
}

class GeneralTab : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralTab(QWidget *parent = nullptr);
    ~GeneralTab();

private:
    Ui::GeneralTab *ui;
};

#endif // GENERALTAB_H
