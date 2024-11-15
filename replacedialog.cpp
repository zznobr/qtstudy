#include "replacedialog.h"
#include "ui_replacedialog.h"

#include <QMessageBox>

replaceDialog::replaceDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::replaceDialog)
{
    ui->setupUi(this);
    connect(ui->btn_cancel,&QPushButton::clicked,[=](){
        this->close();
    });
    connect(ui->line_search,&QLineEdit::textChanged,[=](){
        target = ui->line_search->text();
    });
    connect(ui->btn_replace,&QPushButton::clicked,this,&replaceDialog::on_btn_next_clicked);

    connect(ui->btn_replace_all,&QPushButton::clicked,[=](){
        // qDebug()<<"replace all";
        if(!target.isEmpty())
            emit replace_all(target,ui->line_replace->text());
    });
}

replaceDialog::~replaceDialog()
{
    this->clearDialog();
    delete ui;
}

void replaceDialog::clearDialog()
{
    text.clear();
    target.clear();
    index = 0;
    is_checkBox_case_checked = false;
    ui->line_search->clear();
    ui->checkBox_case->setChecked(false);
    ui->radioButton_down->setChecked(true);
}

void replaceDialog::getText(QString text)
{
    this->text = text;
}

void replaceDialog::on_btn_next_clicked()
{
    bool is_replace = false;
    if(qobject_cast<QPushButton *>(sender())->text() == "替换(R)"){
        qDebug()<<"replace";
        is_replace = true;
        if(is_replace&&index != -1){
            ui->radioButton_down->isChecked() ? (emit return_cursor_position(index-target.length(),target.length(),ui->line_replace->text(),is_replace)) : (emit return_cursor_position(index,target.length(),target,is_replace));
        }
    }
    else{
        Qt::CaseSensitivity cs = ui->checkBox_case->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
        if(target.isEmpty()){
            QMessageBox::information(this,"提示","搜索词为空!");
        }
        else{
            if(!ui->radioButton_up->isChecked()){
                index = text.indexOf(target,index,cs) + target.length();
                if(index-target.length() != -1)
                    emit return_cursor_position(index-target.length(),target.length(),target,is_replace);
                else{
                    QMessageBox::information(this,"查找","查找到底或未查找到");
                    index = 0;
                }
            }
            else{
                index = text.lastIndexOf(target,index-text.length()-target.length(),cs);
                if(index != -1)
                    emit return_cursor_position(index,target.length(),target,is_replace);
                else{
                    QMessageBox::information(this,"查找","查找到底或未查找到");
                    index = text.length();
                }
            }
        }
    }
}

