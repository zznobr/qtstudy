#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>

namespace Ui {
class inputWidget;
}

class inputWidget : public QWidget
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

    explicit inputWidget(QWidget *parent = nullptr);
    ~inputWidget();

private:
    Ui::inputWidget *ui;

private slots:

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
    void btnFourCalculateClick(); // "+ - * /"

signals:

    //保存记录
    void calculateRecord(QString record);

    // void nowNum_changed(double nowNum);
    void beforeQStr_changed(QString beforeQStr);
    void nowQStr_changed(QString nowQStr);

};

#endif // INPUTWIDGET_H
