#ifndef CAPACITY_H
#define CAPACITY_H
#include <bits/stdc++.h>
#include <QString>

class Capacity
{
public:
    Capacity();

    //容积类型
    std::map<QString,QString> capacityList;

    //容积转换
    std::map<QString, double> capacityRates;

    //获取转换
    double getRate(QString fromCurrency, QString toCurrency);
};

#endif // CAPACITY_H



