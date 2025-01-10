#ifndef BINARYCONVERSIONMODULE_H
#define BINARYCONVERSIONMODULE_H

#include <QWidget>
#include "baseinputwidget.h"

namespace Ui {
class BinaryConversionModule;
}

class BinaryConversionModule : public QWidget
{
    Q_OBJECT

public:
    void language(QString str);

    explicit BinaryConversionModule(QWidget *parent = nullptr);
    ~BinaryConversionModule();

    int base1 = 10;
    int base2 = 10;

    //进制
    std::map<QString,QString> baseList;

    //进制转换
    std::map<QString, double> baseRates;

    //切换中文
    void switchChinese();

    //切换英文
    void switchEnglish();

signals:
    void returnBase(int base,QString nowStr);
private slots:
    void on_lineEdit_1_selectionChanged();
    void getBase1();
    void getBase2();
    void showLine(QString str);

    void on_lineEdit_2_editingFinished();

    void on_comboBox_1_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

private:
    Ui::BinaryConversionModule *ui;
    BaseInputWidget *inputBox;
    bool is_cn;
    int nowLineEditIndex;

    void updateBase(int index, QString str);
    int getBase(int index);
    QString convertNumber(const QString& str, int fromBase, int toBase); //数字进制转换

};

#endif // BINARYCONVERSIONMODULE_H
