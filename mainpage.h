#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>

namespace Ui {
class mainPage;
}

class mainPage : public QWidget
{
    Q_OBJECT

public:
    explicit mainPage(QWidget *parent = nullptr);
    ~mainPage();

signals:
    void toPatientView();
    void toDoctorView();
    void toDepartmentView();

private slots:
    void on_btnToPatient_clicked();

    void on_btnToDoctor_clicked();

    void on_btnToDepartment_clicked();

private:
    Ui::mainPage *ui;
};

#endif // MAINPAGE_H
