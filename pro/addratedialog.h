#ifndef ADDRATEDIALOG_H
#define ADDRATEDIALOG_H

#include <QDialog>

namespace Ui {
class AddRateDialog;
}

class AddRateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRateDialog(QWidget *parent = nullptr);
    ~AddRateDialog();

    QString nameEnglish();
    QString nameChinese();
    double rate();

    void clear();

private:
    Ui::AddRateDialog *ui;
};

#endif // ADDRATEDIALOG_H
