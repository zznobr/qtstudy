#ifndef EXCHANGERATECONVERSIONMODULE_H
#define EXCHANGERATECONVERSIONMODULE_H

#include <QWidget>
#include "addratedialog.h"

namespace Ui {
class ExchangeRateConversionModule;
}

class ExchangeRateConversionModule : public QWidget
{
    Q_OBJECT

public:
    void language(QString str);

    explicit ExchangeRateConversionModule(QWidget *parent = nullptr);
    ~ExchangeRateConversionModule();

    //币种
    std::map<QString, QString> currencyList;

    //储存汇率
    std::map<QString, double> exchangeRates;

    // 添加汇率
    void addRate(QString enName,  QString cnName, double rate);

    // 获取汇率
    double getRate(QString fromCurrency, QString toCurrency);

    void loadData();

    QString getName(QString str);

    void updataTip();

private slots:
    void on_comboBox_1_currentTextChanged(const QString &arg1);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_doubleSpinBox_1_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_btnAddRate_clicked();

private:
    bool is_cn;

    QString currency1;
    QString currency2;

    AddRateDialog *addRateDialog;

    Ui::ExchangeRateConversionModule *ui;


};

#endif // EXCHANGERATECONVERSIONMODULE_H
