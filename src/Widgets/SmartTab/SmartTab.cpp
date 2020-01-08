#include "SmartTab.h"
#include "ui_SmartTab.h"

SmartTab::SmartTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmartTab)
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
    headerLabels << "ID" << "Name" << "VAL" << "Wrst" << "Tresh" << "Raw" << "Health";
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->tableWidget->setColumnWidth(0, 30);
    ui->tableWidget->setColumnWidth(1, 270);
    ui->tableWidget->setColumnWidth(2, 30);
    ui->tableWidget->setColumnWidth(3, 30);
    ui->tableWidget->setColumnWidth(4, 30);
    ui->tableWidget->setColumnWidth(5, 146);
    ui->tableWidget->setColumnWidth(6, 100);
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0,0, new QTableWidgetItem("sdaf"));


}
SmartTab::~SmartTab()
{
    delete ui;
}
