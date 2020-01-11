#include "Test.h"
#include <QThread>
#include <QDebug>

Test::Test(QObject *parent)
    : QObject(parent)
    , _stop(false)
{
    qRegisterMetaType<DiskBlockAccess>("DiskBlockAccess");
}

void Test::process(uint32_t start, uint32_t end)
{
    int count = 0;
    _stop = false;
    for(uint32_t i = start; i <= end; i += 256) {
        if (_stop)
            return;
        if (count % 2 == 0) {
            emit read(static_cast<DiskBlockAccess>(0));
            QThread::currentThread()->msleep(10);
        }
        if (count % 8 == 0) {
            emit read(static_cast<DiskBlockAccess>(0));
            QThread::currentThread()->msleep(10);
        }
        if (count % 15 == 0) {
            emit read(static_cast<DiskBlockAccess>(1));
            QThread::currentThread()->msleep(50);
        }
        if (count % 9 == 0) {
            emit read(static_cast<DiskBlockAccess>(1));
            QThread::currentThread()->msleep(50);
        }
        if (count % 87 == 0) {
            emit read(static_cast<DiskBlockAccess>(2));
            QThread::currentThread()->msleep(100);
        }
        if (count % 255 == 0) {
            emit read(static_cast<DiskBlockAccess>(2));
            QThread::currentThread()->msleep(150);
        }
        count++;
        QThread::currentThread()->msleep(1);
    }

    emit finished();
}

void Test::stop()
{
    _stop = true;
    emit finished();
}
