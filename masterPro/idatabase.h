#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QDataWidgetMapper>
#include <QtSql>

class idatabase : public QObject
{
    Q_OBJECT

public:

    static idatabase &getInstance(){
        static idatabase instance;
        return instance;
    }

    QString userLogin(QString userName,QString userPassword);

    bool initPatientModel();

    bool searchPatient(QString filter);
    bool delPatient();
    int addPatient();
    bool editPatient();
    bool submitPatientEdit();
    bool revertPatientEdit();

    QSqlTableModel *patientTabModel;
    QItemSelectionModel *thePatientSelection;


private:

    void initDataBase();

    explicit idatabase(QObject *parent = nullptr);
    idatabase(idatabase const &) = delete;
    void operator=(idatabase const &) = delete;

    QSqlDatabase database;

signals:


};

#endif // IDATABASE_H
