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
    headerLabels << "ID" << "Attribut name" << "VAL" << "Wrst" << "Tresh" << "Fail" << "Raw";
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->tableWidget->setColumnWidth(0, 60);
    ui->tableWidget->setColumnWidth(1, 270);
    ui->tableWidget->setColumnWidth(2, 60);
    ui->tableWidget->setColumnWidth(3, 60);
    ui->tableWidget->setColumnWidth(4, 60);
    ui->tableWidget->setColumnWidth(5, 130);
    ui->tableWidget->setColumnWidth(6, 100);
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
//        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(a.id)));
//        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromLatin1(a.attr_name)));
//        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(a.value)));
//        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(a.worst)));
//        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(a.threshold)));
//        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString(a.fail)));
//        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(a.raw)));
        i++;
    }

    dc_procedure_close(actctx);
}
