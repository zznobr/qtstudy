#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <QEvent>
#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QDialog>
#include <QColorDialog>
#include <QPainter>
#include "binaryconversionmodule.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);
    history = new historyWidget();
    history->hide();

    this->standardInputBox = new inputWidget(this);
    connect(this->standardInputBox,&inputWidget::beforeQStr_changed,this,&MainWindow::showLineBefore);
    connect(this->standardInputBox,&inputWidget::nowQStr_changed,this,&MainWindow::showLineNow);

    this->sciInputBox = new sciInputWidget(this);
    connect(this->sciInputBox,&sciInputWidget::beforeQStr_changed,this,&MainWindow::showLineBefore);
    connect(this->sciInputBox,&sciInputWidget::nowQStr_changed,this,&MainWindow::showLineNow);

    this->dateView = new dataWidget(this);
    ui->dateStacked->addWidget(dateView);

    this->bitWiseView = new bitWise(this);
    ui->bitWiseStacked->addWidget(bitWiseView);

    //恢复转换页
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onTabChanged(int)));

    ui->inputStacked->addWidget(standardInputBox);
    ui->inputStacked->addWidget(sciInputBox);
    // this->on_selectComboBox_currentTextChanged("标准计算");
    // qDebug()<<ui->inputStacked->count();

    //进制模块初始化以及加入页栈中
    baseConversionModule = new BinaryConversionModule(this);
    ui->transformStacked->addWidget(baseConversionModule);
    //汇率转换模块
    rateModule = new ExchangeRateConversionModule(this);
    ui->transformStacked->addWidget(rateModule);
    //容量转换模块
    capacityModule = new CapacityConversionModule(this);
    ui->transformStacked->addWidget(capacityModule);

    //历史记录写入
    connect(standardInputBox,&inputWidget::calculateRecord,history,&historyWidget::writeStringToHistory);
    connect(sciInputBox,&sciInputWidget::calculateRecord,history,&historyWidget::writeStringToHistory);
    connect(bitWiseView,&bitWise::calculateRecord,history,&historyWidget::writeStringToHistory);

    //初始中文
    this->on_comboBox_2_currentTextChanged("中文");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCentralWidgetStyle(QString styleSheetContent)
{
    ui->centralwidget->setStyleSheet(styleSheetContent);
}

QColor MainWindow::calculateContrastColor(const QColor &color)
{
    double rLinear = sRGBToLinear(color.redF());
    double gLinear = sRGBToLinear(color.greenF());
    double bLinear = sRGBToLinear(color.blueF());
    double luminance = 0.2126 * rLinear + 0.7152 * gLinear + 0.0722 * bLinear;
    return luminance > 0.5? Qt::black : Qt::white;
}

double MainWindow::sRGBToLinear(double value)
{
    if (value <= 0.04045) {
        return value / 12.92;
    }
    return std::pow((value + 0.055) / 1.055, 2.4);
}


void MainWindow::showLineBefore(QString str)
{
    ui->lineBefore->setText(str);
}

void MainWindow::showLineNow(QString str)
{
    ui->lineNow->setText(str);
}


void MainWindow::on_btnBaseConversion_clicked()
{
    toBinaryConversionModule();
}

void MainWindow::toBinaryConversionModule()
{
    ui->transformStacked->setCurrentWidget(baseConversionModule);
}

void MainWindow::onTabChanged(int index)
{
    if (index != 1)
    {
        ui->transformStacked->setCurrentIndex(0);
    }
}

void MainWindow::writeToHistory(QString str)
{
    history->writeStringToHistory(str);
}


void MainWindow::on_selectComboBox_currentTextChanged(const QString &arg1)
{
    qDebug()<<arg1;
    QString toPage = arg1;
    if(toPage == "标准计算"|| toPage == "Standard calculation"){
        ui->inputStacked->setCurrentWidget(standardInputBox);
        ui->tabWidget->setCurrentIndex(0);
    }
    if(toPage == "科学计算"|| toPage == "Scientific computing"){
        ui->inputStacked->setCurrentWidget(sciInputBox);
        ui->tabWidget->setCurrentIndex(0);
    }
    if(toPage == "日期计算"|| toPage == "Date calculation"){
        ui->tabWidget->setCurrentIndex(3);
    }
    if(toPage == "进制换算"|| toPage == "Binary conversion"){
        ui->tabWidget->setCurrentIndex(1);
        this->on_btnBaseConversion_clicked();
    }
    if(toPage == "汇率转换"|| toPage == "Converter"){
        ui->tabWidget->setCurrentIndex(1);
        this->on_btnRateConversion_clicked();
    }
    if(toPage == "容量转换"|| toPage == "Capacity conversion"){
        ui->tabWidget->setCurrentIndex(1);
        this->on_btnCapacityConversion_clicked();
    }

}


