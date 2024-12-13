#include "idatabase.h"
#include "loginview.h"
#include "ui_loginview.h"
#include <QMessageBox>

loginView::loginView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::loginView)
{
    ui->setupUi(this);
}

loginView::~loginView()
{
    delete ui;
}

void loginView::on_btn_login_clicked()
{
    QString loginInformation = idatabase::getInstance().userLogin(ui->input_name->text(),ui->input_password->text());
    if(loginInformation == "loginS"){
        emit loginSuccessful(ui->input_name->text());
        return;
    }
    if(loginInformation == "PasswordError"){
        QMessageBox::information(this,"错误","密码错误",QMessageBox::Yes|QMessageBox::No);
        return;
    }
    QMessageBox::information(this,"提示","用户不存在!",QMessageBox::Yes|QMessageBox::No);
}

