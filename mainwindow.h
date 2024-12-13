#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginview.h"
#include "mainpage.h"
#include "patientview.h"
#include "patienteditview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int pageCount;

    loginView *loginpage;
    mainPage *mainpage;
    patientView *patientpage;
    patientEditView *patientEditPage;

    void pushStackedView(QWidget *widget);

private:
    Ui::MainWindow *ui;

public slots:
    void goLoginView();
    void goMainPage(QString id);
    void goPatientView();
    void goPatientEditView(int index);
    void goPreviousView();

private slots:
    void on_pushButton_2_clicked(bool checked);

signals:
    ;

};
#endif // MAINWINDOW_H
