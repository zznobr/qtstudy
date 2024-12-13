#include "mainpage.h"
#include "ui_mainpage.h"

mainPage::mainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainPage)
{
    ui->setupUi(this);
}

mainPage::~mainPage()
{
    delete ui;
}

void mainPage::on_btnToPatient_clicked()
{
    emit toPatientView();
}


void mainPage::on_btnToDoctor_clicked()
{
    emit toDoctorView();
}


void mainPage::on_btnToDepartment_clicked()
{
    emit toDepartmentView();
}

