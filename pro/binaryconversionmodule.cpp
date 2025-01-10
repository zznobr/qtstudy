#include "binaryconversionmodule.h"
#include "ui_binaryconversionmodule.h"

void BinaryConversionModule::language(QString str)
{
    if(str == "cn"){
        ui->label->setText("进制转换器");
        is_cn = true;
        switchChinese();
    }
    if(str == "en"){
        ui->label->setText("BHD Converter");
        is_cn = false;
        switchEnglish();
    }
}

BinaryConversionModule::BinaryConversionModule(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BinaryConversionModule)
{
    ui->setupUi(this);

    nowLineEditIndex = 0;
    //初始化进制列表
    this->baseList = {{"Binary","二进制"},
                          {"Quaternary","四进制"},
                          {"Octal","八进制"},
                          {"Decimalism","十进制"},
                          {"Hexadecimal","十六进制"}
                          };

    //初始化进制转换列表
    this->baseRates = {{"Binary",2},
                           {"Quaternary",4},
                           {"Octal",8},
                           {"Decimalism",10},
                           {"Hexadecimal",16}
                           };

    inputBox = new BaseInputWidget(this);
    ui->stackedWidget->addWidget(inputBox);
    ui->lineEdit_1->setText("0");
    ui->lineEdit_2->setText("0");

    //MyLineEdit
    connect(ui->lineEdit_1,&MyLineEdit::clicked,this,&BinaryConversionModule::getBase1);
    connect(ui->lineEdit_2,&MyLineEdit::clicked,this,&BinaryConversionModule::getBase2);
    connect(this,&BinaryConversionModule::returnBase,inputBox,&BaseInputWidget::baseChanged);
    connect(inputBox,&BaseInputWidget::nowStr_changed,this,&BinaryConversionModule::showLine);
}

BinaryConversionModule::~BinaryConversionModule()
{
    delete ui;
}

void BinaryConversionModule::switchChinese()
{
    ui->comboBox_1->clear();
    ui->comboBox_2->clear();
    for (const auto& entry : baseList) {
        ui->comboBox_1->addItem(entry.second);
        ui->comboBox_2->addItem(entry.second);
    }
    //初始化为十进制
    ui->comboBox_1->setCurrentIndex(1);
    ui->comboBox_2->setCurrentIndex(1);
}

void BinaryConversionModule::switchEnglish()
{
    ui->comboBox_1->clear();
    ui->comboBox_2->clear();
    for (const auto& entry : baseList) {
        ui->comboBox_1->addItem(entry.first);
        ui->comboBox_2->addItem(entry.first);
    }
    //初始化为十进制
    ui->comboBox_1->setCurrentIndex(1);
    ui->comboBox_2->setCurrentIndex(1);
}


void BinaryConversionModule::on_lineEdit_1_selectionChanged()
{
    // qDebug()<<ui->lineEdit_1->text();
}

void BinaryConversionModule::getBase1()
{
    int baseIndex = ui->comboBox_1->currentIndex();
    QString nowStr = ui->lineEdit_1->text();
    qDebug()<<"the index of selected LineEdit is 1";
    nowLineEditIndex = 1;
    this->updateBase(baseIndex,nowStr);
}

void BinaryConversionModule::getBase2()
{
    int baseIndex = ui->comboBox_2->currentIndex();
    QString nowStr = ui->lineEdit_2->text();
    qDebug()<<"the index of selected LineEdit is 1";
    nowLineEditIndex = 2;
    this->updateBase(baseIndex,nowStr);
}

void BinaryConversionModule::showLine(QString str)
{
    if(nowLineEditIndex != 0){
        if(nowLineEditIndex == 1){
            ui->lineEdit_1->setText(str);
            ui->lineEdit_2->setText(convertNumber(str,base1,base2));
        }
        else{
            ui->lineEdit_2->setText(str);
            ui->lineEdit_1->setText(convertNumber(str,base2,base1));
        }
    }
}


void BinaryConversionModule::on_lineEdit_2_editingFinished()
{
    ;
}


void BinaryConversionModule::on_comboBox_1_currentIndexChanged(int index)
{
    // this->updateBase(index,"updateBase");
    nowLineEditIndex = 0;
    ui->lineEdit_1->setText(convertNumber(ui->lineEdit_1->text(),base1,getBase(1)));
    base1 = getBase(1);
}


