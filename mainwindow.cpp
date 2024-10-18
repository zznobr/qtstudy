#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QEvent>
#include <QDebug>
#include <math.h>

bool MainWindow::checkOpExist()
{
    if(beforeOp=="-"||beforeOp=="+"||beforeOp=="/"||beforeOp=="*")
        return true;
    return false;
}

void MainWindow::showBefore()
{
    beforeQStr = firstStr + beforeOp ;
    ui->lineBefore->setText(beforeQStr);
}

void MainWindow::calculate()
{
    if(nowNum!=0&&beforeOp!="/"){
        if(beforeOp == "+")
            nowNum = nowNum + beforeNum;
        if(beforeOp == "-")
            nowNum = beforeNum - nowNum;
        if(beforeOp == "*")
            nowNum = beforeNum * nowNum;
        if(beforeOp == "/")
            nowNum = beforeNum / nowNum;
        beforeNum = 0;
        firstStr.clear();
        beforeOp.clear();
        showBefore();
        nowQStr = QString::number(nowNum);
        nowQStr = clearZero(nowQStr);
        ui->lineNow->setText(nowQStr);
    }
}

QString MainWindow::clearZero(QString str)
{
    if(!str.contains('.'))
        ;
    else {
        while(str[str.size()-1]=='0')
            str.chop(1);
        if(str[str.size()-1]=='.')
            str.chop(1);
    }
    return str;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isOp = false;
    nowQStr = "0";
    nowNum = 0;
    firstStr = "";
    ui->lineNow->setText(nowQStr);

    //connect连接
    //Number输入1~9
    connect(ui->btn0,&QPushButton::clicked,this,&MainWindow::btnNumClick);
    connect(ui->btn1,&QPushButton::clicked,this,&MainWindow::btnNumClick);
    connect(ui->btn2,&QPushButton::clicked,this,&MainWindow::btnNumClick);
    connect(ui->btn3,&QPushButton::clicked,this,&MainWindow::btnNumClick);
    connect(ui->btn4,&QPushButton::clicked,this,&MainWindow::btnNumClick);
    connect(ui->btn5,&QPushButton::clicked,this,&MainWindow::btnNumClick);
    connect(ui->btn6,&QPushButton::clicked,this,&MainWindow::btnNumClick);
    connect(ui->btn7,&QPushButton::clicked,this,&MainWindow::btnNumClick);
    connect(ui->btn8,&QPushButton::clicked,this,&MainWindow::btnNumClick);
    connect(ui->btn9,&QPushButton::clicked,this,&MainWindow::btnNumClick);
    //单操作符 %,+/-,.,=....
    connect(ui->btnPOI,&QPushButton::clicked,this,&MainWindow::btnPointClick);
    connect(ui->btnBAC,&QPushButton::clicked,this,&MainWindow::btnBackClick);
    connect(ui->btnOPP,&QPushButton::clicked,this,&MainWindow::btnOppositeClick);
    connect(ui->btnREC,&QPushButton::clicked,this,&MainWindow::btnReciprocalClick);
    connect(ui->btnC,&QPushButton::clicked,this,&MainWindow::btnCClick);
    connect(ui->btnCE,&QPushButton::clicked,this,&MainWindow::btnCeClick);
    connect(ui->btnPRE,&QPushButton::clicked,this,&MainWindow::btnPrecentClick);
    connect(ui->btnSQR,&QPushButton::clicked,this,&MainWindow::btnSqrClick);
    connect(ui->btnSQRT,&QPushButton::clicked,this,&MainWindow::btnSqrtClick);
    connect(ui->btnRES,&QPushButton::clicked,this,[=](){
        if(checkOpExist())
            calculate();
    });
    //加减乘除 + - * /
    connect(ui->btnADD,&QPushButton::clicked,this,&MainWindow::btnFourCalculateClick);
    connect(ui->btnSUB,&QPushButton::clicked,this,&MainWindow::btnFourCalculateClick);
    connect(ui->btnMUL,&QPushButton::clicked,this,&MainWindow::btnFourCalculateClick);
    connect(ui->btnDIV,&QPushButton::clicked,this,&MainWindow::btnFourCalculateClick);
    //绑定键盘Qt::Key
    ui->btn0->setShortcut(Qt::Key_0);
    ui->btn1->setShortcut(Qt::Key_1);
    ui->btn2->setShortcut(Qt::Key_2);
    ui->btn3->setShortcut(Qt::Key_3);
    ui->btn4->setShortcut(Qt::Key_4);
    ui->btn5->setShortcut(Qt::Key_5);
    ui->btn6->setShortcut(Qt::Key_6);
    ui->btn7->setShortcut(Qt::Key_7);
    ui->btn8->setShortcut(Qt::Key_8);
    ui->btn9->setShortcut(Qt::Key_9);
    ui->btnPOI->setShortcut(Qt::Key_Period);
    ui->btnRES->setShortcut(Qt::Key_Equal);
    ui->btnRES->setShortcut(Qt::Key_Return);
    ui->btnADD->setShortcut(Qt::Key_Plus);
    ui->btnSUB->setShortcut(Qt::Key_Minus);
    ui->btnMUL->setShortcut(Qt::Key_Asterisk);
    ui->btnDIV->setShortcut(Qt::Key_Slash);
    ui->btnBAC->setShortcut(Qt::Key_Backspace);
    ui->btnC->setShortcut(Qt::Key_C);
    ui->btnPRE->setShortcut(Qt::Key_Percent);
    ui->btnCE->setShortcut(Qt::Key_C);
    ui->btnCE->setShortcut(Qt::Key_C);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnNumClick()
{
    if(nowNum==0&&nowQStr=="0"){
        nowQStr = qobject_cast<QPushButton*>(sender())->text();
        nowNum = nowQStr.toDouble();
        ui->lineNow->setText(nowQStr);
    }
    else{
        if(isOp){
            nowQStr = "";
            ui->lineNow->setText(nowQStr);
            isOp = false;
        }
        // qDebug()<<qobject_cast<QPushButton*>(sender())->text();
        nowQStr = nowQStr + qobject_cast<QPushButton*>(sender())->text();
        nowNum = nowQStr.toDouble();
        ui->lineNow->setText(nowQStr);
    }
    qDebug()<<nowNum;
    // qDebug()<<nowQStr.size();
}

void MainWindow::btnPointClick()
{
    if(!nowQStr.contains('.')){
        nowQStr = nowQStr + qobject_cast<QPushButton*>(sender())->text();
        ui->lineNow->setText(nowQStr);
    }
}

void MainWindow::btnBackClick()
{
    if(nowNum==0&&nowQStr[nowQStr.size()-1]=='.'){
        nowQStr.chop(1);
        ui->lineNow->setText(nowQStr);
    }
    if(nowNum!=0){
        nowQStr.chop(1);
        if(nowQStr==""||nowQStr=="-"){
            nowQStr="0";
            nowNum=0;
            ui->lineNow->setText(nowQStr);
        }
        else{
            if(nowQStr[nowQStr.size()-1]=='.'){
                nowQStr.chop(1);
                nowNum = nowQStr.toDouble();
                nowQStr.append('.');
            }
            else
                nowNum = nowQStr.toDouble();
            ui->lineNow->setText(nowQStr);
        }
    }
}

void MainWindow::btnOppositeClick()
{
    if(nowNum==0);
    else{
        if(nowNum<0){
            nowQStr.remove(QChar('-'));
            nowNum = nowQStr.toDouble();
            qDebug()<<nowQStr.size();
            ui->lineNow->setText(nowQStr);
        }
        else{
            nowQStr.prepend('-');
            nowNum = nowQStr.toDouble();
            qDebug()<<nowQStr.size();
            ui->lineNow->setText(nowQStr);
        }
    }
}

void MainWindow::btnReciprocalClick()
{
    if(nowNum==0){
        nowQStr="0";
        ui->lineNow->setText(nowQStr);
    }
    else{
        nowNum = 1/nowNum;
        nowQStr = QString::number(nowNum,'f',10);
        nowQStr = clearZero(nowQStr);
        ui->lineNow->setText(nowQStr);
    }
}

void MainWindow::btnCeClick()
{
    nowNum = 0;
    nowQStr.clear();
    nowQStr.append('0');
    ui->lineNow->setText(nowQStr);
}

void MainWindow::btnCClick()
{
    nowNum = 0;
    nowQStr.clear();
    nowQStr.append('0');
    ui->lineNow->setText(nowQStr);
    beforeNum = 0;
    beforeOp.clear();
    firstStr.clear();
    beforeQStr.clear();
    showBefore();
}

void MainWindow::btnPrecentClick()
{
    nowNum = nowNum*0.01;
    nowQStr = QString::number(nowNum,'f',10);
    nowQStr = clearZero(nowQStr);
    ui->lineNow->setText(nowQStr);
}

void MainWindow::btnSqrClick()
{
    nowNum = nowNum * nowNum;
    nowQStr = QString::number(nowNum,'f',10);
    nowQStr = clearZero(nowQStr);
    ui->lineNow->setText(nowQStr);
}

void MainWindow::btnSqrtClick()
{
    nowNum = sqrt(nowNum);
    nowQStr = QString::number(nowNum,'f',10);
    nowQStr = clearZero(nowQStr);
    ui->lineNow->setText(nowQStr);
}

void MainWindow::btnFourCalculateClick()
{
    if(checkOpExist())
        calculate();
    beforeNum = nowNum;
    firstStr = nowQStr;
    beforeOp = qobject_cast<QPushButton*>(sender())->text();
    nowNum = 0;
    nowQStr = QString::number(nowNum);
    ui->lineNow->setText(nowQStr);
    showBefore();
}

