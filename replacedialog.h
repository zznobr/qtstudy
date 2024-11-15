#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>

namespace Ui {
class replaceDialog;
}

class replaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit replaceDialog(QWidget *parent = nullptr);
    ~replaceDialog();

    void clearDialog();
    void getText(QString text);

private slots:
    void on_btn_next_clicked();

private:
    Ui::replaceDialog *ui;
    bool is_checkBox_case_checked;
    int index;
    QString target;
    QString text;

signals:
    void replace_all(QString target,QString repalce_word);
    void return_cursor_position(int position,int length,QString replace_word,bool is_replace);

};

#endif // REPLACEDIALOG_H
