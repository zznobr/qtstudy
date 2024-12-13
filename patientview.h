#ifndef PATIENTVIEW_H
#define PATIENTVIEW_H

#include <QWidget>
#include <qdatawidgetmapper.h>

namespace Ui {
class patientView;
}

class patientView : public QWidget
{
    Q_OBJECT

public:

    QDataWidgetMapper *dataMapper;

    explicit patientView(QWidget *parent = nullptr);
    ~patientView();

private slots:
    void on_btnSearch_clicked();

    void on_btnAdd_clicked();

    void on_btnDel_clicked();

    void on_btnEdit_clicked();

private:
    Ui::patientView *ui;

signals:
    void toPatientEditView(int rowIndex);
};

#endif // PATIENTVIEW_H
