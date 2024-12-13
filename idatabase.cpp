#include "idatabase.h"
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

QString idatabase::userLogin(QString userName, QString userPassword)
{
    QSqlQuery query;
    QString password;
    query.prepare("select username,password from user where userName = :NAME");
    query.bindValue(":NAME",userName);
    query.exec();
    // qDebug()<<query.first()<<query.value("password")<<query.value("password").toString();
    if(query.first()&&query.value("username").isValid()){
        password = query.value("password").toString();
        if(userPassword == password){
            return "loginS";
        }
        else{
            return "PasswordError";
        }
    }
    qDebug()<<userName<<userPassword<<password;
    return "NULL";
}

void idatabase::initDataBase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    QString aFile = "D:/Allcode/qt/MasterPro/qtlab.db";
    database.setDatabaseName(aFile);

    if(!database.open()){
        qDebug()<<"数据库打开失败";
    }
    else{
        qDebug()<<"数据库打开成功";
    }
}

bool idatabase::initPatientModel()
{
    patientTabModel = new QSqlTableModel(this,database);
    patientTabModel->setTable("patient");
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    patientTabModel->setSort(patientTabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(patientTabModel->select()))
        return false;
    thePatientSelection = new QItemSelectionModel(patientTabModel);
    return true;
}

bool idatabase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();
}

bool idatabase::delPatient()
{
    QModelIndex currentIndex = thePatientSelection->currentIndex();
    patientTabModel->removeRow(currentIndex.row());
    patientTabModel->submitAll();
    patientTabModel->select();
}

int idatabase::addPatient()
{
    patientTabModel->insertRow(patientTabModel->rowCount(),QModelIndex());
    QModelIndex curIndex = patientTabModel->index(patientTabModel->rowCount()-1,1);
    int curRecNo = curIndex.row();
    QSqlRecord curRec = patientTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));
    patientTabModel->setRecord(curRecNo,curRec);
    return curIndex.row();
}

bool idatabase::submitPatientEdit()
{
    return patientTabModel->submitAll();
}

bool idatabase::revertPatientEdit()
{
    patientTabModel->revertAll();
}

idatabase::idatabase(QObject *parent)
    : QObject{parent}
{
    initDataBase();
}
