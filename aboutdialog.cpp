#include "aboutdialog.h"
#include "ui_aboutdialog.h"

aboutDialog::aboutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::aboutDialog)
{
    ui->setupUi(this);

    //固定窗口大小
    this->setFixedSize(400,300);
    //Ok按钮退出
    connect(ui->pushButton,&QPushButton::clicked,[&](){
        this->close();
    });
}

aboutDialog::~aboutDialog()
{
    delete ui;
}
