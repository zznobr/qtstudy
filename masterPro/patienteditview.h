#ifndef PATIENTEDITVIEW_H
#define PATIENTEDITVIEW_H

#include <QDataWidgetMapper>
#include <QWidget>

namespace Ui {
class patientEditView;
}

class patientEditView : public QWidget
{
    Q_OBJECT

public:

    QDataWidgetMapper *dataMapper;

    explicit patientEditView(QWidget *parent = nullptr);
    patientEditView(QWidget *parent,int index);
    ~patientEditView();

private slots:
    void on_btn_save_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::patientEditView *ui;

signals:
    void save();
    void cancel();

};

#endif // PATIENTEDITVIEW_H
