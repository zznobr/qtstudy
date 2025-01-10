#include "exchangerateconversionmodule.h"
#include "ui_exchangerateconversionmodule.h"

#include <QMessageBox>

void ExchangeRateConversionModule::language(QString str)
{
    if(str == "cn"){
        ui->title->setText("汇率换算");
        ui->btnAddRate->setText("新增汇率");
        is_cn = true;
    }
    if(str == "en"){
        ui->title->setText("Currency Converter");
        ui->btnAddRate->setText("Add Exchange Rate");
        is_cn = false;
    }
    updataTip();
}

ExchangeRateConversionModule::ExchangeRateConversionModule(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExchangeRateConversionModule)
{
    ui->setupUi(this);

    //初始化币种列表
    this->currencyList = {{"CNY", "人民币"},
                          {"USD", "美元"},
                          {"JPY", "日元"},
                          {"EUR", "欧元"},
                          {"GBP", "英镑"},
                          {"RUB", "卢布"},
                          {"KRW", "韩元"},
                          {"AUD", "澳大利亚元"},
                          {"HKD", "港元"},
                          {"MOP", "澳元"},
                          {"TWD", "台元"}};

    //初始化汇率表
    this->exchangeRates = {{"CNY", 1},
                           {"USD", 0.14},
                           {"JPY", 20.59},
                           {"EUR", 0.13},
                           {"GBP", 0.11},
                           {"RUB", 14.58},
                           {"KRW", 192.4},
                           {"AUD", 0.21},
                           {"HKD", 1.07},
                           {"MOP", 1.1},
                           {"TWD", 4.47}};
    loadData();

    currency1 = "AUD";
    currency2 = "AUD";
    updataTip();

}

ExchangeRateConversionModule::~ExchangeRateConversionModule()
{
    delete ui;
}

// 添加汇率
void ExchangeRateConversionModule::addRate(QString enName,  QString cnName, double rate)
{
    bool isExist = false;
    if (this->currencyList.count(enName) == 0){
        for(const auto&entry : currencyList){
            if(entry.second==cnName)
                isExist = true;
        }
    }
    if(!isExist){
        currencyList[enName] = cnName;
        exchangeRates[enName] = rate;
    }
    loadData();
}

// 获取汇率
double ExchangeRateConversionModule::getRate(QString fromCurrency, QString toCurrency)
{
    double returnRate = 0;
    returnRate = exchangeRates.find(toCurrency)->second / exchangeRates.find(fromCurrency)->second;
    return returnRate;
}

void ExchangeRateConversionModule::loadData()
{
    ui->comboBox_1->clear();
    ui->comboBox_2->clear();
    ui->doubleSpinBox_1->setValue(0);
    ui->doubleSpinBox_2->setValue(0);
    if(!is_cn){
        for(const auto&entry : currencyList){
            ui->comboBox_1->addItem(entry.first);
            ui->comboBox_2->addItem(entry.first);
        }
    }
    if(is_cn){
        for(const auto&entry : currencyList){
            ui->comboBox_1->addItem(entry.second);
            ui->comboBox_2->addItem(entry.second);
        }
    }
}

QString ExchangeRateConversionModule::getName(QString str)
{
    // qDebug()<<str<<"1";
    for(const auto&entry : currencyList){
        if(entry.first == str||entry.second == str){
            return entry.first;
        }
    }
    // QMessageBox::warning(this,"警告","未寻找到所选择币种,默认为CNY");
    return "CNY";
}

void ExchangeRateConversionModule::updataTip()
{
    QString tip = "";
    tip.append("1"+ui->comboBox_1->currentText()+" = "+QString::number(getRate(currency1,currency2))+ui->comboBox_2->currentText());
    ui->tip1->setText(tip);
    tip.clear();
    tip.append("1"+ui->comboBox_2->currentText()+" = "+QString::number(getRate(currency2,currency1))+ui->comboBox_1->currentText());
    ui->tip2->setText(tip);
}

void ExchangeRateConversionModule::on_comboBox_1_currentTextChanged(const QString &arg1)
{
    currency1 = getName(arg1);
    // qDebug()<<currency1;
    double rate = getRate(currency1,currency2);
    ui->doubleSpinBox_2->setValue(ui->doubleSpinBox_1->value()*rate);
    updataTip();
}


void ExchangeRateConversionModule::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    currency2 = getName(arg1);
    // qDebug()<<currency2;
    double rate = getRate(currency2,currency1);
    ui->doubleSpinBox_1->setValue(ui->doubleSpinBox_2->value()*rate);
    updataTip();
}


void ExchangeRateConversionModule::on_doubleSpinBox_1_valueChanged(double arg1)
{
    double value = arg1;
    double rate = getRate(currency1,currency2);
    double toValue = ui->doubleSpinBox_2->value();
    if(value*rate != toValue)
        ui->doubleSpinBox_2->setValue(rate*value);
}


void ExchangeRateConversionModule::on_doubleSpinBox_2_valueChanged(double arg1)
{
    double value = arg1;
    double rate = getRate(currency2,currency1);
    double toValue = ui->doubleSpinBox_1->value();
    if(value*rate != toValue)
        ui->doubleSpinBox_1->setValue(rate*value);
}


void ExchangeRateConversionModule::on_btnAddRate_clicked()
{
    addRateDialog = new AddRateDialog(this);
    if (addRateDialog->exec() == QDialog::Accepted) {
        this->addRate(addRateDialog->nameEnglish(),addRateDialog->nameChinese(),addRateDialog->rate());
    }
}

