#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "inputwidget.h"
#include "sciinputwidget.h"
#include "datawidget.h"
#include "binaryconversionmodule.h"
#include "bitwise.h"
#include "exchangerateconversionmodule.h"
#include "capacityconversionmodule.h"
#include "historywidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    inputWidget *standardInputBox;
    sciInputWidget *sciInputBox;
    dataWidget *dateView;
    bitWise *bitWiseView;
    ExchangeRateConversionModule *rateModule;
    CapacityConversionModule *capacityModule;
    historyWidget * history;
    BinaryConversionModule *baseConversionModule;

    void setCentralWidgetStyle(QString styleSheetContent);
    QColor calculateContrastColor(const QColor &color);
    double sRGBToLinear(double value);

private slots:

    //更新步骤行数据
    void showLineBefore(QString str);
    //更新当前行数据
    void showLineNow(QString str);

    void on_btnBaseConversion_clicked();

    void toBinaryConversionModule();

    void onTabChanged(int index);

    void writeToHistory(QString str);

    void on_selectComboBox_currentTextChanged(const QString &arg1);
    void on_btnDateCalculate_clicked();
    void on_btnRateConversion_clicked();
    void on_btnCapacityConversion_clicked();
    void on_pushButton_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);
    void on_btnHistory_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_2_clicked();
    void on_spinBox_valueChanged(int arg1);
};
#endif // MAINWINDOW_H
