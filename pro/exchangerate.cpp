#include "exchangerate.h"
#include <bits/stdc++.h>

ExchangeRate::ExchangeRate()
{
    //初始化币种列表
    this->currency = {{"CNY","人民币"},
                      {"USD","美元"},
                      {"JPY","日元"},
                      {"EUR","欧元"},
                      {"GBP","英镑"},
                      {"RUB","卢布"},
                      {"KRW","韩元"},
                      {"AUD","澳大利亚元"},
                      {"HKD","港元"},
                      {"MOP","澳元"},
                      {"TWD","台元"}};

    //初始化汇率表
    this->rates = {{"CNY",1},
        {"USD",0.14},
        {"JPY",20.59},
        {"EUR",0.13},
        {"GBP",0.11},
        {"RUB",14.58},
        {"KRW",192.4},
        {"AUD",0.21},
        {"HKD",1.07},
        {"MOP",1.1},
        {"TWD",4.47}
    };
}

// 添加汇率
void ExchangeRate::addRate(QString fromCurrency, QString toCurrency, double rate, QString name) {
    double newRate = getRate("CNY",toCurrency);
    newRate = newRate / rate;
    //加入汇率表
    if(this->rates.count(fromCurrency) == 0)
        this->rates[fromCurrency] = newRate;
    //加入币种列表
    if(this->currency.count(fromCurrency) == 0)
        this->currency[fromCurrency] = name;
}

// 获取汇率
double ExchangeRate::getRate(QString fromCurrency, QString toCurrency)  {
    double returnRate = 0;
    returnRate = rates.find(toCurrency)->second/ rates.find(fromCurrency)->second;
    return returnRate;
}