void BinaryConversionModule::on_comboBox_2_currentIndexChanged(int index)
{
    // this->updateBase(index,"updateBase");
    nowLineEditIndex = 0;
    ui->lineEdit_2->setText(convertNumber(ui->lineEdit_2->text(),base2,getBase(2)));
    base2 = getBase(2);
}

void BinaryConversionModule::updateBase(int index, QString str)
{
    switch (index) {
    case 0:
        emit this->returnBase(2,str);
        break;
    case 1:
        emit this->returnBase(10,str);
        break;
    case 2:
        emit this->returnBase(16,str);
        break;
    case 3:
        emit this->returnBase(8,str);
        break;
    case 4:
        emit this->returnBase(4,str);
        break;
    default:
        break;
    }
}

int BinaryConversionModule::getBase(int index)
{
    int i = 100;
    if(index == 1)
        i = ui->comboBox_1->currentIndex();
    if(index == 2)
        i = ui->comboBox_2->currentIndex();
    switch (i) {
    case 0:
        return 2;
        break;
    case 1:
        return 10;
        break;
    case 2:
        return 16;
        break;
    case 3:
        return 8;
        break;
    case 4:
        return 4;
        break;
    default:
        return 10;
        break;
    }
}


QString BinaryConversionModule::convertNumber(const QString& str, int fromBase, int toBase) {
    int decimalPlaces = 4;
    // 数字字符到值的映射
    std::unordered_map<char, int> charToValue = {
        {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
        {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
        {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15},
        {'a', 10}, {'b', 11}, {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}
    };

    // 值到数字字符的映射
    std::unordered_map<int, char> valueToChar = {
        {0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'},
        {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}, {9, '9'},
        {10, 'A'}, {11, 'B'}, {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'}
    };

    // 分割整数部分和小数部分
    QString integerPart = str.section('.', 0, 0);
    QString fractionalPart = str.section('.', 1, 1).left(decimalPlaces); // 只取小数点后decimalPlaces位

    // 将整数部分转换为十进制
    long long integerDecimalValue = 0;
    for (char c : integerPart.toStdString()) {
        if (charToValue.find(c) == charToValue.end()) {
            qWarning() << "Invalid character in integer part of input string:" << c;
            return QString(); // 返回空字符串表示错误
        }
        integerDecimalValue = integerDecimalValue * fromBase + charToValue[c];
    }

    // 将小数部分转换为十进制（作为分数处理）
    double fractionalDecimalValue = 0.0;
    double fractionMultiplier = 1.0 / std::pow(fromBase, decimalPlaces);
    for (int i = 0; i < fractionalPart.length(); ++i) {
        char c = fractionalPart[i].toLatin1();
        if (charToValue.find(c) == charToValue.end()) {
            qWarning() << "Invalid character in fractional part of input string:" << c;
            return QString(); // 返回空字符串表示错误
        }
        fractionalDecimalValue += charToValue[c] * std::pow(fromBase, -(i + 1));
    }
    fractionalDecimalValue *= fractionMultiplier; // 调整到正确的比例

    // 合并整数部分和小数部分的十进制值
    double combinedDecimalValue = integerDecimalValue + fractionalDecimalValue;

    // 将合并后的十进制值转换为目标进制字符串
    QString result;
    long long integerResult = static_cast<long long>(combinedDecimalValue);
    double fractionalResult = combinedDecimalValue - integerResult;

    // 转换整数部分
    while (integerResult > 0) {
        int remainder = integerResult % toBase;
        result.prepend(valueToChar[remainder]);
        integerResult /= toBase;
    }
    if (result.isEmpty()) {
        result = "0";
    }

    // 转换小数部分（有限精度）
    QString fractionalResultStr;
    int fractionalDigits = 0;
    while (fractionalResult > 0 && fractionalDigits < decimalPlaces) {
        fractionalResult *= toBase;
        int integerPartOfFraction = static_cast<int>(fractionalResult);
        fractionalResult -= integerPartOfFraction;
        fractionalResultStr.append(valueToChar[integerPartOfFraction]);
        ++fractionalDigits;
    }

    // 如果小数部分不为空，则添加小数点
    if (!fractionalResultStr.isEmpty()) {
        result.append(".");
        result.append(fractionalResultStr);
    }

    return result;
}
