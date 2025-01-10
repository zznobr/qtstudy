#include "inputwidget.h"
#include "ui_inputwidget.h"
#include <QDateTime>
#include <QMessageBox>


inputWidget::inputWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::inputWidget)
{
    ui->setupUi(this);

    isOp = false;
    nowQStr = "0";
    nowNum = 0;
    firstStr = "";
    nowQStr_changed(nowQStr);

    //connect连接
    //Number输入1~9
    connect(ui->btn0,&QPushButton::clicked,this,&inputWidget::btnNumClick);
    connect(ui->btn1,&QPushButton::clicked,this,&inputWidget::btnNumClick);
    connect(ui->btn2,&QPushButton::clicked,this,&inputWidget::btnNumClick);
    connect(ui->btn3,&QPushButton::clicked,this,&inputWidget::btnNumClick);
    connect(ui->btn4,&QPushButton::clicked,this,&inputWidget::btnNumClick);
    connect(ui->btn5,&QPushButton::clicked,this,&inputWidget::btnNumClick);
    connect(ui->btn6,&QPushButton::clicked,this,&inputWidget::btnNumClick);
    connect(ui->btn7,&QPushButton::clicked,this,&inputWidget::btnNumClick);
    connect(ui->btn8,&QPushButton::clicked,this,&inputWidget::btnNumClick);
    connect(ui->btn9,&QPushButton::clicked,this,&inputWidget::btnNumClick);
    //单操作符 %,+/-,.,=....
    connect(ui->btnPOI,&QPushButton::clicked,this,&inputWidget::btnPointClick);
    connect(ui->btnDEL,&QPushButton::clicked,this,&inputWidget::btnBackClick);
    connect(ui->btnOPP,&QPushButton::clicked,this,&inputWidget::btnOppositeClick);
    connect(ui->btnREC,&QPushButton::clicked,this,&inputWidget::btnReciprocalClick);
    connect(ui->btnC,&QPushButton::clicked,this,&inputWidget::btnCClick);
    connect(ui->btnCE,&QPushButton::clicked,this,&inputWidget::btnCeClick);
    connect(ui->btnPER,&QPushButton::clicked,this,&inputWidget::btnPercentClick);
    connect(ui->btnSQR,&QPushButton::clicked,this,&inputWidget::btnSqrClick);
    connect(ui->btnSQRT,&QPushButton::clicked,this,&inputWidget::btnSqrtClick);
    connect(ui->btnRES,&QPushButton::clicked,this,[=](){
        if(checkOpExist())
            calculate();
    });
    //加减乘除 + - * /
    connect(ui->btnADD,&QPushButton::clicked,this,&inputWidget::btnFourCalculateClick);
    connect(ui->btnSUB,&QPushButton::clicked,this,&inputWidget::btnFourCalculateClick);
    connect(ui->btnMUL,&QPushButton::clicked,this,&inputWidget::btnFourCalculateClick);
    connect(ui->btnDIV,&QPushButton::clicked,this,&inputWidget::btnFourCalculateClick);
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
    ui->btnDEL->setShortcut(Qt::Key_Backspace);
    ui->btnC->setShortcut(Qt::Key_C);
    ui->btnPER->setShortcut(Qt::Key_Percent);
}

inputWidget::~inputWidget()
{
    delete ui;
}

void inputWidget::language(QString str)
{
    if(str == "cn"){
        ui->btnOPP->setText("相反数");
        ui->btnPER->setText("百分比");
        ui->btnSQR->setText("平方");
        ui->btnSQRT->setText("开方");
        ui->btnCE->setText("清空");
        ui->btnC->setText("清空一行");
        ui->btnDEL->setText("退格");
        ui->btnREC->setText("倒数");
    }
    if(str == "en"){
        ui->btnOPP->setText("OPP");
        ui->btnPER->setText("%");
        ui->btnSQR->setText("sqr");
        ui->btnSQRT->setText("sqrt");
        ui->btnCE->setText("C");
        ui->btnC->setText("CE");
        ui->btnDEL->setText("Del");
        ui->btnREC->setText("1/X");
    }
}


bool inputWidget::checkOpExist()
{
    if(beforeOp=="-"||beforeOp=="+"||beforeOp=="/"||beforeOp=="*")
        return true;
    return false;
}

void inputWidget::showBefore()
{
    beforeQStr = firstStr + beforeOp ;
    // ui->lineBefore->setText(beforeQStr);
    emit beforeQStr_changed(beforeQStr);
}

void inputWidget::calculate()
{
    if(nowNum==0&&beforeOp=="/"){
        QMessageBox::warning(this,"警告","0不能作为除数");
    }
    else{
        QString record = "";
        QDateTime currentDateTime = QDateTime::currentDateTime();
        record.append(currentDateTime.toString("yyyy-MM-dd hh:mm:ss")+": "+firstStr+" "+beforeOp+" "+nowQStr+" = ");
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
        record.append(nowQStr);
        emit calculateRecord(record);
        // ui->lineNow->setText(nowQStr);
        emit nowQStr_changed(nowQStr);
    }
}

QString inputWidget::clearZero(QString str)
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

void inputWidget::btnNumClick()
{
    if(nowNum==0&&nowQStr=="0"){
        nowQStr = qobject_cast<QPushButton*>(sender())->text();
        nowNum = nowQStr.toDouble();
        // ui->lineNow->setText(nowQStr);
        emit nowQStr_changed(nowQStr);
    }
    else{
        if(isOp){
            nowQStr = "";
            // ui->lineNow->setText(nowQStr);
            emit nowQStr_changed(nowQStr);
            isOp = false;
        }
        // qDebug()<<qobject_cast<QPushButton*>(sender())->text();
        nowQStr = nowQStr + qobject_cast<QPushButton*>(sender())->text();
        nowNum = nowQStr.toDouble();
        // ui->lineNow->setText(nowQStr);
        emit nowQStr_changed(nowQStr);
    }
    qDebug()<<nowNum;
    // qDebug()<<nowQStr.size();
}

