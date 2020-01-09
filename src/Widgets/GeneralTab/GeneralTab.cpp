#include "GeneralTab.h"
#include "ui_GeneralTab.h"

#include <QDebug>

static const std::array<QString, 7> DEVICE_INFO {
    "Device path:",
    "Model:",
    "Serial number:",
    "Capacity:",
    "Capacity LBA (Max LBA):",
    "Security status:",
    "HPA enabled:"
};

GeneralTab::GeneralTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GeneralTab)
    , _logger("GeneralTab")
    , _devlist(dc_dev_list())
    , _currentDev(_devlist->arr)
{
    ui->setupUi(this);
    LOG_TRACE(_logger)
    init();
    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableWidget->verticalHeader()->hide();

    ui->tableWidget->insertColumn(0);
    ui->tableWidget->insertColumn(1);

    QStringList headerLabels;
    headerLabels << " " << "Disk information";

    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->tableWidget->setColumnWidth(0, 224);
    ui->tableWidget->setColumnWidth(1, 540);

}

GeneralTab::~GeneralTab()
{
    delete ui;
}

void GeneralTab::init()
{
    int r = dc_init();
    assert(!r);

    if (r) {
        _logger.log(Logger::FATAL, "Init fail");
        return;
    }

    assert(_devlist);

    DC_Dev *current = _devlist->arr;
    for(int i = 0; i < _devlist->arr_size; ++i) {
        ui->comboBox->insertItem(i, QString::fromLatin1(current->model_str));
        current = current->next;
    }
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::activated),
            [=](int index){
        DC_Dev *cur = _devlist->arr;
        for(int i = 0; i <= index; ++i) {
            _currentDev = cur;
            cur = cur->next;
        }
    });
}

void GeneralTab::on_pushButton_clicked()
{
    ui->tableWidget->setRowCount(0);
    for(int i = 0; i < 6; ++i) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0,
                                 new QTableWidgetItem(DEVICE_INFO.at(static_cast<size_t>(i))));
    }
    ui->tableWidget->setItem(0, 1,
                             new QTableWidgetItem(QString::fromLatin1(_currentDev->node_path)));
    ui->tableWidget->setItem(1, 1,
                             new QTableWidgetItem(QString::fromLatin1(_currentDev->model_str)));
    ui->tableWidget->setItem(2, 1,
                             new QTableWidgetItem(QString::fromLatin1(_currentDev->serial_no)));
    ui->tableWidget->setItem(3, 1,
                             new QTableWidgetItem(QString::number(_currentDev->capacity)));
    ui->tableWidget->setItem(4, 1,
                             new QTableWidgetItem(QString::number(_currentDev->native_capacity)));
    ui->tableWidget->setItem(5, 1,
                             new QTableWidgetItem(QString::number(_currentDev->security_on)));
    ui->tableWidget->setItem(6, 1,
                             new QTableWidgetItem(QString::number(_currentDev->hpa_enabled)));

}
