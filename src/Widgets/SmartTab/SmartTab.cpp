#include "SmartTab.h"
#include "ui_SmartTab.h"

#include <QDebug>

SmartTab::SmartTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SmartTab)
    , _logger("SmartTab")
{
    ui->setupUi(this);
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->insertColumn(0);
    ui->tableWidget->insertColumn(1);
    ui->tableWidget->insertColumn(2);
    ui->tableWidget->insertColumn(3);
    ui->tableWidget->insertColumn(4);
    ui->tableWidget->insertColumn(5);
    ui->tableWidget->insertColumn(6);
    QStringList headerLabels;
    headerLabels << "ID" << "Attribute name" << "Value" << "Worst" << "Tresh" << "Fail" << "Raw";
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->tableWidget->setColumnWidth(0, 50);
    ui->tableWidget->setColumnWidth(1, 270);
    ui->tableWidget->setColumnWidth(2, 70);
    ui->tableWidget->setColumnWidth(3, 70);
    ui->tableWidget->setColumnWidth(4, 70);
    ui->tableWidget->setColumnWidth(5, 70);
    ui->tableWidget->setColumnWidth(6, 142);
    ui->tableWidget->insertRow(0);

}
SmartTab::~SmartTab()
{
    delete ui;
}

void SmartTab::setCurrentDev(DC_Dev *dev)
{
    _currentDev = dev;
}

void SmartTab::on_pushButton_clicked()
{
    ui->tableWidget->setRowCount(0);

    DC_Procedure *act = dc_find_procedure("smart_show");
    DC_OptionSetting *option_set = static_cast<DC_OptionSetting*>(calloc(act->options_num + 1,
                                                                         sizeof(DC_OptionSetting)));

    DC_ProcedureCtx *actctx;
    int r = dc_procedure_open(act, _currentDev, &actctx, option_set);
    if (r) {
        _logger.log(Logger::ERROR, "Getting SMART attributes faile");
        return;
    }

    int i = 0;
    for (auto &a : actctx->smart_attrs.attrs_vec) {
        ui->tableWidget->insertRow(i);
        QTableWidgetItem *id = new QTableWidgetItem(QString::number(a.id));
        id->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
        ui->tableWidget->setItem(i, 0, id);
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromLatin1(a.attr_name)));
        QTableWidgetItem *value = new QTableWidgetItem(QString::number(a.value));
        value->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 2, value);
        QTableWidgetItem *worst = new QTableWidgetItem(QString::number(a.worst));
        worst->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 3, worst);
        QTableWidgetItem *threshold = new QTableWidgetItem(QString::number(a.threshold));
        threshold->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 4, threshold);
        QTableWidgetItem *fail = new QTableWidgetItem(QString::number(a.fail));
        fail->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 5, fail);
        QTableWidgetItem *raw = new QTableWidgetItem(QString::number(a.raw));
        raw->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 6, raw);
        i++;
    }

    dc_procedure_close(actctx);
}
