#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QWidget>
#include "idatabase.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pageCount = 0;
    goLoginView();

    idatabase::getInstance();

    connect(ui->btn_return,&QPushButton::clicked,this,&MainWindow::goPreviousView);
    connect(ui->btn_exit,&QPushButton::clicked,this,&MainWindow::on_pushButton_2_clicked);
    connect(loginpage,&loginView::loginSuccessful,this,&MainWindow::goMainPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushStackedView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    pageCount = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(pageCount-1);
    ui->label->setText(widget->windowTitle());
}

void MainWindow::goLoginView()
{
    loginpage = new loginView(this);
    pushStackedView(loginpage);
}

void MainWindow::goMainPage(QString id)
{
    mainpage = new mainPage(this);
    pushStackedView(mainpage);
    connect(this->mainpage,&mainPage::toPatientView,this,&MainWindow::goPatientView);
}

void MainWindow::goPatientView()
{
    qDebug()<<"patient view";
    patientpage = new patientView(this);
    pushStackedView(patientpage);
    connect(this->patientpage,&patientView::toPatientEditView,this,&MainWindow::goPatientEditView);
}

void MainWindow::goPatientEditView(int index)
{
    patientEditPage = new patientEditView(this,index);
    pushStackedView(patientEditPage);
    connect(this->patientEditPage,&patientEditView::save,this,&MainWindow::goPreviousView);
    connect(this->patientEditPage,&patientEditView::cancel,this,&MainWindow::goPreviousView);
}

void MainWindow::goPreviousView()
{
    pageCount = ui->stackedWidget->count();
    if(pageCount>1){
        QWidget *wight = ui->stackedWidget->currentWidget();
        ui->stackedWidget->setCurrentIndex(pageCount-1);
        ui->stackedWidget->removeWidget(wight);
        delete(wight);
    }
}


void MainWindow::on_pushButton_2_clicked(bool checked)
{
    if(QMessageBox::question(this,"退出","确定要退出吗？")==QMessageBox::Yes)
        this->close();
}

