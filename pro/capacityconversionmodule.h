#ifndef CAPACITYCONVERSIONMODULE_H
#define CAPACITYCONVERSIONMODULE_H

#include <QWidget>

namespace Ui {
class CapacityConversionModule;
}

class CapacityConversionModule : public QWidget
{
    Q_OBJECT

public:
    void language(QString str);

    explicit CapacityConversionModule(QWidget *parent = nullptr);
    ~CapacityConversionModule();

    //容积
    std::map<QString, QString> capacityList;

    //容积转换
    std::map<QString, double> capacityRates;

    //获取转换
    double getRate(QString fromCapacity, QString toCapacity);

    void loadData();

    QString getName(QString str);

    void updataTip();

private slots:
    void on_comboBox_1_currentTextChanged(const QString &arg1);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_doubleSpinBox_1_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

private:
    QString capacity1;
    QString capacity2;
    bool is_cn;

    Ui::CapacityConversionModule *ui;
};

#endif // CAPACITYCONVERSIONMODULE_H
