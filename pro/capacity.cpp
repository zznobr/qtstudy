#include "capacity.h"

Capacity::Capacity()
{
    //初始化容积列表
    this->capacityList = {{"m3","立方米"},
                          {"dm3","立方分米"},
                          {"cc","立方里面"},
                          {"l","升"},
                          {"dl","分升"},
                          {"ml","毫升"},
                          {"bbl","桶"},
                          {"gal","加仑"},
                          {"cup","杯"},
                          };

    //初始化容积转换列表
    this->capacityRates = {{"m3",0.001},
                           {"dm3",1},
                           {"cc",1000},
                           {"l",1},
                           {"dl",10},
                           {"ml",1000},
                           {"bbl",0.0062898},
                           {"gal",0.264172},
                           {"cup",4.226753},
                           };
}

double Capacity::getRate(QString fromCurrency, QString toCurrency)
{
    double returnRate = 0;
    returnRate = capacityRates.find(toCurrency)->second/ capacityRates.find(fromCurrency)->second;
    return returnRate;
}
