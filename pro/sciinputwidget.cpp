#include "sciinputwidget.h"
#include "ui_sciinputwidget.h"

#include <QDateTime>
#include <QMessageBox>

sciInputWidget::sciInputWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sciInputWidget)
{
    ui->setupUi(this);

    isOp = false;
    nowQStr = "0";
    nowNum = 0;
    firstStr = "";
    nowQStr_changed(nowQStr);

    //connect连接
    //Number输入1~9
    connect(ui->btn0,&QPushButton::clicked,this,&sciInputWidget::btnNumClick);
    connect(ui->btn1,&QPushButton::clicked,this,&sciInputWidget::btnNumClick);
    connect(ui->btn2,&QPushButton::clicked,this,&sciInputWidget::btnNumClick);
    connect(ui->btn3,&QPushButton::clicked,this,&sciInputWidget::btnNumClick);
    connect(ui->btn4,&QPushButton::clicked,this,&sciInputWidget::btnNumClick);
    connect(ui->btn5,&QPushButton::clicked,this,&sciInputWidget::btnNumClick);
    connect(ui->btn6,&QPushButton::clicked,this,&sciInputWidget::btnNumClick);
    connect(ui->btn7,&QPushButton::clicked,this,&sciInputWidget::btnNumClick);
    connect(ui->btn8,&QPushButton::clicked,this,&sciInputWidget::btnNumClick);
    connect(ui->btn9,&QPushButton::clicked,this,&sciInputWidget::btnNumClick);
    //单操作符 %,+/-,.,=....
    connect(ui->btnPOI,&QPushButton::clicked,this,&sciInputWidget::btnPointClick);
    connect(ui->btnDEL,&QPushButton::clicked,this,&sciInputWidget::btnBackClick);
    connect(ui->btnOPP,&QPushButton::clicked,this,&sciInputWidget::btnOppositeClick);
    connect(ui->btnREC,&QPushButton::clicked,this,&sciInputWidget::btnReciprocalClick);
    connect(ui->btnC,&QPushButton::clicked,this,&sciInputWidget::btnCClick);
    connect(ui->btnCE,&QPushButton::clicked,this,&sciInputWidget::btnCeClick);
    connect(ui->btnPER,&QPushButton::clicked,this,&sciInputWidget::btnPercentClick);
    connect(ui->btnSQR,&QPushButton::clicked,this,&sciInputWidget::btnSqrClick);
    connect(ui->btnSQRT,&QPushButton::clicked,this,&sciInputWidget::btnSqrtClick);
    connect(ui->btnRES,&QPushButton::clicked,this,[=](){
        if(checkOpExist())
            calculate();
    });
    //加减乘除 + - * 指数对数 log_ ^_/
    connect(ui->btnADD,&QPushButton::clicked,this,&sciInputWidget::btnCalculateClick);
    connect(ui->btnSUB,&QPushButton::clicked,this,&sciInputWidget::btnCalculateClick);
    connect(ui->btnMUL,&QPushButton::clicked,this,&sciInputWidget::btnCalculateClick);
    connect(ui->btnDIV,&QPushButton::clicked,this,&sciInputWidget::btnCalculateClick);
    connect(ui->btnLOG,&QPushButton::clicked,this,&sciInputWidget::btnCalculateClick);
    connect(ui->btnINDEX,&QPushButton::clicked,this,&sciInputWidget::btnCalculateClick);
    //sin cos tan
    connect(ui->btnSIN,&QPushButton::clicked,this,&sciInputWidget::btnTrigCalculateClick);
    connect(ui->btnCOS,&QPushButton::clicked,this,&sciInputWidget::btnTrigCalculateClick);
    connect(ui->btnTAN,&QPushButton::clicked,this,&sciInputWidget::btnTrigCalculateClick);
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

sciInputWidget::~sciInputWidget()
{
    delete ui;
}

bool sciInputWidget::checkOpExist()
{
    if(beforeOp=="-"||beforeOp=="+"||beforeOp=="/"||beforeOp=="*"||beforeOp=="log_"||beforeOp=="^_")
        return true;
    return false;
}

void sciInputWidget::showBefore()
{
    beforeQStr = firstStr + beforeOp ;
    // ui->lineBefore->setText(beforeQStr);
    emit beforeQStr_changed(beforeQStr);
}

void sciInputWidget::calculate()
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
        if(beforeOp == "log_"){
            if(beforeNum <= 0){
                QMessageBox::warning(this,"警告","真数不能小于等于0");
            }
            else if(nowNum == 1 || nowNum < 0){
                QMessageBox::warning(this,"警告","底数不能为1或小于0");
            }else{
                nowNum = std::log(beforeNum) / std::log(nowNum);
            }
        }
        if(beforeOp == "^_"){
            if(beforeNum == 0 && nowNum <= 0){
                QMessageBox::warning(this,"警告","底数为0时，指数不能小于等于0");
            }else
            if(beforeNum < 0 && (!std::floor(nowNum) == nowNum) ){
                QMessageBox::warning(this,"警告","底数小于0时，指数不支持非整数");
            }else
                nowNum = std::pow(beforeNum, nowNum);
        }
        beforeNum = 0;
        firstStr.clear();
        beforeOp.clear();
        showBefore();
        nowQStr = QString::number(nowNum);
        nowQStr = clearZero(nowQStr);
        record.append(nowQStr);
        calculateRecord(record);
        // ui->lineNow->setText(nowQStr);
        emit nowQStr_changed(nowQStr);
    }
}

