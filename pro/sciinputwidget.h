#ifndef SCIINPUTWIDGET_H
#define SCIINPUTWIDGET_H

#include <QWidget>

namespace Ui {
class sciInputWidget;
}

class sciInputWidget : public QWidget
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

    void language(QString str);

    explicit sciInputWidget(QWidget *parent = nullptr);
    ~sciInputWidget();

private slots:
    void on_btnROOT_clicked();

private:

    void btnNumClick();//Number
    void btnPointClick();//" . "
    void btnBackClick();//" Del "
    void btnOppositeClick();//" +/- "
    void btnReciprocalClick();//" 1/x "
    void btnCeClick();// " CE "
    void btnCClick();// " C "
    void btnPercentClick();// " % "
    void btnSqrClick();// " SQR "
    void btnSqrtClick();// " EXT "
    void btnCalculateClick(); // "+ - * /"
    void btnTrigCalculateClick(); // sin cos tan

    Ui::sciInputWidget *ui;

signals:
    //保存记录
    void calculateRecord(QString record);

    // void nowNum_changed(double nowNum);
    void beforeQStr_changed(QString beforeQStr);
    void nowQStr_changed(QString nowQStr);


};

#endif // SCIINPUTWIDGET_H
