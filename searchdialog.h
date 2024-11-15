#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>

namespace Ui {
class searchDialog;
}

class searchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit searchDialog(QWidget *parent = nullptr);
    ~searchDialog();

    void clearDialog();
    void getText(QString text);

    void closeEvent(QCloseEvent *event);

private:
    Ui::searchDialog *ui;
    bool is_checkBox_case_checked;
    int index;
    QString target;
    QString text;

signals:

    void return_cursor_position(int position,int length,QString replace_word,bool is_replace);

    void unlock_textEdit();

private slots:
    void on_btn_next_clicked();
};

#endif // SEARCHDIALOG_H
