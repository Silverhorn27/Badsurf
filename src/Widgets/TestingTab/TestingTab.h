#ifndef TESTTAB_H
#define TESTTAB_H

#include <QWidget>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QGraphicsScene>
#include "Test.h"


class Testing;

namespace Ui {
class TestingTab;
}

class TestingTab : public QWidget
{
    Q_OBJECT

public:
    explicit TestingTab(QWidget *parent = nullptr);
    void resetAll();
    void paintStatusBlocks();
    void readSectors();
    ~TestingTab();

private slots:
    void on_startButton_clicked();
    void on_pauseButton_clicked();

public slots:
    void addToResult(DiskBlockAccess status);
    void showResult();
    void stopShowResult();
    void addRect(DiskBlockAccess status);

signals:
    void on_stop();

private:
    Ui::TestingTab *ui;
    QGraphicsScene _scene;
    Test _test;
    bool _stopShow;
    std::array<uint32_t, 13> _sectorsCounter;
    int _x;
    int _y;
};

#endif // TESTTAB_H
