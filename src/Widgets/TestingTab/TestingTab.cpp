#include "TestingTab.h"
#include "ui_TestingTab.h"

TestingTab::TestingTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestingTab)
{
    ui->setupUi(this);
}

TestingTab::~TestingTab()
{
    delete ui;
}