void MainWindow::on_btnDateCalculate_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}


void MainWindow::on_btnRateConversion_clicked()
{
    ui->transformStacked->setCurrentWidget(rateModule);
}


void MainWindow::on_btnCapacityConversion_clicked()
{
    ui->transformStacked->setCurrentWidget(capacityModule);
}


void MainWindow::on_pushButton_clicked()
{
    ;
}


void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    QString language = arg1;
    if(language == "中文"){
        ui->selectComboBox->clear();
        ui->selectComboBox->addItem("标准计算");
        ui->selectComboBox->addItem("科学计算");
        ui->selectComboBox->addItem("日期计算");
        ui->selectComboBox->addItem("进制换算");
        ui->selectComboBox->addItem("汇率转换");
        ui->selectComboBox->addItem("容量转换");
        ui->btnHistory->setText("历史记录");
        ui->title->setText("快捷选择:");
        ui->tabWidget->setTabText(0,"计算");
        ui->tabWidget->setTabText(1,"转换");
        ui->tabWidget->setTabText(2,"按位运算");
        ui->tabWidget->setTabText(3,"日期运算");
        ui->tabWidget->setTabText(4,"设置");
        ui->btnBaseConversion->setText("进制转换");
        ui->btnDateCalculate->setText("日期加减");
        ui->btnRateConversion->setText("汇率转换");
        ui->btnCapacityConversion->setText("容量转换");
        ui->label->setText("开发者：张桓瑜");
        ui->label_2->setText("联系方式：2043181861（QQ）");
        ui->label_3->setText("主题：");
        ui->label_4->setText("语言：");
        ui->label_5->setText("字体大小：");
        ui->pushButton_2->setText("界面颜色：");
        ui->comboBox->clear();
        ui->comboBox->addItem("白天模式");
        ui->comboBox->addItem("夜间模式");
        this->standardInputBox->language("cn");
        this->sciInputBox->language("cn");
        this->bitWiseView->language("cn");
        this->history->language("cn");
        this->dateView->language("cn");
        this->rateModule->language("cn");
        this->capacityModule->language("cn");
        this->baseConversionModule->language("cn");
    }
    if(language == "English"){
        ui->selectComboBox->clear();
        ui->selectComboBox->addItem("Standard calculation");
        ui->selectComboBox->addItem("Scientific computing");
        ui->selectComboBox->addItem("Date calculation");
        ui->selectComboBox->addItem("Binary conversion");
        ui->selectComboBox->addItem("Converter");
        ui->selectComboBox->addItem("Capacity conversion");
        ui->btnHistory->setText("History Record");
        ui->title->setText("Quick selection:");
        ui->tabWidget->setTabText(0,"Calculation");
        ui->tabWidget->setTabText(1,"Transform");
        ui->tabWidget->setTabText(2,"Binary");
        ui->tabWidget->setTabText(3,"Date");
        ui->tabWidget->setTabText(4,"Setting");
        ui->btnBaseConversion->setText("Decimal conversion");
        ui->btnDateCalculate->setText("Date calculation");
        ui->btnRateConversion->setText("Converter");
        ui->btnCapacityConversion->setText("Capacity conversion");
        ui->label->setText("Developer: Zhang Huanyu");
        ui->label_2->setText("Contact information:2043181861");
        ui->label_3->setText("Theme:");
        ui->label_4->setText("Language:");
        ui->label_5->setText("Font-Size:");
        ui->pushButton_2->setText("Interface Color");
        ui->comboBox->clear();
        ui->comboBox->addItem("Daytime mode");
        ui->comboBox->addItem("Night mode");
        this->standardInputBox->language("en");
        this->sciInputBox->language("en");
        this->bitWiseView->language("en");
        this->history->language("en");
        this->dateView->language("en");
        this->rateModule->language("en");
        this->capacityModule->language("en");
        this->baseConversionModule->language("en");
    }
}


void MainWindow::on_btnHistory_clicked()
{
    history->show();
    history->readHistoryToTextEdit();
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0){
        this->setCentralWidgetStyle("background-color: white;color:black;");
    }
    else
        this->setCentralWidgetStyle("background-color: rgb(40, 40, 40);color: rgb(255, 255, 255);");
}


void MainWindow::on_pushButton_2_clicked()
{
    QColor selectedColor = QColorDialog::getColor(Qt::white, nullptr);
    if (selectedColor.isValid()) {
        ui->centralwidget->setStyleSheet(QString("QWidget { background-color: %1; }").arg(selectedColor.name()));
        QColor textColor = calculateContrastColor(selectedColor);
        // 设置字体颜色样式
        ui->centralwidget->setStyleSheet(ui->centralwidget->styleSheet() + QString(" QWidget { color: %1; }").arg(textColor.name()));
    }
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->tabWidget->setStyleSheet("font-size:"+QString::number(arg1)+"px;");
}

