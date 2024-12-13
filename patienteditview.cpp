#include "patienteditview.h"
#include "ui_patienteditview.h"
#include "idatabase.h"
#include <QMessageBox>

patientEditView::patientEditView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::patientEditView)
{
    ui->setupUi(this);

}

patientEditView::patientEditView(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::patientEditView)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tabModel = idatabase::getInstance().patientTabModel;
    dataMapper->setModel(idatabase::getInstance().patientTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->input_id,tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->input_name,tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->input_card,tabModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->height_Spin,tabModel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(ui->weight_Spin,tabModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->input_callNumber,tabModel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(ui->date_select,tabModel->fieldIndex("DOB"));
    dataMapper->addMapping(ui->sex_select,tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->input_create,tabModel->fieldIndex("CREATEDTIMESTAMP"));

    dataMapper->setCurrentIndex(index);

}

patientEditView::~patientEditView()
{
    // emit ui->btn_cancel->click();
    delete ui;
}

void patientEditView::on_btn_save_clicked()
{
    if(idatabase::getInstance().submitPatientEdit()){
        qDebug()<<"保存成功";
        emit this->save();
    }
    else{
        QMessageBox::information(this,"提示","保存失败");
    }
}


void patientEditView::on_btn_cancel_clicked()
{
    idatabase::getInstance().revertPatientEdit();
    emit this->cancel();
}

