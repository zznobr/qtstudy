#ifndef BASEINPUTWIDGET_H
#define BASEINPUTWIDGET_H

#include <QWidget>

namespace Ui {
class BaseInputWidget;
}

class BaseInputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BaseInputWidget(QWidget *parent = nullptr);
    ~BaseInputWidget();

    QString beforeStr;
    QString nowStr;
    // double beforeNum;
    // double nowNum;

signals:
    // void beforeStr_changed(QString beforeStr);
    void nowStr_changed(QString nowStr);

public slots:
    void baseChanged(int base, QString nowStr);

private slots:
    void on_btnADD_clicked();
    void btnNumClick();//Number
    void btnPointClick();//" . "
    void btnBackClick();//" Del "
    void btnCClick();//"  C  "

private:
    Ui::BaseInputWidget *ui;
    int nowbase;

    void binModel();//切换二进制
    void quaModel();//切换四进制
    void octModel();//切换八进制
    void decModel();//切换十进制
    void hexModel();//切换十六进制

};

#endif // BASEINPUTWIDGET_H
