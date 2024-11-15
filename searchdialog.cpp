#include "searchdialog.h"
#include "ui_searchdialog.h"

#include <QCloseEvent>
#include <QMessageBox>

searchDialog::searchDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::searchDialog)
{
    ui->setupUi(this);
    connect(ui->btn_cancel,&QPushButton::clicked,[=](){
        this->close();
    });
    connect(ui->lineEdit_search,&QLineEdit::textChanged,[=](){
        target = ui->lineEdit_search->text();
    });
}

searchDialog::~searchDialog()
{
    this->clearDialog();
    delete ui;
}

void searchDialog::clearDialog()
{
    text.clear();
    target.clear();
    index = 0;
    is_checkBox_case_checked = false;
    ui->lineEdit_search->clear();
    ui->checkBox_case->setChecked(false);
    ui->radioButton_down->setChecked(true);
}

void searchDialog::getText(QString text)
{
    this->text = text;
}

void searchDialog::closeEvent(QCloseEvent *event)
{
    this->clearDialog();
    event->accept();
}

void searchDialog::on_btn_next_clicked()
{
    Qt::CaseSensitivity cs = ui->checkBox_case->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    if(target.isEmpty()){
        QMessageBox::information(this,"提示","搜索词为空!");
    }
    else{
        if(!ui->radioButton_up->isChecked()){
            index = text.indexOf(target,index,cs) + target.length();
            if(index-target.length() != -1)
                emit return_cursor_position(index-target.length(),target.length(),target,false);
            else{
                QMessageBox::information(this,"查找","查找到底或未查找到");
                index = 0;
            }
        }
        else{
            index = text.lastIndexOf(target,index-text.length()-target.length(),cs);
            if(index != -1)
                emit return_cursor_position(index,target.length(),target,false);
            else{
                QMessageBox::information(this,"查找","查找到底或未查找到");
                index = text.length();
            }
        }
        }
}

