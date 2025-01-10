#include "baseinputwidget.h"
#include "ui_baseinputwidget.h"

BaseInputWidget::BaseInputWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BaseInputWidget)
{
    ui->setupUi(this);

    // nowNum = 0;
    nowStr = "0";

    this->decModel();

    //connect连接
    //Number输入1~9
    connect(ui->btn0,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    connect(ui->btn1,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    connect(ui->btn2,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    connect(ui->btn3,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    connect(ui->btn4,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    connect(ui->btn5,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    connect(ui->btn6,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    connect(ui->btn7,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    connect(ui->btn8,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    connect(ui->btn9,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    connect(ui->btnA,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    connect(ui->btnB,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    connect(ui->btnC,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    connect(ui->btnD,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    connect(ui->btnE,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    connect(ui->btnF,&QPushButton::clicked,this,&BaseInputWidget::btnNumClick);
    //单操作符 %,+/-,.,=....
    connect(ui->btnPOI,&QPushButton::clicked,this,&BaseInputWidget::btnPointClick);
    connect(ui->btnDEL,&QPushButton::clicked,this,&BaseInputWidget::btnBackClick);
    connect(ui->btnClear,&QPushButton::clicked,this,&BaseInputWidget::btnCClick);
}

BaseInputWidget::~BaseInputWidget()
{
    delete ui;
}

void BaseInputWidget::baseChanged(int base,QString nowStr)
{
    this->nowbase = base;
    if(nowStr != "updateBase")
        this->nowStr = nowStr;
    switch(this->nowbase){
        case 2:
            this->binModel();
            break;
        case 4:
            this->quaModel();
            break;
        case 8:
            this->octModel();
            break;
        case 10:
            this->decModel();
            break;
        case 16:
            this->hexModel();
            break;
        default:
            break;
    }

    qDebug()<<"base is "<<this->nowbase<<" now";
}



void BaseInputWidget::on_btnADD_clicked()
{
    ;
}

void BaseInputWidget::btnNumClick()
{
    if(nowStr=="0"){
        nowStr = qobject_cast<QPushButton*>(sender())->text();
        // nowNum = nowStr.toDouble();
        emit nowStr_changed(nowStr);
    }
    else{
        nowStr = nowStr + qobject_cast<QPushButton*>(sender())->text();
        // nowNum = nowStr.toDouble();
        // ui->lineNow->setText(nowQStr);
        emit nowStr_changed(nowStr);
    }
    qDebug()<<nowStr;
}

void BaseInputWidget::btnPointClick()
{
    if(!nowStr.contains('.')){
        nowStr = nowStr + qobject_cast<QPushButton*>(sender())->text();
        emit nowStr_changed(nowStr);
    }
}

void BaseInputWidget::btnBackClick()
{
    if(nowStr == "0."){
        nowStr = "0";
        // ui->lineNow->setText(nowQStr);
        emit nowStr_changed(nowStr);
    }
    if(nowStr != "0"){
        nowStr.chop(1);
        if(nowStr==""){
            nowStr="0";
            // nowNum=0;
            emit nowStr_changed(nowStr);
        }
        else{
            if(nowStr[nowStr.size()-1]=='.'){
                nowStr.chop(1);
                // nowNum = nowStr.toDouble();
                nowStr.append('.');
            }
            // else
            //     nowNum = nowStr.toDouble();
            emit nowStr_changed(nowStr);
        }
    }
}

void BaseInputWidget::btnCClick()
{
    // nowNum = 0;
    nowStr.clear();
    nowStr.append('0');
    emit nowStr_changed(nowStr);
}

void BaseInputWidget::binModel()
{
    ui->btn2->setEnabled(false);
    ui->btn3->setEnabled(false);
    ui->btn4->setEnabled(false);
    ui->btn5->setEnabled(false);
    ui->btn6->setEnabled(false);
    ui->btn7->setEnabled(false);
    ui->btn8->setEnabled(false);
    ui->btn9->setEnabled(false);
    ui->btnA->setEnabled(false);
    ui->btnB->setEnabled(false);
    ui->btnC->setEnabled(false);
    ui->btnD->setEnabled(false);
    ui->btnE->setEnabled(false);
    ui->btnF->setEnabled(false);
}

void BaseInputWidget::quaModel()
{
    this->binModel();
    ui->btn2->setEnabled(true);
    ui->btn3->setEnabled(true);
}

void BaseInputWidget::octModel()
{
    this->quaModel();
    ui->btn4->setEnabled(true);
    ui->btn5->setEnabled(true);
    ui->btn6->setEnabled(true);
    ui->btn7->setEnabled(true);
}

void BaseInputWidget::decModel()
{
    this->octModel();
    ui->btn8->setEnabled(true);
    ui->btn9->setEnabled(true);
}

void BaseInputWidget::hexModel()
{
    this->decModel();
    ui->btnA->setEnabled(true);
    ui->btnB->setEnabled(true);
    ui->btnC->setEnabled(true);
    ui->btnD->setEnabled(true);
    ui->btnE->setEnabled(true);
    ui->btnF->setEnabled(true);
}

