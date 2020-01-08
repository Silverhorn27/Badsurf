#include "GeneralTab.h"
#include "ui_GeneralTab.h"

#include <badsurflib/objects_def.hpp>
#include <badsurflib/badsurflib.hpp>
#include <badsurflib/device.hpp>

#include <QDebug>

GeneralTab::GeneralTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GeneralTab)
    , _logger("GeneralTab")
{
    ui->setupUi(this);
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->insertColumn(0);
    ui->tableWidget->insertColumn(1);
    ui->tableWidget->insertColumn(2);
    QStringList headerLabels;
    headerLabels << " " << "Disk information" << " ";
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->tableWidget->setColumnWidth(0, 124);
    ui->tableWidget->setColumnWidth(1, 440);
    ui->tableWidget->setColumnWidth(2, 200);

    int r = dc_init();
    assert(!r);

    if (r) {
        _logger.log(Logger::FATAL, "Init fail");
        return;
    }

    DC_DevList *devlist = dc_dev_list();
    assert(devlist);

    DC_Dev *current = devlist->arr;
    for(int i = 0; i < devlist->arr_size; ++i) {
        ui->comboBox->insertItem(i, StringUtils::toQString(std::string(current->model_str)));
        current = current->next;
    }
}

GeneralTab::~GeneralTab()
{
    delete ui;
}
