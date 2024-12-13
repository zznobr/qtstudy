#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>

namespace Ui {
class loginView;
}

class loginView : public QWidget
{
    Q_OBJECT

public:
    explicit loginView(QWidget *parent = nullptr);
    ~loginView();

private slots:
    void on_btn_login_clicked();

private:
    Ui::loginView *ui;

signals:
    void loginSuccessful(QString id);

};



#endif // LOGINVIEW_H
