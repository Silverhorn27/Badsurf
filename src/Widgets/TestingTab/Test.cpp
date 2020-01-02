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
    _stop = false;
    for(uint32_t i = start; i <= end; i += 255) {
        if (_stop)
            return;
        int num = qrand() % 6;

        emit read(static_cast<DiskBlockAccess>(num));
        QThread::currentThread()->msleep(10);
    }

    emit finished();
}

void Test::stop()
{
    _stop = true;
    emit finished();
}
