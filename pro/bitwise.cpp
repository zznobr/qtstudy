#include "bitwise.h"
#include "ui_bitwise.h"

#include <QDateTime>
#include <QMessageBox>

void bitWise::language(QString str)
{
    if(str == "cn"){
        ui->btnAND->setText("与");
        ui->btnOR->setText("或");
        ui->btnXOR->setText("异或");
        ui->btnLEFT->setText("左移");
        ui->btnRIGHT->setText("右移");
        ui->btnDEL->setText("删除");
        ui->btnTEN->setText("10进制");
    }
    if(str == "en"){
        ui->btnAND->setText("And");
        ui->btnOR->setText("Or");
        ui->btnXOR->setText("Xor");
        ui->btnLEFT->setText("leftShit");
        ui->btnRIGHT->setText("rightShit");
        ui->btnDEL->setText("Del");
        ui->btnTEN->setText("Decimalism");
    }
}

bitWise::bitWise(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::bitWise)
{
    ui->setupUi(this);

    firstStr = "0";
    nowQStr = "0";
    beforeQStr = "0";
    isOp = false;

    connect(ui->btn0,&QPushButton::clicked,this,&bitWise::btnNumClick);
    connect(ui->btn1,&QPushButton::clicked,this,&bitWise::btnNumClick);
    connect(ui->btnDEL,&QPushButton::clicked,this,&bitWise::btnBackClick);
    connect(ui->btnClear,&QPushButton::clicked,this,&bitWise::btnCClick);
    connect(ui->btnCE,&QPushButton::clicked,this,&bitWise::btnCeClick);

    connect(ui->btnAND,&QPushButton::clicked,this,&bitWise::dualOp);
    connect(ui->btnOR,&QPushButton::clicked,this,&bitWise::dualOp);
    connect(ui->btnXOR,&QPushButton::clicked,this,&bitWise::dualOp);
    connect(ui->btnRES,&QPushButton::clicked,[=](){
        this->calculate();
    });
}

bitWise::~bitWise()
{
    delete ui;
}

bool bitWise::checkOpExist()
{
    if(beforeOp=="And"||beforeOp=="Or"||beforeOp=="Xor")
        return true;
    return false;
}

void bitWise::showBefore()
{
    beforeQStr = firstStr + beforeOp ;
    ui->lineBefore->setText(beforeQStr);
}

void bitWise::calculate()
{
    // qDebug()<<beforeOp;
    QString record = "";
    QDateTime currentDateTime = QDateTime::currentDateTime();
    record.append(currentDateTime.toString("yyyy-MM-dd hh:mm:ss")+": "+firstStr+" "+beforeOp+" "+nowQStr+" = ");
    if(beforeOp == "And"||beforeOp == "与")
        nowQStr = bitwiseAnd(firstStr,nowQStr);
    if(beforeOp == "Or"||beforeOp == "或")
        nowQStr = bitwiseOr(firstStr,nowQStr);
    if(beforeOp == "Xor"||beforeOp == "异或")
        nowQStr = bitwiseXor(firstStr,nowQStr);
    firstStr.clear();
    beforeOp.clear();
    nowQStr = clearZero(nowQStr);
    showBefore();
    ui->lineNow->setText(nowQStr);
    record.append(nowQStr);
    emit calculateRecord(record);
}

QString bitWise::clearZero(QString str)
{
    int index = 0;
    while (index < str.size() && str.at(index) == '0') {
        index++;
    }
    return str.mid(index);
}

int bitWise::binaryStringToInt(const QString binStr)
{
    return binStr.toInt(nullptr, 2);
}

QString bitWise::intToBinaryString(int num, int bitLength)
{
    QString result = QString::number(num, 2);
    if (bitLength > 0) {
        result = result.rightJustified(bitLength, '0');
    }
    return result;
}

QString bitWise::bitwiseAnd(QString str1, QString str2)
{
    int num1 = binaryStringToInt(str1);
    int num2 = binaryStringToInt(str2);
    int result = num1 & num2;
    return intToBinaryString(result, std::max(str1.size(), str2.size()));
}

