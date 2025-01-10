#ifndef BITWISE_H
#define BITWISE_H

#include <QWidget>

namespace Ui {
class bitWise;
}

class bitWise : public QWidget
{
    Q_OBJECT

public:

    void language(QString str);

    explicit bitWise(QWidget *parent = nullptr);
    ~bitWise();

private:

    QString beforeQStr;
    QString nowQStr;
    QString firstStr;
    QString beforeOp;
    bool isOp;

    bool checkOpExist();
    void showBefore();
    void calculate();
    QString clearZero(QString str);

    int binaryStringToInt( QString binStr);
    QString intToBinaryString(int num, int bitLength = 0);
    QString bitwiseAnd( QString str1,  QString str2);
    QString bitwiseOr( QString str1,  QString str2);
    QString bitwiseXor( QString str1,  QString str2);
    QString leftShift( QString str, int shiftAmount);
    QString rightShift( QString str, int shiftAmount);

    Ui::bitWise *ui;

private slots:
    void btnNumClick();//Number
    void btnBackClick();//" Del "
    void btnCClick();//"  C  "
    void btnCeClick();// " CE "
    void dualOp();
    void on_btnLEFT_clicked();
    void on_btnRIGHT_clicked();
    void on_btnTEN_clicked();

signals:

    //保存记录
    void calculateRecord(QString record);

};

#endif // BITWISE_H
