#ifndef TESTTAB_H
#define TESTTAB_H

#include <QWidget>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QGraphicsScene>
#include "Test.h"
#include "Logger/Logger.h"
#include <badsurflib/objects_def.hpp>
#include <badsurflib/badsurflib.hpp>
#include <badsurflib/device.hpp>

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

    void setCurrentDev(DC_Dev *dev);

private slots:
    void on_startButton_clicked();
    void on_pauseButton_clicked();

public slots:
    void addToResult(DC_BlockReport report);
    void showResult();
    void stopShowResult();
    void addRect(DC_BlockReport report);

signals:
    void on_stop();

private:
    Ui::TestingTab *ui;
    Logger _logger;
    Test _test;
    bool _stopShow;
    DC_Dev *_currentDev;
    std::array<uint32_t, 13> _sectorsCounter;
    int _x;
    int _y;
};

#endif // TESTTAB_H
