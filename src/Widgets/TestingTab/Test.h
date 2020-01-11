#ifndef TESTING_H
#define TESTING_H

#include <QObject>
#include "badsurflib/objects_def.hpp"
#include "badsurflib/badsurflib.hpp"
#include "badsurflib/procedure.hpp"
#include "badsurflib/device.hpp"

class Test : public QObject
{
    Q_OBJECT
private:
    bool _stop;

public:
    Test(QObject *parent = nullptr);
    void process(DC_Dev *dev, uint32_t start, uint32_t end);
    static int statusCallback(DC_ProcedureCtx *ctx, void *callback_priv);
    int callback(DC_ProcedureCtx *ctx);

    int procedure_perform_loop(DC_ProcedureCtx *ctx);

public slots:
    void stop();

signals:
    void read(DC_BlockReport);
    void finished();
};

#endif // TESTING_H
