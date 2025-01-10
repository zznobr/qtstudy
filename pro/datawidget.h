#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include <QWidget>

namespace Ui {
class dataWidget;
}

class dataWidget : public QWidget
{
    Q_OBJECT

public:
    void language(QString str);

    explicit dataWidget(QWidget *parent = nullptr);
    ~dataWidget();

private:
    bool is_cn;
    QDate addDaysToDate( QDate date, int days);
    QDate subtractDaysFromDate( QDate date, int days);
    int daysBetweenDates( QDate date1,  QDate date2);
    void dateChange(QDate date1, QDate date2);
    QTimer* m_timer;
    Ui::dataWidget *ui;

private slots:
    void updateDateTime();
    void on_nowData_dateChanged(const QDate &date);
    void on_toData_dateChanged(const QDate &date);
    void on_addData_clicked();
    void on_subData_clicked();
};

#endif // DATAWIDGET_H
