#include "GeneralTab.h"
#include "ui_GeneralTab.h"

#include <QDebug>

GeneralTab::GeneralTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralTab)
{
    ui->setupUi(this);

}

GeneralTab::~GeneralTab()
{
    delete ui;
}
