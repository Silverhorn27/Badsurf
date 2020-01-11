#include "Test.h"
#include <QThread>
#include <QDebug>

Test::Test(QObject *parent)
    : QObject(parent)
    , _stop(false)
{
    qRegisterMetaType<DC_BlockReport>("DC_BlockReport");
}

int Test::procedure_perform_loop(DC_ProcedureCtx *ctx) {
    int r;
    int ret = 0;
    int perform_ret;
    while (!ctx->interrupt && !_stop) {
        if (_stop)
            ctx->interrupt = 1;
        if (ctx->progress.num >= ctx->progress.den)
            break;
        perform_ret = ctx->procedure->perform(ctx);
        r = 0;
        emit read(ctx->report);
        if (perform_ret) {
            ret = perform_ret;
            break;
        }
        if (r) {
            ret = r;
            break;
        }
    }
    ctx->finished = 1;
    return ret;
}

int Test::callback(DC_ProcedureCtx *ctx) {
    emit read(ctx->report);
    return 0;
}

void Test::process(DC_Dev *dev, uint32_t start, uint32_t end)
{
    _stop = false;

    DC_Procedure *act = dc_find_procedure("read_test");

    DC_OptionSetting *option_set = static_cast<DC_OptionSetting*>(calloc(act->options_num + 1, sizeof(DC_OptionSetting)));

    int i, r;
    for (i = 0; i < act->options_num; i++) {
        option_set[i].name = act->options[i].name;
        r = act->suggest_default_value(dev, &option_set[i]);
        if (r) {
            break;
        }
    }
    /* for read test */
    option_set[0].value = strdup("ata");   // set io method ata or posix
    option_set[1].value = strdup(QString::number(start).toStdString().c_str());     // set start_lba
    option_set[2].value = strdup(QString::number(end).toStdString().c_str());  // set end_lba

    DC_ProcedureCtx *actctx;
    r = dc_procedure_open(act, dev, &actctx, option_set);

    this->procedure_perform_loop(actctx);

    dc_procedure_close(actctx);

    emit finished();
}

void Test::stop()
{
    _stop = true;
    emit finished();
}