QString bitWise::bitwiseOr(QString str1, QString str2)
{
    int num1 = binaryStringToInt(str1);
    int num2 = binaryStringToInt(str2);
    int result = num1 | num2;
    return intToBinaryString(result, std::max(str1.size(), str2.size()));
}

QString bitWise::bitwiseXor(QString str1, QString str2)
{
    int num1 = binaryStringToInt(str1);
    int num2 = binaryStringToInt(str2);
    int result = num1 ^ num2;
    return intToBinaryString(result, std::max(str1.size(), str2.size()));
}

QString bitWise::leftShift(QString str, int shiftAmount)
{
    QString record = "";
    QDateTime currentDateTime = QDateTime::currentDateTime();
    record.append(currentDateTime.toString("yyyy-MM-dd hh:mm:ss")+": "+nowQStr+"左移1位:");
    int num = binaryStringToInt(str);
    int result = num << shiftAmount;
    return intToBinaryString(result, str.size() + shiftAmount);
    record.append(nowQStr);
    emit calculateRecord(record);
}

QString bitWise::rightShift(QString str, int shiftAmount)
{
    QString record = "";
    QDateTime currentDateTime = QDateTime::currentDateTime();
    record.append(currentDateTime.toString("yyyy-MM-dd hh:mm:ss")+": "+nowQStr+"右移1位:");
    int num = binaryStringToInt(str);
    int result = num >> shiftAmount;
    return intToBinaryString(result, str.size() - shiftAmount);
    record.append(nowQStr);
    emit calculateRecord(record);
}

void bitWise::btnNumClick()
{
    if(nowQStr=="0"){
        nowQStr = qobject_cast<QPushButton*>(sender())->text();
        ui->lineNow->setText(nowQStr);
    }
    else{
        if(isOp){
            nowQStr = "";
            ui->lineNow->setText(nowQStr);
            isOp = false;
        }
        nowQStr = nowQStr + qobject_cast<QPushButton*>(sender())->text();
        ui->lineNow->setText(nowQStr);
    }
}

void bitWise::btnBackClick()
{
    if(nowQStr!="0"){
        nowQStr.chop(1);
        if(nowQStr==""){
            nowQStr="0";
            ui->lineNow->setText(nowQStr);
        }
        else{
            ui->lineNow->setText(nowQStr);
        }
    }
}

void bitWise::btnCClick()
{
    nowQStr.clear();
    nowQStr.append('0');
    ui->lineNow->setText(nowQStr);
    beforeOp.clear();
    firstStr.clear();
    beforeQStr.clear();
    showBefore();
}

void bitWise::btnCeClick()
{
    nowQStr.clear();
    nowQStr.append('0');
    ui->lineNow->setText(nowQStr);
}

void bitWise::dualOp()
{
    if(checkOpExist()){
        calculate();
    }
    firstStr = nowQStr;
    beforeOp = qobject_cast<QPushButton*>(sender())->text();
    nowQStr = "0";
    ui->lineNow->setText(nowQStr);
    showBefore();
}

void bitWise::on_btnLEFT_clicked()
{
    nowQStr = leftShift(nowQStr,1);
    ui->lineNow->setText(nowQStr);
}

void bitWise::on_btnRIGHT_clicked()
{
    nowQStr = rightShift(nowQStr,1);
    ui->lineNow->setText(nowQStr);
}


void bitWise::on_btnTEN_clicked()
{
    bool ok;
    int decimalValue = nowQStr.toInt(&ok, 2);
    if (ok) {
        QString message = QString("该二进制数 %1 对应的十进制数为: %2")
                              .arg(nowQStr)
                              .arg(decimalValue);
        QMessageBox::information(nullptr, "二进制转十进制提示", message);
    } else {
        QMessageBox::warning(nullptr, "错误提示", "输入的不是合法的二进制数，请重新输入！");
    }
}

