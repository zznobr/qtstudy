#include "datawidget.h"
#include "ui_datawidget.h"

#include <QTimer>

void dataWidget::language(QString str)
{
    if(str == "cn"){
        ui->addData->setText("加日期");
        ui->subData->setText("减日期");
        ui->label->setText("日期差:");
        is_cn = true;
    }
    if(str == "en"){
        ui->addData->setText("Add Date");
        ui->subData->setText("Sub Date");
        ui->label->setText("Date difference:");
        is_cn = false;
    }
}

dataWidget::dataWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::dataWidget)
{
    ui->setupUi(this);
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &dataWidget::updateDateTime);
    m_timer->start(1000);
    updateDateTime();
    is_cn = true;
}

dataWidget::~dataWidget()
{
    delete ui;
}

QDate dataWidget::addDaysToDate(QDate date, int days)
{
    return date.addDays(days);
}

QDate dataWidget::subtractDaysFromDate(QDate date, int days)
{
    return date.addDays(-days);
}

int dataWidget::daysBetweenDates(QDate date1, QDate date2)
{
    return date1.daysTo(date2);
}

void dataWidget::dateChange(QDate date1, QDate date2)
{
    ui->spinBox->setValue(daysBetweenDates(date1,date2));
}

void dataWidget::updateDateTime()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    // qDebug()<<"当前时间:"+currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    if(is_cn)
        ui->dateLabel->setText("当前时间:"+currentDateTime.toString("yyyy-MM-dd hh:mm:ss"));
    else
        ui->dateLabel->setText("Current Time:"+currentDateTime.toString("yyyy-MM-dd hh:mm:ss"));
}

void dataWidget::on_nowData_dateChanged(const QDate &date)
{
    // qDebug()<<"1";
    this->dateChange(ui->nowData->date(),ui->toData->date());
}


void dataWidget::on_toData_dateChanged(const QDate &date)
{
    // qDebug()<<"2";
    this->dateChange(ui->nowData->date(),ui->toData->date());
}


void dataWidget::on_addData_clicked()
{
    ui->nowData->setDate(addDaysToDate(ui->nowData->date(),ui->spinData->value()));
}


void dataWidget::on_subData_clicked()
{
    ui->nowData->setDate(subtractDaysFromDate(ui->nowData->date(),ui->spinData->value()));
}

