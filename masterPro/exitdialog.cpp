#include "exitdialog.h"
#include "ui_exitdialog.h"

exitDialog::exitDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::exitDialog)
{
    ui->setupUi(this);
}

exitDialog::~exitDialog()
{
    delete ui;
}
