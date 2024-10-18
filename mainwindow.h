#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QString beforeQStr;
    QString nowQStr;
    QString firstStr;
    QString beforeOp;
    double beforeNum;
    double nowNum;
    bool isOp;

    bool checkOpExist();
    void showBefore();
    void calculate();
    QString clearZero(QString str);

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void btnNumClick();//Number
    void btnPointClick();//" . "
    void btnBackClick();//" X "
    void btnOppositeClick();//" +/- "
    void btnReciprocalClick();//" 1/x "
    void btnCeClick();// " CE "
    void btnCClick();// " C "
    void btnPrecentClick();// " % "
    void btnSqrClick();// " SQR "
    void btnSqrtClick();// " EXT "
    void btnFourCalculateClick(); // "+ - * /"
};
#endif // MAINWINDOW_H