QString sciInputWidget::clearZero(QString str)
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

void sciInputWidget::language(QString str)
{
    if(str == "cn"){
        ui->btnOPP->setText("相反数");
        ui->btnPER->setText("百分比");
        ui->btnSQR->setText("平方");
        ui->btnSQRT->setText("开方");
        ui->btnCE->setText("清空");
        ui->btnC->setText("清空一行");
        ui->btnDEL->setText("退格");
        ui->btnSIN->setText("正弦");
        ui->btnCOS->setText("余弦");
        ui->btnTAN->setText("正切");
        ui->btnREC->setText("倒数");
        ui->btnROOT->setText("平方根");
    }
    if(str == "en"){
        ui->btnOPP->setText("OPP");
        ui->btnPER->setText("%");
        ui->btnSQR->setText("sqr");
        ui->btnSQRT->setText("sqrt");
        ui->btnCE->setText("C");
        ui->btnC->setText("CE");
        ui->btnDEL->setText("Del");
        ui->btnSIN->setText("sin");
        ui->btnCOS->setText("cos");
        ui->btnTAN->setText("tan");
        ui->btnREC->setText("1/X");
        ui->btnROOT->setText("root");
    }
}

void sciInputWidget::btnNumClick()
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

void sciInputWidget::btnPointClick()
{
    if(!nowQStr.contains('.')){
        nowQStr = nowQStr + qobject_cast<QPushButton*>(sender())->text();
        // ui->lineNow->setText(nowQStr);
        emit nowQStr_changed(nowQStr);
    }
}

void sciInputWidget::btnBackClick()
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

void sciInputWidget::btnOppositeClick()
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

void sciInputWidget::btnReciprocalClick()
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

void sciInputWidget::btnCeClick()
{
    nowNum = 0;
    nowQStr.clear();
    nowQStr.append('0');
    // ui->lineNow->setText(nowQStr);
    emit nowQStr_changed(nowQStr);
}

void sciInputWidget::btnCClick()
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

void sciInputWidget::btnPercentClick()
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

void sciInputWidget::btnSqrClick()
{
    QString record = "";
    QDateTime currentDateTime = QDateTime::currentDateTime();
    record.append(currentDateTime.toString("yyyy-MM-dd hh:mm:ss")+": "+nowQStr+"取平方:");
    nowNum = nowNum * nowNum;
    nowQStr = QString::number(nowNum,'f',10);
    nowQStr = clearZero(nowQStr);
    // ui->lineNow->setText(nowQStr);
    emit nowQStr_changed(nowQStr);
    record.append(nowQStr);
    emit calculateRecord(record);
}

void sciInputWidget::btnSqrtClick()
{
    QString record = "";
    QDateTime currentDateTime = QDateTime::currentDateTime();
    record.append(currentDateTime.toString("yyyy-MM-dd hh:mm:ss")+": "+nowQStr+"开方:");
    nowNum = sqrt(nowNum);
    nowQStr = QString::number(nowNum,'f',10);
    nowQStr = clearZero(nowQStr);
    // ui->lineNow->setText(nowQStr);
    emit nowQStr_changed(nowQStr);
    record.append(nowQStr);
    emit calculateRecord(record);
}

void sciInputWidget::btnCalculateClick()
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

void sciInputWidget::btnTrigCalculateClick()
{
    QString trig = qobject_cast<QPushButton*>(sender())->text();
    QString record = "";
    QDateTime currentDateTime = QDateTime::currentDateTime();
    record.append(currentDateTime.toString("yyyy-MM-dd hh:mm:ss")+": "+trig+nowQStr+":");
    if (trig == "sin"||trig == "正弦") {
        nowNum = std::sin(nowNum);
        nowQStr = QString::number(nowNum);
        emit nowQStr_changed(nowQStr);
    } else if (trig == "cos"||trig == "余弦") {
        nowNum = std::cos(nowNum);
        nowQStr = QString::number(nowNum);
        emit nowQStr_changed(nowQStr);
    } else if (trig == "tan"||trig == "正切") {
        if (std::fmod(nowNum, M_PI / 2) == 0 && (static_cast<int>(nowNum / (M_PI / 2)) % 2 == 1)) {
            QMessageBox::critical(nullptr, "错误", "输入的数值对于正切函数无定义，请重新输入合适的值");
        }
        nowNum = std::tan(nowNum);
        nowQStr = QString::number(nowNum);
        emit nowQStr_changed(nowQStr);
    } else {
        QMessageBox::warning(nullptr, "错误", "请输入有效的三角函数类型（sin、cos、tan）");
    }
    record.append(nowQStr);
    emit calculateRecord(record);
}

void sciInputWidget::on_btnROOT_clicked()
{
    double inputNum = nowNum;
    QString record = "";
    QDateTime currentDateTime = QDateTime::currentDateTime();
    record.append(currentDateTime.toString("yyyy-MM-dd hh:mm:ss")+": "+nowQStr+"平方根:");
    if (nowNum >= 0) {
        double squareRoot = std::sqrt(inputNum);
        QMessageBox::information(nullptr, "平方根结果", QString("输入数字的平方根是: +%1/-%2").arg(squareRoot).arg(squareRoot));
        record.append(QString("+%1/-%2").arg(squareRoot).arg(squareRoot));
    } else {
        QMessageBox::warning(nullptr, "错误", "请输入有效的数字");
    }
}

