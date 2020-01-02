#include "SmartTab.h"
#include "ui_SmartTab.h"
#include "TableModel.h"

SmartTab::SmartTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmartTab)
{
    TableModel *table = new TableModel(10, 7, this);
    ui->setupUi(this);
    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->tableView->setModel(table);
    ui->tableView->setColumnWidth(0, 30);
    ui->tableView->setColumnWidth(1, 260);
    ui->tableView->setColumnWidth(2, 30);
    ui->tableView->setColumnWidth(3, 30);
    ui->tableView->setColumnWidth(4, 30);
    ui->tableView->setColumnWidth(5, 144);
    ui->tableView->setColumnWidth(6, 100);
    table->appendData(QVariantList() << 2341 << 3453 << 3254 << 432);
}
SmartTab::~SmartTab()
{
    delete ui;
}