void inputWidget::btnPointClick()
{
    if(!nowQStr.contains('.')){
        nowQStr = nowQStr + qobject_cast<QPushButton*>(sender())->text();
        // ui->lineNow->setText(nowQStr);
        emit nowQStr_changed(nowQStr);
    }
}

void inputWidget::btnBackClick()
{
    if(nowNum==0&&nowQStr.contains(".")){
        nowQStr = "0";
        // ui->lineNow->setText(nowQStr);
        emit nowQStr_changed(nowQStr);
    }
    if(nowNum!=0){
        nowQStr.chop(1);
        if(nowQStr==""||nowQStr=="-"){
            nowQStr="0";
            nowNum=0;
            // ui->lineNow->setText(nowQStr);
            emit nowQStr_changed(nowQStr);
        }
        else{
            if(nowQStr[nowQStr.size()-1]=='.'){
                nowQStr.chop(1);
                nowNum = nowQStr.toDouble();
                nowQStr.append('.');
            }
            else
                nowNum = nowQStr.toDouble();
            // ui->lineNow->setText(nowQStr);
            emit nowQStr_changed(nowQStr);
        }
    }
}

void inputWidget::btnOppositeClick()
{
    if(nowNum==0);
    else{
        QString record = "";
        QDateTime currentDateTime = QDateTime::currentDateTime();
        record.append(currentDateTime.toString("yyyy-MM-dd hh:mm:ss")+": "+nowQStr+"取相反数:");
        if(nowNum<0){
            nowQStr.remove(QChar('-'));
            nowNum = nowQStr.toDouble();
            qDebug()<<nowQStr.size();
            // ui->lineNow->setText(nowQStr);
            emit nowQStr_changed(nowQStr);
        }
        else{
            nowQStr.prepend('-');
            nowNum = nowQStr.toDouble();
            qDebug()<<nowQStr.size();
            // ui->lineNow->setText(nowQStr);
            emit nowQStr_changed(nowQStr);
        }
        record.append(nowQStr);
        emit calculateRecord(record);
    }
}

void inputWidget::btnReciprocalClick()
{
    if(nowNum==0){
        nowQStr="0";
        // ui->lineNow->setText(nowQStr);
        emit nowQStr_changed(nowQStr);
    }
    else{
        QString record = "";
        QDateTime currentDateTime = QDateTime::currentDateTime();
        record.append(currentDateTime.toString("yyyy-MM-dd hh:mm:ss")+": "+nowQStr+"取倒数:");
        nowNum = 1/nowNum;
        nowQStr = QString::number(nowNum,'f',10);
        nowQStr = clearZero(nowQStr);
        // ui->lineNow->setText(nowQStr);
        record.append(nowQStr);
        emit calculateRecord(record);
        emit nowQStr_changed(nowQStr);
    }
}

void inputWidget::btnCeClick()
{
    nowNum = 0;
    nowQStr.clear();
    nowQStr.append('0');
    // ui->lineNow->setText(nowQStr);
    emit nowQStr_changed(nowQStr);
}

void inputWidget::btnCClick()
{
    nowNum = 0;
    nowQStr.clear();
    nowQStr.append('0');
    // ui->lineNow->setText(nowQStr);
    emit nowQStr_changed(nowQStr);
    beforeNum = 0;
    beforeOp.clear();
    firstStr.clear();
    beforeQStr.clear();
    showBefore();
}

void inputWidget::btnPercentClick()
{
    QString record = "";
    QDateTime currentDateTime = QDateTime::currentDateTime();
    record.append(currentDateTime.toString("yyyy-MM-dd hh:mm:ss")+": "+nowQStr+"取倒数:");
    nowNum = nowNum*0.01;
    nowQStr = QString::number(nowNum,'f',10);
    nowQStr = clearZero(nowQStr);
    // ui->lineNow->setText(nowQStr);
    emit nowQStr_changed(nowQStr);
    record.append(nowQStr);
    emit calculateRecord(record);
}

void inputWidget::btnSqrClick()
{
    QString record = "";
    QDateTime currentDateTime = QDateTime::currentDateTime();
    record.append(currentDateTime.toString("yyyy-MM-dd hh:mm:ss")+": "+nowQStr+"取平方:");
    nowNum = nowNum * nowNum;
    nowQStr = QString::number(nowNum,'f',10);
    nowQStr = clearZero(nowQStr);
    // ui->lineNow->setText(nowQStr);
    record.append(nowQStr);
    emit calculateRecord(record);
    emit nowQStr_changed(nowQStr);
}

void inputWidget::btnSqrtClick()
{
    QString record = "";
    QDateTime currentDateTime = QDateTime::currentDateTime();
    record.append(currentDateTime.toString("yyyy-MM-dd hh:mm:ss")+": "+nowQStr+"开方:");
    nowNum = sqrt(nowNum);
    nowQStr = QString::number(nowNum,'f',10);
    nowQStr = clearZero(nowQStr);
    // ui->lineNow->setText(nowQStr);
    record.append(nowQStr);
    emit calculateRecord(record);
    emit nowQStr_changed(nowQStr);
}

void inputWidget::btnFourCalculateClick()
{
    if(checkOpExist())
        calculate();
    beforeNum = nowNum;
    firstStr = nowQStr;
    beforeOp = qobject_cast<QPushButton*>(sender())->text();
    nowNum = 0;
    nowQStr = QString::number(nowNum);
    // ui->lineNow->setText(nowQStr);
    emit nowQStr_changed(nowQStr);
    showBefore();
}
