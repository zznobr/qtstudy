#include "addratedialog.h"
#include "ui_addratedialog.h"

AddRateDialog::AddRateDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddRateDialog)
{
    ui->setupUi(this);
}

AddRateDialog::~AddRateDialog()
{
    delete ui;
}

QString AddRateDialog::nameEnglish()
{
    return ui->en->text();
}

QString AddRateDialog::nameChinese()
{
    return ui->cn->text();
}

double AddRateDialog::rate()
{
    return ui->rate->value();
}

void AddRateDialog::clear()
{
    ui->en->clear();
    ui->cn->clear();
    ui->rate->clear();
}
