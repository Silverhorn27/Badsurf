#ifndef TESTING_H
#define TESTING_H

#include <QObject>

enum DiskBlockAccess {
    BLK_TL3 = 0,
    BLK_TL10,
    BLK_TL50,
    BLK_TL150,
    BLK_TL500,
    BLK_TG500,

    BLK_TIME,
    BLK_UNC,
    BLK_ABRT,
    BLK_INDF,
    BLK_AMNF,
    BLK_T0NG,
    BLK_BRK
};

class Test : public QObject
{
    Q_OBJECT
private:
    bool _stop;

public:
    Test(QObject *parent = nullptr);
    void process(uint32_t start, uint32_t end);

public slots:
    void stop();

signals:
    void read(DiskBlockAccess);
    void finished();
};

#endif // TESTING_H
