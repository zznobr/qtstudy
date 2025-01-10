#ifndef EXCHANGERATE_H
#define EXCHANGERATE_H
#include <bits/stdc++.h>
#include <QString>

class ExchangeRate {
public:

    //币种
    std::map<QString,QString> currency;

    //储存汇率
    std::map<QString, double> rates;

    ExchangeRate();
    // 添加汇率
    void addRate(QString fromCurrency, QString toCurrency, double rate, QString name);

    // 获取汇率
    double getRate(QString fromCurrency, QString toCurrency);

};

#endif // EXCHANGERATE_H
