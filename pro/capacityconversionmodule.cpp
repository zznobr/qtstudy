#include "capacityconversionmodule.h"
#include "ui_capacityconversionmodule.h"

void CapacityConversionModule::language(QString str)
{
    if(str == "cn"){
        ui->title->setText("容量换算");
        is_cn = true;
    }
    if(str == "en"){
        ui->title->setText("Capacity Converter");
        is_cn = false;
    }
    updataTip();
}

CapacityConversionModule::CapacityConversionModule(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CapacityConversionModule)
{
    ui->setupUi(this);

    //初始化容积列表
    this->capacityList = {
        // {"m3", "立方米"},
        {"dm3", "立方分米"},
        {"cc", "立方厘米"},
        {"l", "升"},
        {"dl", "分升"},
        {"ml", "毫升"},
        // {"bbl", "桶"},
        {"gal", "加仑"},
        {"cup", "杯"},
    };

    //初始化容积转换列表
    this->capacityRates = {
        // {"m3", 0.001},
        {"dm3", 1},
        {"cc", 1000},
        {"l", 1},
        {"dl", 10},
        {"ml", 1000},
        // {"bbl", 0.0062898},
        {"gal", 0.264172},
        {"cup", 4.226753},
    };
    loadData();

    capacity1 = "dm3";
    capacity2 = "dm3";
    updataTip();

}

CapacityConversionModule::~CapacityConversionModule()
{
    delete ui;
}

double CapacityConversionModule::getRate(QString fromCapacity, QString toCapacity)
{
    double returnRate = 0;
    returnRate = capacityRates.find(toCapacity)->second / capacityRates.find(fromCapacity)->second;
    return returnRate;
}

void CapacityConversionModule::loadData()
{
    ui->comboBox_1->clear();
    ui->comboBox_2->clear();
    ui->doubleSpinBox_1->setValue(0);
    ui->doubleSpinBox_2->setValue(0);
    if(!is_cn){
        for(const auto&entry : capacityList){
            ui->comboBox_1->addItem(entry.first);
            ui->comboBox_2->addItem(entry.first);
        }
    }
    if(is_cn){
        for(const auto&entry : capacityList){
            ui->comboBox_1->addItem(entry.second);
            ui->comboBox_2->addItem(entry.second);
        }
    }
}

QString CapacityConversionModule::getName(QString str)
{
    // qDebug()<<str<<"1";
    for(const auto&entry : capacityList){
        if(entry.first == str||entry.second == str){
            return entry.first;
        }
    }
    return "m3";
}

void CapacityConversionModule::updataTip()
{
    QString tip = "";
    tip.append("1"+ui->comboBox_1->currentText()+" = "+QString::number(getRate(capacity1,capacity2))+ui->comboBox_2->currentText());
    ui->tip1->setText(tip);
    tip.clear();
    tip.append("1"+ui->comboBox_2->currentText()+" = "+QString::number(getRate(capacity2,capacity1))+ui->comboBox_1->currentText());
    ui->tip2->setText(tip);
}

void CapacityConversionModule::on_comboBox_1_currentTextChanged(const QString &arg1)
{
    capacity1 = getName(arg1);
    // qDebug()<<capacity1;
    double rate = getRate(capacity1,capacity2);
    ui->doubleSpinBox_2->setValue(ui->doubleSpinBox_1->value()*rate);
    updataTip();
}


void CapacityConversionModule::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    capacity2 = getName(arg1);
    // qDebug()<<capacity2;
    double rate = getRate(capacity2,capacity1);
    ui->doubleSpinBox_1->setValue(ui->doubleSpinBox_2->value()*rate);
    updataTip();
}


void CapacityConversionModule::on_doubleSpinBox_1_valueChanged(double arg1)
{
    double value = arg1;
    double rate = getRate(capacity1,capacity2);
    double toValue = ui->doubleSpinBox_2->value();
    if(value*rate != toValue)
        ui->doubleSpinBox_2->setValue(rate*value);
}


void CapacityConversionModule::on_doubleSpinBox_2_valueChanged(double arg1)
{
    double value = arg1;
    double rate = getRate(capacity2,capacity1);
    double toValue = ui->doubleSpinBox_1->value();
    if(value*rate != toValue)
        ui->doubleSpinBox_1->setValue(rate*value);
}

