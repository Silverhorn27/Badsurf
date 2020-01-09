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
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, 20, 40);
    ui->whiteLabel->setPixmap(pix);
    painter.setBrush(Qt::gray);
    painter.drawRect(0, 0, 20, 40);
    ui->greyLabel->setPixmap(pix);
    painter.setBrush(Qt::white);
    painter.drawRect(0, 0, 20, 40);
    ui->blackLabel->setPixmap(pix);
    painter.setBrush(Qt::green);
    painter.drawRect(0, 0, 20, 40);
    ui->greenLabel->setPixmap(pix);
    painter.setBrush(Qt::yellow);
    painter.drawRect(0, 0, 20, 40);
    ui->orangeLabel->setPixmap(pix);
    painter.setBrush(Qt::red);
    painter.drawRect(0, 0, 20, 40);
    ui->redLabel->setPixmap(pix);

}

void TestingTab::readSectors()
{
    _stopShow = false;
    QFuture<void> ftest = QtConcurrent::run(&this->_test, &Test::process,
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
}

void TestingTab::on_startButton_clicked()
{
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

void TestingTab::addToResult(DiskBlockAccess status)
{
    ulong num = ui->startLine->text().toULong() + 255;
    ui->startLine->setText(QString::number(num));
    _sectorsCounter.at(status)++;
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

void TestingTab::addRect(DiskBlockAccess status)
{
    if (status % 2 == 0) {
        ui->graphicsView->scene()->addRect(_x, _y, 20, 30, QPen(Qt::black), QBrush(Qt::black));
    } else
        ui->graphicsView->scene()->addRect(_x, _y, 20, 30, QPen(Qt::black), QBrush(Qt::gray));
    _x += 20;
    if (_y > 360)
        ui->graphicsView->verticalScrollBar()->setValue(_y);
    if (_x > 400) {
        _x = 0;
        _y += 30;
    }

}
