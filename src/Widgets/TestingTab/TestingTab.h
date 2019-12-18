#ifndef TESTTAB_H
#define TESTTAB_H

#include <QWidget>

namespace Ui {
class TestingTab;
}

class TestingTab : public QWidget
{
    Q_OBJECT

public:
    explicit TestingTab(QWidget *parent = nullptr);
    ~TestingTab();

private:
    Ui::TestingTab *ui;
};

#endif // TESTTAB_H
