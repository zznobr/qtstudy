#include "historywidget.h"
#include "ui_historywidget.h"

#include <QFile>

void historyWidget::readHistoryToTextEdit()
{
    QFile file("history.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;
        while (in.readLineInto(&line)) {
            ui->textEdit->append(line);
        }
        file.close();
    }
}

void historyWidget::writeStringToHistory(QString content)
{
    QFile file("history.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << content << "\n";
        file.close();
    }
}

void historyWidget::clearHistoryFile()
{
    QFile file("history.txt");
    if (file.open(QIODevice::WriteOnly)) {
        file.resize(0);
        file.close();
    }
}

void historyWidget::language(QString str)
{
    if(str == "en"){
        ui->label->setText("History Record");
        ui->pushButton->setText("Clear");
    }
    if(str == "cn"){
        ui->label->setText("历史记录");
        ui->pushButton->setText("清空");
    }
}


historyWidget::historyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::historyWidget)
{
    ui->setupUi(this);
}

historyWidget::~historyWidget()
{
    delete ui;
}

void historyWidget::on_pushButton_clicked()
{
    this->clearHistoryFile();
    this->readHistoryToTextEdit();
}

