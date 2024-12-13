#include "patientview.h"
#include "ui_patientview.h"
#include "idatabase.h"

patientView::patientView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::patientView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    idatabase &iDatabase = idatabase::getInstance();
    if(iDatabase.initPatientModel()){
        ui->tableView->setModel(iDatabase.patientTabModel);
        ui->tableView->setSelectionModel(iDatabase.thePatientSelection);
    }
}

patientView::~patientView()
{
    delete ui;
}

void patientView::on_btnSearch_clicked()
{
    QString filter = QString("name like '%%1%'").arg(ui->lineEdit->text());
    idatabase::getInstance().searchPatient(filter);
}


void patientView::on_btnAdd_clicked()
{
    int currow = idatabase::getInstance().addPatient();
    // qDebug()<<currow;
    emit toPatientEditView(currow);
}


void patientView::on_btnDel_clicked()
{
    idatabase::getInstance().delPatient();
}


void patientView::on_btnEdit_clicked()
{
    QModelIndex curIndex = idatabase::getInstance().thePatientSelection->currentIndex();
    // qDebug()<<curIndex.row();
    emit toPatientEditView(curIndex.row());
}

