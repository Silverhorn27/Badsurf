#include "TestingTab.h"
#include "ui_TestingTab.h"
#include "Utils/StringUtils.h"
#include "Test.h"
#include <QDebug>
#include <QPainter>
#include <QScrollBar>

TestingTab::TestingTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestingTab)
    , _logger("TestingTab")
    , _test(nullptr)
    , _stopShow(false)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(ui->graphicsView));
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->pauseButton->setEnabled(false);
    resetAll();
    paintStatusBlocks();
    connect(&_test, &Test::read, this, &TestingTab::addToResult);
    connect(&_test, &Test::read, this, &TestingTab::addRect);
    connect(this, &TestingTab::on_stop, &_test, &Test::stop);
    connect(this, &TestingTab::on_stop, this, &TestingTab::stopShowResult);
}

void TestingTab::resetAll()
{
    for(auto &i : _sectorsCounter)
        i = 0;
    ui->t3label->setText("0");
    ui->t10label->setText("0");
    ui->t50label->setText("0");
    ui->t150label->setText("0");
    ui->t500label->setText("0");
    ui->t500olabel->setText("0");
    ui->startLine->setText("0");
    delete ui->graphicsView->scene();
    ui->graphicsView->setScene(new QGraphicsScene(ui->graphicsView));
    _x = 0;
    _y = 0;
}

void TestingTab::paintStatusBlocks()
{
    QPixmap pix(QSize(20,30));
    QPainter painter(&pix);
    painter.setBrush(QBrush(QColor("#C9C9CA")));
    painter.drawRect(0, 0, 20, 40);
    ui->whiteLabel->setPixmap(pix);
    painter.setBrush(QBrush(QColor("#AAAAAB")));
    painter.drawRect(0, 0, 20, 40);
    ui->greyLabel->setPixmap(pix);
    painter.setBrush(QBrush(QColor("#808080")));
    painter.drawRect(0, 0, 20, 40);
    ui->blackLabel->setPixmap(pix);
    painter.setBrush(QBrush(QColor("#05EF00")));
    painter.drawRect(0, 0, 20, 40);
    ui->greenLabel->setPixmap(pix);
    painter.setBrush(QBrush(QColor("#FF8000")));
    painter.drawRect(0, 0, 20, 40);
    ui->orangeLabel->setPixmap(pix);
    painter.setBrush(QBrush(QColor("#F60909")));
    painter.drawRect(0, 0, 20, 40);
    ui->redLabel->setPixmap(pix);

}

void TestingTab::readSectors()
{
    _stopShow = false;
    _logger.log(Logger::INFO, "Start testing");
    QFuture<void> ftest = QtConcurrent::run(&this->_test, &Test::process,
                                            _currentDev,
                                            ui->startLine->text().toULong(),
                                            ui->endLine->text().toULong());
    QFuture<void> fshow = QtConcurrent::run(this, &TestingTab::showResult);
}


TestingTab::~TestingTab()
{
    emit on_stop();
    delete ui;
}

void TestingTab::setCurrentDev(DC_Dev *dev)
{
    _currentDev = dev;
    ui->endLine->setText(QString::number(dev->capacity >> 5));
}

void TestingTab::on_startButton_clicked()
{
    if (ui->endLine->text() == "0")
        return;
    if (ui->startButton->text() == "Start") {
        ui->startButton->setText("Stop");
        ui->pauseButton->setEnabled(true);
        readSectors();
    } else {
        emit on_stop();
        ui->startButton->setText("Start");
        ui->pauseButton->setText("Pause");
        ui->pauseButton->setEnabled(false);
        resetAll();
    }
}

void TestingTab::on_pauseButton_clicked()
{
    if (ui->pauseButton->text() == "Pause") {
        ui->pauseButton->setText("Continue");
        emit on_stop();
    } else {
        ui->pauseButton->setText("Pause");
        readSectors();
    }
}

void TestingTab::addToResult(DC_BlockReport report)
{
    ulong num = ui->startLine->text().toULong() + 256;
    ui->startLine->setText(QString::number(num));
    if (report.blk_status == 0) {
        if (report.blk_access_time < 10 * 1000)
            _sectorsCounter.at(0)++;
        else if (report.blk_access_time < 50 * 1000)
            _sectorsCounter.at(1)++;
        else if (report.blk_access_time < 150 * 1000)
            _sectorsCounter.at(2)++;
        else if (report.blk_access_time < 500 * 1000)
            _sectorsCounter.at(3)++;
        else if (report.blk_access_time > 500 * 1000)
            _sectorsCounter.at(4)++;
    } else {
        _sectorsCounter.at(4 + report.blk_status)++;
    }
}

void TestingTab::showResult()
{
    while(!_stopShow) {
        ui->t3label->setText(QString::number(_sectorsCounter.at(0)));
        ui->t10label->setText(QString::number(_sectorsCounter.at(1)));
        ui->t50label->setText(QString::number(_sectorsCounter.at(2)));
        ui->t150label->setText(QString::number(_sectorsCounter.at(3)));
        ui->t500label->setText(QString::number(_sectorsCounter.at(4)));
        ui->t500olabel->setText(QString::number(_sectorsCounter.at(5)));
        QThread::msleep(100);
    }
}

void TestingTab::stopShowResult()
{
    _stopShow = true;
}

void TestingTab::addRect(DC_BlockReport report)
{
    if (report.blk_status == 0) {
        if (report.blk_access_time < 10 * 1000)
            ui->graphicsView->scene()->addRect(_x, _y, 20, 30, QPen(Qt::black), QBrush(QColor("#C9C9CA")));
        else if (report.blk_access_time < 50 * 1000)
            ui->graphicsView->scene()->addRect(_x, _y, 20, 30, QPen(Qt::black), QBrush(QColor("#AAAAAB")));
        else if (report.blk_access_time < 150 * 1000)
            ui->graphicsView->scene()->addRect(_x, _y, 20, 30, QPen(Qt::black), QBrush(QColor("#808080")));
        else if (report.blk_access_time < 500 * 1000)
            ui->graphicsView->scene()->addRect(_x, _y, 20, 30, QPen(Qt::black), QBrush(QColor("#05EF00")));
        else if (report.blk_access_time > 500 * 1000)
            ui->graphicsView->scene()->addRect(_x, _y, 20, 30, QPen(Qt::black), QBrush(QColor("#FF8000")));
    } else {
        ui->graphicsView->scene()->addRect(_x, _y, 20, 30, QPen(Qt::black), QBrush(QColor(Qt::blue)));
    }

    _x += 20;
    if (_y > 360)
        ui->graphicsView->verticalScrollBar()->setValue(_y);
    if (_x > 400) {
        _x = 0;
        _y += 30;
    }

}
